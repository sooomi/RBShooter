// Copyright (c) 2019 PSQ Grupp 4 =)


#include "RBShooterGameInstance.h"
#include "HighscoreHandler.h"

URBShooterGameInstance::URBShooterGameInstance()
{
	HighScoreHandler = nullptr;
}

URBShooterGameInstance::~URBShooterGameInstance()
{
}

void URBShooterGameInstance::Init()
{
	UGameInstance::Init();

	HighScoreHandler = NewObject<UHighscoreHandler>(this, UHighscoreHandler::StaticClass());
	HighScoreHandler->Load();
}
