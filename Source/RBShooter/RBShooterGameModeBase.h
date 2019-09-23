// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RBShooterGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EEnemySpawnTypes : uint8
{
	EST_Random = 0 UMETA(DisplayName = "Random Enemy"),
	EST_Red UMETA(DisplayName = "Red Enemy"),
	EST_Blue UMETA(DisplayName = "Blue Enemy"),

	EST_COUNT
};

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
};
