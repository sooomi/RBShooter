// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameUtility.h"
#include "ScoreManager.generated.h"

class AEnemy;
class APlayerCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FScoreChangedDelegate, float, CurrentScore, float, ScoreIncrease, EEnemyHitTypes, HitLocation, AEnemy*, Enemy);

UCLASS()
class RBSHOOTER_API UScoreManager : public UObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UScoreManager();

	UFUNCTION(BlueprintCallable, Category="Score Tier Bonus")
	void ActivateTierBonus(EColorTypes ColorType, EPowerTiesTypes PowerTier, float IncreasePerTier, float BonusDuration);

	UFUNCTION(BlueprintCallable, Category = "Score BlueprintImplement")
	void UpdateScoreTimer(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category="Score BlueprintImplement")
	void HandleEnemyDeath(AEnemy* Enemy, AActor* Killer);

	UFUNCTION(BlueprintCallable, Category="Score BlueprintImplement")
	void HandleDamageDealt(float Damage, AActor* DamageTarget, EEnemyHitTypes HitLocation);

	/* Returns score streak amount fraction for color */
	UFUNCTION(BlueprintPure, Category="Score Streak")
	float GetScoreStreakAmountFraction(EColorTypes ColorType);

	/* Returns score streak amount for color */
	UFUNCTION(BlueprintPure, Category="Score Streak")
	int32 GetScoreStreak(EColorTypes ColorType);

	/* Return true if score streak color is active */
	UFUNCTION(BlueprintPure, Category = "Score Streak")
	bool IsScoreStreakActive(EColorTypes ColorType);

	/* Event for when score streak is updated */
	UFUNCTION(BlueprintImplementableEvent, Category = "Score Streak")
	void OnScoreStreakUpdated(EColorTypes ColorType, int32 Amount, float NewTime, bool bWasStarted);

public:

	UFUNCTION(BlueprintPure, Category = "Score Streak")
	float GetScoreStreakMultiplier(EColorTypes ColorType);

	UPROPERTY(BlueprintAssignable, Category="Score Event")
	FScoreChangedDelegate OnScoreChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Score Streak")
	int32 MaxScoreStreakCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score Streak")
	float BaseScore;

	UPROPERTY(BlueprintReadOnly, Category = "Score Streak")
	float CurrentScore;

private:

	int32 ScoreStreakRed;
	int32 ScoreStreakBlue;

	FColorFloatGroup ScoreStreakTime;
	FColorFloatGroup ScoreTierBonus;

	FTimerHandle ScoreTierBonusTimerHandle;

private:

	void UpdateScoreStreak(EColorTypes ColorType, int32 Amount = 1, float NewTime = 5.0f);
	void CancelScoreStreak(EColorTypes ColorType);

	void UpdateStreakTime(int32& StreakValue, float& TimeValue, float DeltaTime);

	UFUNCTION()
	void ScoreTierBonusUpdate(EColorTypes ColorType);

};
