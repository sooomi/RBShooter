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

	UFUNCTION(BlueprintImplementableEvent, Category="Timer Callbacks")
	void OnTimerStarted(EColorTypes EnemyType);

	UFUNCTION(BlueprintImplementableEvent, Category = "Timer Callbacks")
	void OnTimerEnded(EColorTypes EnemyType);

	UFUNCTION(BlueprintImplementableEvent, Category = "Timer Callbacks")
	void OnBombPointAdded(UPARAM(DisplayName = "Number of Bomb Points") int32 NumPoints);

public:

	UPROPERTY(BlueprintReadOnly, DisplayName="Number of Bomb Points",Category="Combat Values")
	int32 NumBombPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat Values")
	float MaxTime;

private:

	FTimerHandle EnemyKillTimerHandleRed;
	FTimerHandle EnemyKillTimerHandleBlue;

private:

	UFUNCTION()
	void EnemyKillTimerUpdate(EColorTypes EnemyType);

	void AddBombPoint();

};
