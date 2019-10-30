// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameUtility.h"
#include "ScoreManager.generated.h"

UCLASS()
class RBSHOOTER_API AScoreManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoreManager();

	/* Returns score streak amount fraction for color */
	UFUNCTION(BlueprintPure, Category="Score Streak")
	float GetScoreStreakAmountFraction(EColorTypes ColorType);

	/* Returns score streak amount for color */
	UFUNCTION(BlueprintPure, Category="Score Streak")
	int32 GetScoreStreak(EColorTypes ColorType);

	/* Return true if score streak color is active */
	UFUNCTION(BlueprintPure, Category = "Score Streak")
	bool IsScoreStreakActive(EColorTypes ColorType);

	/* Update/Start score streak */
	UFUNCTION(BlueprintCallable, Category="Score Streak")
	void UpdateScoreStreak(EColorTypes ColorType, int32 Amount = 1, float NewTime = 5.0f);

	/* Cancel active score streak */
	UFUNCTION(BlueprintCallable, Category = "Score Streak")
	void CancelScoreStreak(EColorTypes ColorType);

	/* Event for when score streak is updated */
	UFUNCTION(BlueprintImplementableEvent, Category = "Score Streak")
	void OnScoreStreakUpdated(EColorTypes ColorType, int32 Amount, float NewTime, bool bWasStarted);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Score Streak")
	int32 MaxScoreStreakCount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	int32 ScoreStreakRed;
	int32 ScoreStreakBlue;

	float ScoreStreakTimeRed;
	float ScoreStreakTimeBlue;

private:

	void UpdateScoreStreak(int32& StreakValue, float& TimeValue, float DeltaTime);

};
