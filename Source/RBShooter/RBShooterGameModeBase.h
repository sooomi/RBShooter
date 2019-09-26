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

	/* Get randomly selected nodes from available nodes in the level */
	UFUNCTION(BlueprintCallable, Category = "Enemy Spawning")
	void GetRandomEnemySpawnNodes(UPARAM(DisplayName="Number of Nodes") int32 NumNodes, TArray<AActor*>& OutNodes);

	/* Start a wave if not currently in progress. @return True if wave was started */
	UFUNCTION(BlueprintCallable, Category="Wave Management")
	bool StartWave(int32 NumberOfBursts, float BurstDuration, float BurstPauseDuration);

	/* Stops a wave and its timers. @return True if wave was stopped */
	UFUNCTION(BlueprintCallable, Category="Wave Management")
	bool StopWave();

	/* Starts a burst timer if wave is in progress. @param1 How long until next burst @param2 How long the burst should last */
	UFUNCTION(BlueprintCallable, Category="Wave Management")
	bool StartBurst(UPARAM(DisplayName = "Number of Enemies to Spawn") int32 NumEnemiesToSpawn);

	/* Stops a burst timer. @return True if burst was stopped */
	UFUNCTION(BlueprintCallable, Category = "Wave Management")
	bool StopBurst();

	/* When a wave is completed */
	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Management")
	void OnNextWaveReady(int32 WaveNumber);

	/* When a burst is completed. A wave can consist of several bursts. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Management")
	void OnNextBurstReady(int32 WaveNumber, int32 BurstNumber);

	/* When a wave is completed */
	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Management")
	void OnWaveCompleted(int32 WaveNumber, float TimeLeft);

	/* When a burst is completed. A wave can consist of several bursts. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Management")
	void OnBurstCompleted(int32 WaveNumber, int32 BurstNumber);

	UFUNCTION(BlueprintCallable, Category="Wave Management")
	bool StartGameIfPossible(float TimeUntilFirstBurst = 0.0f);

	UFUNCTION(BlueprintCallable, Category="Wave Management")
	void ResetToDefault();

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
	FTimerHandle BurstSpawnTimerHandle;

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

	void ActivateNextEnemyNode();
	void WaveTimerUpdate();
	void BurstTimerUpdate();
	void BurstSpawnTimerUpdate();
	void FirstBurstDelayTimerUpdate();

	void ResetWaveVariables();

private:

	float CurrentBurstDuration;
	float CurrentBurstPauseDuration;
	float CurrentWaveDuration;

	float CurrentSpawnInterval;

	int32 NumNextBurstEnemies;
	int32 NumCurrentEnemiesPendingSpawn;

	FTimerHandle InitialWaveBurstTimer;
};
