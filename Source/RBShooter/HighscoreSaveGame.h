// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameUtility.h"
#include "HighscoreSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RBSHOOTER_API UHighscoreSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UHighscoreSaveGame();
	~UHighscoreSaveGame();

	UPROPERTY(VisibleAnywhere, Category="Save Data")
	TArray<FHighScoreEntry> HighScoreList;
	
};
