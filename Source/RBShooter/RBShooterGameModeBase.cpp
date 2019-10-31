// Copyright (c) 2019 PSQ Grupp 4 =)


#include "RBShooterGameModeBase.h"
#include "Level/EnemySpawnNode.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Enemy/Enemy.h"

ARBShooterGameModeBase::ARBShooterGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bGameActive = false;
	bFirstBurstDelayActive = false;
	bWaitForEnemiesToDie = false;
	bHasAttemptedToStartGame = false;
	FirstBurstDelay = 0.0f;

	ResetWaveVariables();
}

ARBShooterGameModeBase::~ARBShooterGameModeBase()
{

}

void ARBShooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ResetToDefault();

	if (bHasAttemptedToStartGame)
	{
		StartGameIfPossible(FirstBurstDelay, bWaitForEnemiesToDie);
	}
}

void ARBShooterGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsWaitingForEnemiesToDie)
	{
		if (AttemptToStartNextWave())
		{
			bIsWaitingForEnemiesToDie = false;
		}
	}
}

float ARBShooterGameModeBase::GetWaveTimeLeft()
{
	float TimeElapsed = FMath::Max(GetWorldTimerManager().GetTimerElapsed(WaveTimerHandle), 0.0f);
	return CurrentWaveDuration - TimeElapsed;
}

float ARBShooterGameModeBase::GetWaveTimeLeftPercent()
{
	return GetWaveTimeLeft() / CurrentWaveDuration;
}

float ARBShooterGameModeBase::GetBurstTimeLeft()
{
	float TimeElapsed = FMath::Max(GetWorldTimerManager().GetTimerElapsed(BurstTimerHandle), 0.0f);
	return CurrentBurstDuration - TimeElapsed;
}

float ARBShooterGameModeBase::GetBurstTimeLeftPercent()
{
	return GetBurstTimeLeft() / CurrentBurstDuration;
}

void ARBShooterGameModeBase::ResetWaveVariables()
{
	bWaveActive = false;
	bIsWaitingForEnemiesToDie = false;
	CurrentBurstDuration = 0.0f;
	CurrentBurstPauseDuration = 0.0f;
	CurrentWaveDuration = 0.0f;
	CurrentSpawnInterval = 0.0f;
	NumNextBurstEnemies = 0;
	NumCurrentEnemiesPendingSpawn = 0;
	NumTotalEnemiesSpawnedThisWave = 0;
	CurrentWave = 0;
	CurrentWaveBurst = 0;
}

bool ARBShooterGameModeBase::StartGameIfPossible(float TimeUntilFirstBurst /*= 0.0f*/, bool bWaitForEnemies /*= true*/)
{
	FirstBurstDelay = TimeUntilFirstBurst;
	bWaitForEnemiesToDie = bWaitForEnemies;
	bHasAttemptedToStartGame = true;

	if (EnemySpawnNodes.Num() > 0)
	{
		bGameActive = true;

		OnNextWaveReady(CurrentWave);

		if (TimeUntilFirstBurst > 0.0f)
		{
			GetWorldTimerManager().SetTimer(InitialWaveBurstTimer, this, &ARBShooterGameModeBase::FirstBurstDelayTimerUpdate, TimeUntilFirstBurst, false, -1.0f);
			bFirstBurstDelayActive = true;
		}

		bHasAttemptedToStartGame = false;

		return true;
	}

	return false;
}

void ARBShooterGameModeBase::ResetToDefault()
{
	StopWave();

	ResetWaveVariables();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnNode::StaticClass(), EnemySpawnNodes);
}

bool ARBShooterGameModeBase::StartWave(int32 NumberOfBursts, float BurstDuration, float BurstPauseDuration)
{
	if (!bWaveActive)
	{
		bWaveActive = true;
		NumTotalEnemiesSpawnedThisWave = 0;
		UGameUtility::ResetKillcount(DeadEnemyCountThisWave);

		CurrentWave++;
		CurrentWaveBurst = 0;

		CurrentBurstDuration = BurstDuration;
		CurrentBurstPauseDuration = BurstPauseDuration;

		float BurstDurationTotal = BurstDuration + BurstPauseDuration;
		float WaveDuration = BurstDurationTotal * (float)NumberOfBursts;

		CurrentWaveDuration = WaveDuration;

		UGameUtility::ResetKillcount(KillCountThisWave);

		// Start wave timer
		GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &ARBShooterGameModeBase::WaveTimerUpdate, WaveDuration, false, -1.0f);

		OnWaveStarted(CurrentWave);

		// Start first burst
		if (!bFirstBurstDelayActive)
		{
			OnNextBurstReady(CurrentWave, CurrentWaveBurst);
		}

		return true;
	}

	return false;
}

bool ARBShooterGameModeBase::StopWave()
{
	if (bWaveActive)
	{
		bWaveActive = false;

		// Stop wave timer
		GetWorldTimerManager().ClearTimer(WaveTimerHandle);

		// Stop burst timer
		StopBurst();

		return true;
	}

	return false;
}

bool ARBShooterGameModeBase::StartBurst(int32 NumEnemiesToSpawn)
{
	if (bGameActive)
	{
		CurrentWaveBurst++;

		// Start burst timer
		float BurstInterval = CurrentBurstDuration + CurrentBurstPauseDuration;
		GetWorldTimerManager().SetTimer(BurstTimerHandle, this, &ARBShooterGameModeBase::BurstTimerUpdate, BurstInterval, false, -1.0f);

		NumNextBurstEnemies = NumEnemiesToSpawn;

		OnBurstStarted(CurrentWave, CurrentWaveBurst);

		// Start burst enemy spawning
		GetRandomEnemySpawnNodes(NumEnemiesToSpawn, SelectedEnemySpawnNodes);
		if (SelectedEnemySpawnNodes.Num() > 0)
		{
			// Start the burst spawn timer
			NumCurrentEnemiesPendingSpawn = NumEnemiesToSpawn;
			float BurstSpawnInterval = CurrentBurstDuration / (float)NumEnemiesToSpawn;

			// Notify the spawn nodes that they're about to spawn
			for (int32 i = 0; i < SelectedEnemySpawnNodes.Num(); i++)
			{
				float TimeUntilFirstSpawn = (1.0f + (float)i) * BurstSpawnInterval;
				AEnemySpawnNode* SpawnNode = Cast<AEnemySpawnNode>(SelectedEnemySpawnNodes[i]);
				if (SpawnNode)
				{
					SpawnNode->OnSpawnSelected(TimeUntilFirstSpawn);
				}
			}

			GetWorldTimerManager().SetTimer(BurstSpawnTimerHandle, this, &ARBShooterGameModeBase::BurstSpawnTimerUpdate, BurstSpawnInterval, true, 0.0f);

			return true;
		}
	}

	return false;
}

bool ARBShooterGameModeBase::StopBurst()
{
	// Stop burst timer
	GetWorldTimerManager().ClearTimer(BurstTimerHandle);
	GetWorldTimerManager().ClearTimer(BurstSpawnTimerHandle);

	return true;
}

void ARBShooterGameModeBase::GetRandomEnemySpawnNodes(int32 NumNodes, TArray<AActor*>& OutNodes)
{
	OutNodes.Reset();

	TArray<AActor*> SpawnableNodes;
	GetSpawnableNodes(SpawnableNodes);

	// SpawnableNodes can't be empty
	if (SpawnableNodes.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnableNodes is empty!"));
		return;
	}

	// Early exit - number of nodes to be randomized is equal to number of spawnable nodes (no randomization needed)
	if (NumNodes == SpawnableNodes.Num())
	{
		OutNodes = SpawnableNodes;
		return;
	}

	// Randomize nodes
	bool bDoDuplicateCheck = true;
	for (int32 i = 0; i < NumNodes; i++)
	{
		int32 RandomIndex = FMath::RandRange(0, SpawnableNodes.Num() - 1);

		// Find a random index from all available nodes, that is not a duplicate of currently selected node array
		int32 IterateCount = 0;
		while (IterateCount < SpawnableNodes.Num())
		{
			// Check if the node was already added
			bool bFoundSameIndex = false;
			if (bDoDuplicateCheck)
			{
				for (int32 j = 0; j < OutNodes.Num(); j++)
				{
					if (SpawnableNodes[RandomIndex] == OutNodes[j])
					{
						bFoundSameIndex = true;
						break;
					}
				}
			}

			if (!bFoundSameIndex)
			{
				break;
			}

			// Re-generate random index
			RandomIndex = FMath::RandRange(0, SpawnableNodes.Num() - 1);

			IterateCount++;
		}

		// "Select" the node by adding it to the array
		OutNodes.Add(SpawnableNodes[RandomIndex]);

		if (OutNodes.Num() >= SpawnableNodes.Num())
		{
			bDoDuplicateCheck = false;
		}
	}
}

bool ARBShooterGameModeBase::CanEnemyNodeBeSpawned(AEnemySpawnNode* SpawnNode)
{
	if (CurrentWave >= SpawnNode->MinimumWaveCount && !SpawnNode->bIsSpawnInProgress)
	{
		return true;
	}

	return false;
}

bool ARBShooterGameModeBase::AttemptToStartNextWave()
{
	if (bWaitForEnemiesToDie)
	{
		// Check if dead enemy count this wave is equal to number of enemies that were spawned
		if (DeadEnemyCountThisWave.KillCountTotal >= NumTotalEnemiesSpawnedThisWave)
		{
			// Start next wave
			OnNextWaveReady(CurrentWave);
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Waiting for all enemies to die before starting wave (%i >= %i)"), DeadEnemyCountThisWave.KillCountTotal, NumTotalEnemiesSpawnedThisWave);
			return false;
		}
	}

	// Start next wave since we're not waiting for enemies to die first
	OnNextWaveReady(CurrentWave);

	return true;
}

void ARBShooterGameModeBase::ActivateNextEnemyNode()
{
	if (NumCurrentEnemiesPendingSpawn > 0)
	{
		int32 CurrentEnemyIndex = SelectedEnemySpawnNodes.Num() - NumCurrentEnemiesPendingSpawn;
		checkf(CurrentEnemyIndex >= 0 && CurrentEnemyIndex < SelectedEnemySpawnNodes.Num(), TEXT("Index out of bounds"));

		AEnemySpawnNode* SpawnNode = Cast<AEnemySpawnNode>(SelectedEnemySpawnNodes[CurrentEnemyIndex]);
		if (SpawnNode)
		{
			AEnemy* SpawnedEnemy = SpawnNode->ActivateSpawn();
			SpawnedEnemy->WaveCountSpawnedAt = CurrentWave;
			SpawnedEnemy->BurstCountSpawnedAt = CurrentWaveBurst;

			NumTotalEnemiesSpawnedThisWave++;
			OnEnemySpawned(SpawnedEnemy, SpawnNode, CurrentEnemyIndex, CurrentWave, CurrentWaveBurst);

			SpawnNode->OnPostSpawnEvent(SpawnedEnemy, CurrentEnemyIndex, CurrentWave, CurrentWaveBurst);
			
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Spawn Node is not AEnemySpawnNode!"));
		}

		NumCurrentEnemiesPendingSpawn--;

		if (NumCurrentEnemiesPendingSpawn <= 0)
		{
			GetWorldTimerManager().ClearTimer(BurstSpawnTimerHandle);
		}
	}
}

void ARBShooterGameModeBase::WaveTimerUpdate()
{
	StopWave();

	float TimeElapsed = GetWorldTimerManager().GetTimerElapsed(WaveTimerHandle);
	OnWaveCompleted(CurrentWave, CurrentWaveBurst);

	bool bWasStarted = AttemptToStartNextWave();
	if (!bWasStarted)
	{
		bIsWaitingForEnemiesToDie = true;
	}
}

void ARBShooterGameModeBase::BurstTimerUpdate()
{
	StopBurst();
	OnBurstCompleted(CurrentWave, CurrentWaveBurst);
	OnNextBurstReady(CurrentWave, CurrentWaveBurst);
}

void ARBShooterGameModeBase::BurstSpawnTimerUpdate()
{
	ActivateNextEnemyNode();
}

void ARBShooterGameModeBase::FirstBurstDelayTimerUpdate()
{
	bFirstBurstDelayActive = false;
	OnNextBurstReady(CurrentWave, CurrentWaveBurst);
}

void ARBShooterGameModeBase::GetSpawnableNodes(TArray<AActor*>& OutNodes)
{
	for (int32 i = 0; i < EnemySpawnNodes.Num(); i++)
	{
		AEnemySpawnNode* EnemySpawnNode = Cast<AEnemySpawnNode>(EnemySpawnNodes[i]);
		if (EnemySpawnNode && CanEnemyNodeBeSpawned(EnemySpawnNode))
		{
			OutNodes.Add(EnemySpawnNode);
		}
	}
}
