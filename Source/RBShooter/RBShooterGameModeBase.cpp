// Copyright (c) 2019 PSQ Grupp 4 =)


#include "RBShooterGameModeBase.h"

ARBShooterGameModeBase::ARBShooterGameModeBase()
{

}

ARBShooterGameModeBase::~ARBShooterGameModeBase()
{

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

		bool bIndexOk = false;
		while (!bIndexOk)
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
				bIndexOk = true;
			}
		}

		SelectedEnemySpawnNodes.Add(EnemySpawnNodes[RandomIndex]);
	}

	return SelectedEnemySpawnNodes;
}
