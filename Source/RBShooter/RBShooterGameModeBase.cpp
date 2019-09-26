// Copyright (c) 2019 PSQ Grupp 4 =)


#include "RBShooterGameModeBase.h"
#include "Level/EnemySpawnNode.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

ARBShooterGameModeBase::ARBShooterGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;

	bGameActive = false;

	ResetWaveVariables();
}

ARBShooterGameModeBase::~ARBShooterGameModeBase()
{

}

void ARBShooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ResetToDefault();
}

void ARBShooterGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// TODO enable tick in constructor before using this
}

void ARBShooterGameModeBase::ResetWaveVariables()
{
	bWaveActive = false;
	CurrentBurstDuration = 0.0f;
	CurrentBurstPauseDuration = 0.0f;
	CurrentWaveDuration = 0.0f;
	CurrentSpawnInterval = 0.0f;
	NumNextBurstEnemies = 0;
	NumCurrentEnemiesPendingSpawn = 0;
	CurrentWave = 0;
	CurrentWaveBurst = 0;
}

bool ARBShooterGameModeBase::StartGameIfPossible(float TimeUntilFirstBurst)
{
	if (EnemySpawnNodes.Num() > 0)
	{
		bGameActive = true;

		OnNextWaveReady(CurrentWave);

		if (TimeUntilFirstBurst > 0.0f)
		{
			GetWorldTimerManager().SetTimer(InitialWaveBurstTimer, this, &ARBShooterGameModeBase::FirstBurstDelayTimerUpdate, TimeUntilFirstBurst, false, -1.0f);
		}
		else
		{
			OnNextBurstReady(CurrentWaveBurst, CurrentWaveBurst);
		}

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

		CurrentWave++;
		CurrentWaveBurst = 0;

		CurrentBurstDuration = BurstDuration;
		CurrentBurstPauseDuration = BurstPauseDuration;

		float BurstDurationTotal = BurstDuration + BurstPauseDuration;
		float WaveDuration = BurstDurationTotal * (float)NumberOfBursts;

		CurrentWaveDuration = WaveDuration;

		UE_LOG(LogTemp, Warning, TEXT("Starting Wave. Number of bursts %i Burst Duration %f Pause %f Wave Duration %f"), NumberOfBursts, BurstDuration, BurstPauseDuration, WaveDuration);

		// Start wave timer
		GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &ARBShooterGameModeBase::WaveTimerUpdate, WaveDuration, false, -1.0f);

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

		float TimeElapsed = GetWorldTimerManager().GetTimerElapsed(WaveTimerHandle);
		OnWaveCompleted(CurrentWave, TimeElapsed);

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

		// Start burst enemy spawning
		GetRandomEnemySpawnNodes(NumEnemiesToSpawn, SelectedEnemySpawnNodes);
		if (SelectedEnemySpawnNodes.Num() > 0)
		{
			// Start the burst spawn timer
			NumCurrentEnemiesPendingSpawn = NumEnemiesToSpawn;
			float BurstSpawnInterval = CurrentBurstDuration / (float)NumEnemiesToSpawn;
			UE_LOG(LogTemp, Warning, TEXT("Enemies %i Interval %f"), NumEnemiesToSpawn, BurstSpawnInterval);
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

	// Early exit - number of nodes to be randomized is equal to number of existing nodes (no randomization needed)
	if (NumNodes == EnemySpawnNodes.Num())
	{
		OutNodes = EnemySpawnNodes;
		return;
	}

	// Randomize nodes
	bool bDoDuplicateCheck = true;
	for (int32 i = 0; i < NumNodes; i++)
	{
		int32 RandomIndex = FMath::RandRange(0, EnemySpawnNodes.Num() - 1);;

		// Find a random index from all available nodes, that is not a duplicate of currently selected node array
		bool bIndexOk = false;
		int32 IterateCount = 0;
		while (!bIndexOk && IterateCount < EnemySpawnNodes.Num())
		{
			// Check if the node was already added
			bool bFoundSameIndex = false;
			if (bDoDuplicateCheck)
			{
				for (int32 j = 0; j < OutNodes.Num(); j++)
				{
					if (EnemySpawnNodes[RandomIndex] == OutNodes[j])
					{
						bFoundSameIndex = true;
					}
				}
			}

			if (!bFoundSameIndex)
			{
				// Cast to its base class
				AEnemySpawnNode* SpawnNode = Cast<AEnemySpawnNode>(EnemySpawnNodes[RandomIndex]);

				if (SpawnNode)
				{
					// Check if the node qualifies
					if (CanEnemyNodeBeSpawned(SpawnNode))
					{
						bIndexOk = true;
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("SpawnNode is nullptr!"));
				}
			}

			// Re-generate random index
			RandomIndex = FMath::RandRange(0, EnemySpawnNodes.Num() - 1);

			IterateCount++;
		}

		// "Select" the node by adding it to the array
		OutNodes.Add(EnemySpawnNodes[RandomIndex]);

		if (OutNodes.Num() >= EnemySpawnNodes.Num())
		{
			bDoDuplicateCheck = false;
		}
	}
}

bool ARBShooterGameModeBase::CanEnemyNodeBeSpawned(AEnemySpawnNode* SpawnNode)
{
	if (CurrentWave >= SpawnNode->MinimumWaveCount)
	{
		return true;
	}

	return false;
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
			SpawnNode->ActivateSpawn();
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
	OnWaveCompleted(CurrentWave, CurrentWaveBurst);
	OnNextWaveReady(CurrentWave);

	UE_LOG(LogTemp, Warning, TEXT("WaveTimerUpdate"));
}

void ARBShooterGameModeBase::BurstTimerUpdate()
{
	StopBurst();
	OnBurstCompleted(CurrentWave, CurrentWaveBurst);
	OnNextBurstReady(CurrentWave, CurrentWaveBurst);

	UE_LOG(LogTemp, Warning, TEXT("BurstTimerUpdate"));
}

void ARBShooterGameModeBase::BurstSpawnTimerUpdate()
{
	ActivateNextEnemyNode();

	UE_LOG(LogTemp, Warning, TEXT("BurstSpawnTimerUpdate %i"), NumCurrentEnemiesPendingSpawn);
}

void ARBShooterGameModeBase::FirstBurstDelayTimerUpdate()
{
	OnNextBurstReady(CurrentWave, CurrentWaveBurst);
}
