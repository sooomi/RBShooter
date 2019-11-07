// Copyright (c) 2019 PSQ Grupp 4 =)


#include "HighscoreHandler.h"

UHighscoreHandler::UHighscoreHandler()
{
	MaxHighScoreEntries = 5;

	ScoreValues.SetNumZeroed(MaxHighScoreEntries);

	UE_LOG(LogTemp, Warning, TEXT("scorevalues size %i"), ScoreValues.Num());
}

UHighscoreHandler::~UHighscoreHandler()
{
}
