// Copyright (c) 2019 PSQ Grupp 4 =)


#include "RBShooterGameModeBase.h"
#include "Level/EnemySpawnNode.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

ARBShooterGameModeBase::ARBShooterGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;

	bWaveActive = false;
	NextBurstNumEnemies = 0;
	CurrentWave = 0;
	CurrentWaveBurst = 0;
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

void ARBShooterGameModeBase::ResetToDefault()
{
	StopWave();

	bWaveActive = false;
	NextBurstNumEnemies = 0;
	CurrentWave = 0;
	CurrentWaveBurst = 0;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnNode::StaticClass(), EnemySpawnNodes);
}

EEnemySpawnTypes ARBShooterGameModeBase::GetRandomEnemySpawnType()
{
	return (EEnemySpawnTypes)FMath::RandRange(1, (int32)EEnemySpawnTypes::EST_COUNT - 1);
}

bool ARBShooterGameModeBase::StartWave(float WaveDuration, float BurstInterval, int32 FirstBurstNumEnemies)
{
	if (!bWaveActive)
	{
		bWaveActive = true;

		CurrentWave++;
		CurrentWaveBurst = 0;

		// Start wave timer
		GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &ARBShooterGameModeBase::WaveTimerUpdate, WaveDuration, false, -1.0f);

		StartBurst(BurstInterval, FirstBurstNumEnemies);

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

bool ARBShooterGameModeBase::StartBurst(float BurstInterval, int32 NumEnemiesToSpawn)
{
	if (bWaveActive)
	{
		// Start burst timer
		GetWorldTimerManager().SetTimer(BurstTimerHandle, this, &ARBShooterGameModeBase::BurstTimerUpdate, BurstInterval, false, -1.0f);

		NextBurstNumEnemies = NumEnemiesToSpawn;

		return true;
	}

	return false;
}

bool ARBShooterGameModeBase::StopBurst()
{
	// Stop burst timer
	GetWorldTimerManager().ClearTimer(BurstTimerHandle);

	return true;
}

bool ARBShooterGameModeBase::DoWaveBurst(int32 NumEnemiesToSpawn)
{
	TArray<AActor*> SelectedEnemySpawnNodes;
	GetRandomEnemySpawnNodes(NumEnemiesToSpawn, SelectedEnemySpawnNodes);

	if (SelectedEnemySpawnNodes.Num() > 0)
	{
		for (int32 i = 0; i < SelectedEnemySpawnNodes.Num(); i++)
		{
			AEnemySpawnNode* SpawnNode = Cast<AEnemySpawnNode>(SelectedEnemySpawnNodes[i]);
			if (SpawnNode)
			{
				SpawnNode->ActivateSpawn();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Spawn Node is not AEnemySpawnNode!"));
			}
		}

		CurrentWaveBurst++;

		OnWaveBurst(CurrentWave, CurrentWaveBurst, NumEnemiesToSpawn);

		return true;
	}

	return false;
}

void ARBShooterGameModeBase::GetRandomEnemySpawnNodes(int32 NumNodes, TArray<AActor*>& OutNodes)
{
	OutNodes.Reset();

	// Cant randomize more nodes than existing
	NumNodes = FMath::Clamp(NumNodes, 0, EnemySpawnNodes.Num());

	// Early exit - number of nodes to be randomized is equal to number of existing nodes (no randomization needed)
	if (NumNodes == EnemySpawnNodes.Num())
	{
		OutNodes = EnemySpawnNodes;
		return;
	}

	// Randomize nodes
	for (int32 i = 0; i < NumNodes; i++)
	{
		int32 RandomIndex = -1;

		// Find a random index from all available nodes, that is not a duplicate of currently selected node array
		bool bIndexOk = false;
		int32 IterateCount = 0;
		while (!bIndexOk && IterateCount < EnemySpawnNodes.Num())
		{
			RandomIndex = FMath::RandRange(0, EnemySpawnNodes.Num() - 1);

			bool bFoundSameIndex = false;
			for (int32 j = 0; j < OutNodes.Num(); j++)
			{
				if (EnemySpawnNodes[RandomIndex] == OutNodes[j])
				{
					bFoundSameIndex = true;
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

			IterateCount++;
		}

		// "Select" the node by adding it to the array
		OutNodes.Add(EnemySpawnNodes[RandomIndex]);
	}
}

bool ARBShooterGameModeBase::CanEnemyNodeBeSpawned(AEnemySpawnNode* SpawnNode)
{
	return true;
}

void ARBShooterGameModeBase::WaveTimerUpdate()
{
	StopWave();

	UE_LOG(LogTemp, Warning, TEXT("WaveTimerUpdate"));
}

void ARBShooterGameModeBase::BurstTimerUpdate()
{
	DoWaveBurst(NextBurstNumEnemies);

	UE_LOG(LogTemp, Warning, TEXT("BurstTimerUpdate"));
}
