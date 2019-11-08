// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HighscoreHandler.generated.h"


USTRUCT(BlueprintType)
struct FHighScoreEntry
{
	GENERATED_BODY()

	FHighScoreEntry()
	{
		Value = 0;
		PlayerName = "Empty";
	}

	UPROPERTY(BlueprintReadOnly, Category = "FHighScoreEntry")
	int32 Value;

	UPROPERTY(BlueprintReadOnly, Category = "FHighScoreEntry")
	FName PlayerName;
};

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

public:

	/* Checks if ScoreValue qualifies to be on the score board. @return Placement on the board if qualified, starting from 0. -1 if not qualified. */
	UFUNCTION(BlueprintCallable, Category="HighScore")
	int32 CheckHighScoreEligibility(int32 ScoreValue);

	/* Submit score to the board. If eligible, update the list of entries. */
	UFUNCTION(BlueprintCallable, Category = "HighScore")
	void PostScore(int32 ScoreValue, const FName& PlayerName);

public:

	UPROPERTY(EditAnywhere, Category="HighScore")
	int32 MaxHighScoreEntries;

	UPROPERTY(BlueprintReadOnly, Category = "HighScore")
	TArray<FHighScoreEntry> ScoreEntries;

	UPROPERTY(BlueprintAssignable, Category="HighScore")
	FScorePostedDelegate OnScorePosted;

private:

	void PushScoreEntriesDown(int32 StartingIndex, int32 Amount);
	
};
