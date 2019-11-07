// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RBShooterGameInstance.generated.h"

class UHighscoreHandler;

/**
 * 
 */
UCLASS()
class RBSHOOTER_API URBShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	URBShooterGameInstance();
	~URBShooterGameInstance();

	virtual void Init() override;

public:

	UPROPERTY(BlueprintReadOnly, Category="HighScore")
	UHighscoreHandler* HighScoreHandler;

private:

	
};
