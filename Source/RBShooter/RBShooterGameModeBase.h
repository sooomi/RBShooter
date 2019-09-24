// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameUtility.h"
#include "RBShooterGameModeBase.generated.h"

class AEnemySpawnNode;

/**
 * 
 */
UCLASS()
class RBSHOOTER_API ARBShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ARBShooterGameModeBase();
	~ARBShooterGameModeBase();

	UFUNCTION(BlueprintCallable, Category="Enemy Spawning")
	EEnemySpawnTypes GetRandomEnemySpawnType();

	UPROPERTY(BlueprintReadWrite, Category="Enemy Spawning")
	TArray<AActor*> EnemySpawnNodes;

	UPROPERTY(BlueprintReadOnly, Category="Enemy Spawning")
	TArray<AActor*> SelectedEnemySpawnNodes;

public:

	UFUNCTION(BlueprintCallable, Category="Enemy Spawning")
	TArray<AActor*>& GetRandomEnemySpawnNodes(int32 NumNodes);

private:

	bool CanEnemyNodeBeSpawned(AEnemySpawnNode* SpawnNode);
};
