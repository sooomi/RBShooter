// Copyright (c) 2019 PSQ Grupp 4 =)


#include "RBShooterGameModeBase.h"
#include "Level/EnemySpawnNode.h"

ARBShooterGameModeBase::ARBShooterGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CurrentWave = 0;
	CurrentWaveBurst = 0;
}

ARBShooterGameModeBase::~ARBShooterGameModeBase()
{

}

void ARBShooterGameModeBase::Tick(float DeltaSeconds)
{
	// TODO enable tick in constructor before using this
}

EEnemySpawnTypes ARBShooterGameModeBase::GetRandomEnemySpawnType()
{
	return (EEnemySpawnTypes)FMath::RandRange(1, (int32)EEnemySpawnTypes::EST_COUNT - 1);
}

TArray<AActor*>& ARBShooterGameModeBase::GetRandomEnemySpawnNodes(int32 NumNodes)
{
	SelectedEnemySpawnNodes.Reset();

	// Cant randomize more nodes than existing
	NumNodes = FMath::Clamp(NumNodes, 0, EnemySpawnNodes.Num());

	// Early exit - number of nodes to be randomized is equal to number of existing nodes (no randomization needed)
	if (NumNodes == EnemySpawnNodes.Num())
	{
		SelectedEnemySpawnNodes = EnemySpawnNodes;
		return SelectedEnemySpawnNodes;
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
			for (int32 j = 0; j < SelectedEnemySpawnNodes.Num(); j++)
			{
				if (EnemySpawnNodes[RandomIndex] == SelectedEnemySpawnNodes[j])
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
		SelectedEnemySpawnNodes.Add(EnemySpawnNodes[RandomIndex]);
	}

	return SelectedEnemySpawnNodes;
}

bool ARBShooterGameModeBase::CanEnemyNodeBeSpawned(AEnemySpawnNode* SpawnNode)
{
	return true;
}
