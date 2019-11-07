// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HighscoreHandler.generated.h"

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

	UPROPERTY(EditAnywhere, Category="HighScore")
	uint32 MaxHighScoreEntries;

private:

	TArray<uint32> ScoreValues;
	
};