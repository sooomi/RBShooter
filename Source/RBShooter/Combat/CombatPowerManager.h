// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameUtility.h"
#include "CombatPowerManager.generated.h"

UCLASS()
class RBSHOOTER_API ACombatPowerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombatPowerManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category="Timer Management")
	float GetTimeLeft(EColorTypes EnemyType);

	UFUNCTION(BlueprintPure, Category = "Timer Management")
	float GetTimeLeftPercentage(EColorTypes EnemyType);

	/* Increases the timer for specified enemy color by Amount. Starts timer if not started. @return True if timer was started, false if only incremented. */
	UFUNCTION(BlueprintCallable, Category="Timer Management")
	bool IncreaseTimer(float Amount, EColorTypes EnemyType);

	/* Adds 1 Bomb Point. @return True if added, false if bomb point amount was at max */
	UFUNCTION(BlueprintCallable, Category = "Bomb Point")
	bool AddBombPoint();

	/* Removes 1 Bomb Point. @return True if removed, false if bomb point amount was already 0 */
	UFUNCTION(BlueprintCallable, Category = "Bomb Point")
	bool RemoveBombPoint();

	/* Called when IncreaseTimer is called. */
	UFUNCTION(BlueprintImplementableEvent, Category="Timer Callbacks")
	void OnTimerStarted(EColorTypes EnemyType);

	/* Called when the current streak timer runs out. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Timer Callbacks")
	void OnTimerEnded(EColorTypes EnemyType);

	/* Called when a Bomb Point is added. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Timer Callbacks")
	void OnBombPointAdded(UPARAM(DisplayName = "Number of Bomb Points") int32 NumPoints);

	/* Called when a Bomb Point is removed. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Timer Callbacks")
	void OnBombPointRemoved(UPARAM(DisplayName = "Number of Bomb Points") int32 NumPoints);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "Max Number of Bomb Points", Category = "Combat Values")
	int32 MaxNumBombPoints;

	UPROPERTY(BlueprintReadOnly, DisplayName="Number of Bomb Points", Category="Combat Values")
	int32 NumBombPoints;

	UPROPERTY(BlueprintReadOnly, DisplayName = "Number of Red Timer Increases", Category = "Combat Values")
	int32 NumRedTimerIncreases;

	UPROPERTY(BlueprintReadOnly, DisplayName = "Number of Blue Timer Increases", Category = "Combat Values")
	int32 NumBlueTimerIncreases;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat Values")
	float MaxTime;

private:

	FTimerHandle EnemyKillTimerHandleRed;

	FTimerHandle EnemyKillTimerHandleBlue;

private:

	UFUNCTION()
	void EnemyKillTimerUpdate(EColorTypes EnemyType);

};
