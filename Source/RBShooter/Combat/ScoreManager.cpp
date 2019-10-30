// Copyright (c) 2019 PSQ Grupp 4 =)


#include "ScoreManager.h"

// Sets default values
AScoreManager::AScoreManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ScoreStreakRed = 0;
	ScoreStreakBlue = 0;

	ScoreStreakTimeRed = 0.0f;
	ScoreStreakTimeBlue = 0.0f;

	MaxScoreStreakCount = 5;
}

// Called when the game starts or when spawned
void AScoreManager::BeginPlay()
{
	Super::BeginPlay();

}

float AScoreManager::GetScoreStreakAmountFraction(EColorTypes ColorType)
{
	if (ColorType == EColorTypes::CT_Red)
	{
		return (float)ScoreStreakRed / (float)MaxScoreStreakCount;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		return (float)ScoreStreakBlue / (float)MaxScoreStreakCount;
	}

	return 0.0f;
}

int32 AScoreManager::GetScoreStreak(EColorTypes ColorType)
{
	if (ColorType == EColorTypes::CT_Red)
	{
		return ScoreStreakRed;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{

		return ScoreStreakBlue;
	}

	return 0;
}

bool AScoreManager::IsScoreStreakActive(EColorTypes ColorType)
{
	if (ColorType == EColorTypes::CT_Red)
	{
		return ScoreStreakTimeRed > 0.0f;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		return ScoreStreakTimeBlue > 0.0f;
	}

	return false;
}

void AScoreManager::UpdateScoreStreak(EColorTypes ColorType, int32 Amount /* = 1*/, float NewTime /* = 5.0f*/)
{
	bool bWasStreakStarted = false;

	if (ColorType == EColorTypes::CT_Red)
	{
		if (ScoreStreakTimeRed <= 0.0f)
		{
			bWasStreakStarted = true;
		}

		ScoreStreakRed = FMath::Clamp(ScoreStreakRed += Amount, 0, MaxScoreStreakCount);
		ScoreStreakTimeRed = NewTime;
		
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		if (ScoreStreakTimeBlue <= 0.0f)
		{
			bWasStreakStarted = true;
		}

		ScoreStreakBlue = FMath::Clamp(ScoreStreakBlue += Amount, 0, MaxScoreStreakCount);
		ScoreStreakTimeBlue = NewTime;
	}

	OnScoreStreakUpdated(ColorType, Amount, NewTime, bWasStreakStarted);
}

void AScoreManager::CancelScoreStreak(EColorTypes ColorType)
{
	if (ColorType == EColorTypes::CT_Red)
	{
		ScoreStreakTimeRed = 0.0f;
		ScoreStreakRed = 0;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		ScoreStreakTimeBlue = 0.0f;
		ScoreStreakBlue = 0;
	}
}

// Called every frame
void AScoreManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateScoreStreak(ScoreStreakRed, ScoreStreakTimeRed, DeltaTime);
	UpdateScoreStreak(ScoreStreakBlue, ScoreStreakTimeBlue, DeltaTime);
}

void AScoreManager::UpdateScoreStreak(int32& StreakValue, float& TimeValue, float DeltaTime)
{
	if (TimeValue > 0.0f)
	{
		TimeValue -= DeltaTime;

		if (TimeValue <= 0.0f)
		{
			TimeValue = 0.0f;
			StreakValue = 0;
		}
	}
}

