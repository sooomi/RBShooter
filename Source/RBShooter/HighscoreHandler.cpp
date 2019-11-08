// Copyright (c) 2019 PSQ Grupp 4 =)


#include "HighscoreHandler.h"

UHighscoreHandler::UHighscoreHandler()
{
	MaxHighScoreEntries = 5;

	ScoreEntries.SetNum(MaxHighScoreEntries);
}

UHighscoreHandler::~UHighscoreHandler()
{
}

int32 UHighscoreHandler::CheckHighScoreEligibility(int32 ScoreValue)
{
	for (int32 i = 0; i < ScoreEntries.Num(); i++)
	{
		if (ScoreValue >= ScoreEntries[i].Value)
		{
			return i;
		}
	}

	return -1;
}

void UHighscoreHandler::PostScore(int32 ScoreValue, const FName& PlayerName)
{
	int32 ScoreEligibility = CheckHighScoreEligibility(ScoreValue);

	if (ScoreEligibility >= 0)
	{
		// Push down all entries, starting from ScoreEligibility position
		PushScoreEntriesDown(ScoreEligibility, 1);

		ScoreEntries[ScoreEligibility].Value = ScoreValue;
		ScoreEntries[ScoreEligibility].PlayerName = PlayerName;

		OnScorePosted.Broadcast(ScoreEligibility, ScoreEntries[ScoreEligibility]);
	}
}

void UHighscoreHandler::PushScoreEntriesDown(int32 StartingIndex, int32 Amount)
{
	const int32 LastIndex = ScoreEntries.Num() - 1;

	if (StartingIndex < LastIndex)
	{
		for (int32 i = LastIndex; i > StartingIndex; i--)
		{
			int32 IndexAbove = i - 1;
			ScoreEntries.Swap(i, IndexAbove);
		}

		// Reset element at StartingIndex
		ScoreEntries[StartingIndex].Value = 0;
		ScoreEntries[StartingIndex].PlayerName = "no_player";
	}
}
