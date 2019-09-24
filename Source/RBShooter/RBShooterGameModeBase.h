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

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category="Enemy Spawning")
	EEnemySpawnTypes GetRandomEnemySpawnType();

	UFUNCTION(BlueprintCallable, Category = "Enemy Spawning")
	TArray<AActor*>& GetRandomEnemySpawnNodes(int32 NumNodes);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Wave Management")
	bool DoWaveBurst(int32 NumberOfEnemiesToSpawn);

	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Management")
	void OnWaveCompleted(int32 WaveNumber, float TimeLeft);

	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Management")
	void OnWaveBurst(int32 WaveNumber, int32 BurstNumber);

public:

	UPROPERTY(BlueprintReadWrite, Category = "Enemy Spawning")
	TArray<AActor*> EnemySpawnNodes;

	UPROPERTY(BlueprintReadOnly, Category = "Enemy Spawning")
	TArray<AActor*> SelectedEnemySpawnNodes;

	UPROPERTY(BlueprintReadOnly, Category="Wave Management")
	FTimerHandle WaveTimerHandle;

	UPROPERTY(BlueprintReadOnly, Category = "Wave Management")
	FTimerHandle BurstTimerHandle;

	UPROPERTY(BlueprintReadOnly, Category = "Wave Management")
	int32 CurrentWave;

	UPROPERTY(BlueprintReadOnly, Category = "Wave Management")
	int32 CurrentWaveBurst;

private:

	bool CanEnemyNodeBeSpawned(AEnemySpawnNode* SpawnNode);
};
