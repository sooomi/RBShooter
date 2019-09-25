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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/* Get random type from enum */
	UFUNCTION(BlueprintCallable, Category="Enemy Spawning")
	EEnemySpawnTypes GetRandomEnemySpawnType();

	/* Get randomly selected nodes from available nodes in the level */
	UFUNCTION(BlueprintCallable, Category = "Enemy Spawning")
	void GetRandomEnemySpawnNodes(UPARAM(DisplayName="Number of Nodes") int32 NumNodes, TArray<AActor*>& OutNodes);

	/* Start a wave if not currently in progress. @return True if wave was started */
	UFUNCTION(BlueprintCallable, Category="Wave Management")
	bool StartWave(float WaveDuration = 30.0f, float BurstInterval = 10.0f, UPARAM(DisplayName = "Number Of Enemies To Spawn On First Burst") int32 FirstBurstNumEnemies = 5);

	/* Stops a wave and its timers. @return True if wave was stopped */
	UFUNCTION(BlueprintCallable, Category="Wave Management")
	bool StopWave();

	/* Starts a burst timer if wave is in progress. */
	UFUNCTION(BlueprintCallable, Category="Wave Management")
	bool StartBurst(float BurstInterval, UPARAM(DisplayName = "Number of Enemies to Spawn") int32 NumEnemiesToSpawn);

	/* Stops a burst timer. @return True if burst was stopped */
	UFUNCTION(BlueprintCallable, Category = "Wave Management")
	bool StopBurst();

	/* Spawn enemies from available nodes in the level */
	UFUNCTION(BlueprintCallable, Category="Wave Management")
	bool DoWaveBurst(UPARAM(DisplayName = "Number of Enemies to Spawn") int32 NumEnemiesToSpawn);

	/* When a wave is completed */
	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Management")
	void OnWaveCompleted(int32 WaveNumber, float TimeLeft);

	/* When a burst is completed. A wave can consist of several bursts. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Management")
	void OnWaveBurst(int32 WaveNumber, int32 BurstNumber, int32 NumEnemiesSpawned);

	UFUNCTION(BlueprintCallable, Category="Wave Management")
	void ResetToDefault();

public:

	UPROPERTY(BlueprintReadWrite, Category = "Enemy Spawning")
	TArray<AActor*> EnemySpawnNodes;

	UPROPERTY(BlueprintReadOnly, Category="Wave Management")
	FTimerHandle WaveTimerHandle;

	UPROPERTY(BlueprintReadOnly, Category = "Wave Management")
	FTimerHandle BurstTimerHandle;

	UPROPERTY(BlueprintReadWrite, Category="Wave Management")
	float WaveInterval;

	UPROPERTY(BlueprintReadOnly, Category = "Wave Management")
	int32 CurrentWave;

	UPROPERTY(BlueprintReadOnly, Category = "Wave Management")
	int32 CurrentWaveBurst;

	UPROPERTY(BlueprintReadOnly, Category="Wave Management")
	bool bWaveActive;

private:

	bool CanEnemyNodeBeSpawned(AEnemySpawnNode* SpawnNode);

	void WaveTimerUpdate();
	void BurstTimerUpdate();

private:

	int32 NextBurstNumEnemies;
};
