// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HighscoreSaveGame.h"
#include "GameUtility.h"
#include "HighscoreHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FScorePostedDelegate, int32, Placement, FHighScoreEntry, ScoreEntry);

/**
 * 
 */
UCLASS()
class RBSHOOTER_API UHighscoreHandler : public UObject
{
	GENERATED_BODY()

public:

	UHighscoreHandler();
	~UHighscoreHandler();

	void Load();
	void Save();

public:

	/* Checks if ScoreValue qualifies to be on the score board. @return Placement on the board if qualified, starting from 0. -1 if not qualified. */
	UFUNCTION(BlueprintCallable, Category="HighScore")
	int32 CheckHighScoreEligibility(int32 ScoreValue);

	/* Submit score to the board. If eligible, update the list of entries. */
	UFUNCTION(BlueprintCallable, Category = "HighScore")
	void PostScore(int32 ScoreValue, const FName& PlayerName);

public:

	UPROPERTY(VisibleAnywhere, Category = "Basic")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "Basic")
	uint32 UserIndex;

	UPROPERTY(EditAnywhere, Category="HighScore")
	int32 MaxHighScoreEntries;

	UPROPERTY(BlueprintReadOnly, Category = "HighScore")
	TArray<FHighScoreEntry> ScoreEntries;

	UPROPERTY(BlueprintAssignable, Category="HighScore")
	FScorePostedDelegate OnScorePosted;

private:

	UHighscoreSaveGame* SaveGameInstance;

	void PushScoreEntriesDown(int32 StartingIndex, int32 Amount);
	
};
