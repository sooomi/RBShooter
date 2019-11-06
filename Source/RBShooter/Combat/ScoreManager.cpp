// Copyright (c) 2019 PSQ Grupp 4 =)


#include "ScoreManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/PlayerCharacter.h"
#include "Enemy/Enemy.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
UScoreManager::UScoreManager()
{
	ScoreStreakRed = 0;
	ScoreStreakBlue = 0;

	ScoreStreakTime.Red = 0.0f;
	ScoreStreakTime.Blue = 0.0f;

	MaxScoreStreakCount = 5;
	CurrentScore = 0.0f;
	BaseScore = 1.0f;
}

void UScoreManager::ActivateTierBonus(EColorTypes ColorType, EPowerTiesTypes PowerTier, float IncreasePerTier, float BonusDuration)
{
	float TierMultiplier = 0.0f;

	switch (PowerTier)
	{
	case EPowerTiesTypes::PTT_Tier1:
		TierMultiplier = 1.0f;
		break;
	case EPowerTiesTypes::PTT_Tier2:
		TierMultiplier = 2.0f;
		break;
	case EPowerTiesTypes::PTT_Tier3:
		TierMultiplier = 3.0f;
		break;
	}

	float FinalMultiplier = 1.0f + (IncreasePerTier * TierMultiplier);

	if (ColorType == EColorTypes::CT_Red)
	{
		ScoreTierBonus.Red = FinalMultiplier;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		ScoreTierBonus.Blue = FinalMultiplier;
	}

	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("ScoreTierBonusUpdate"), ColorType);
	
	GetWorld()->GetTimerManager().SetTimer(ScoreTierBonusTimerHandle, TimerDel, BonusDuration, false, -1.0f);
}

void UScoreManager::UpdateScoreTimer(float DeltaTime)
{
	UpdateStreakTime(ScoreStreakRed, ScoreStreakTime.Red, DeltaTime);
	UpdateStreakTime(ScoreStreakBlue, ScoreStreakTime.Blue, DeltaTime);
}

void UScoreManager::HandleEnemyDeath(AEnemy* Enemy, AActor* Killer)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(Killer);
	if (Player)
	{
		if (Enemy->EnemyType == EColorTypes::CT_Red)
		{
			CancelScoreStreak(EColorTypes::CT_Blue);
		}
		else if (Enemy->EnemyType == EColorTypes::CT_Blue)
		{
			CancelScoreStreak(EColorTypes::CT_Red);
		}

		UpdateScoreStreak(Enemy->EnemyType, 1, 5.0f);
	}
}

void UScoreManager::HandleDamageDealt(float Damage, AActor* DamageTarget, EEnemyHitTypes HitLocation)
{
	AEnemy* Enemy = Cast<AEnemy>(DamageTarget);
	if (DamageTarget)
	{
		float ScoreMultiplier = 1.0f;

		switch (HitLocation)
		{
		case EEnemyHitTypes::EHT_Head:
			ScoreMultiplier = 2.0f;
			break;
		case EEnemyHitTypes::EHT_Chest:
			ScoreMultiplier = 1.0f;
			break;
		case EEnemyHitTypes::EHT_LegLeft:
			ScoreMultiplier = 1.5f;
			break;
		case EEnemyHitTypes::EHT_LegRight:
			ScoreMultiplier = 1.5f;
			break;
		}

		float ScoreIncrease = (Damage * ScoreMultiplier) * BaseScore * GetScoreStreakMultiplier(Enemy->EnemyType);

		CurrentScore += ScoreIncrease;
		OnScoreChanged.Broadcast(CurrentScore, Enemy);
	}
}

float UScoreManager::GetScoreStreakAmountFraction(EColorTypes ColorType)
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

int32 UScoreManager::GetScoreStreak(EColorTypes ColorType)
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

bool UScoreManager::IsScoreStreakActive(EColorTypes ColorType)
{
	if (ColorType == EColorTypes::CT_Red)
	{
		return ScoreStreakTime.Red > 0.0f;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		return ScoreStreakTime.Blue > 0.0f;
	}

	return false;
}

float UScoreManager::GetScoreStreakMultiplier(EColorTypes ColorType)
{
	float ScoreStreakCount = (float)FMath::Max(GetScoreStreak(ColorType) - 1, 0);
	float ScoreStreakMultiplier = 1.0f + (0.2f * ScoreStreakCount);

	return ScoreStreakMultiplier;
}

void UScoreManager::UpdateScoreStreak(EColorTypes ColorType, int32 Amount /* = 1*/, float NewTime /* = 5.0f*/)
{
	bool bWasStreakStarted = false;

	if (ColorType == EColorTypes::CT_Red)
	{
		if (ScoreStreakTime.Red <= 0.0f)
		{
			bWasStreakStarted = true;
		}

		ScoreStreakRed = FMath::Clamp(ScoreStreakRed += Amount, 0, MaxScoreStreakCount);
		ScoreStreakTime.Red = NewTime;
		
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		if (ScoreStreakTime.Blue <= 0.0f)
		{
			bWasStreakStarted = true;
		}

		ScoreStreakBlue = FMath::Clamp(ScoreStreakBlue += Amount, 0, MaxScoreStreakCount);
		ScoreStreakTime.Blue = NewTime;
	}

	OnScoreStreakUpdated(ColorType, Amount, NewTime, bWasStreakStarted);
}

void UScoreManager::CancelScoreStreak(EColorTypes ColorType)
{
	if (ColorType == EColorTypes::CT_Red)
	{
		ScoreStreakTime.Red = 0.0f;
		ScoreStreakRed = 0;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		ScoreStreakTime.Blue = 0.0f;
		ScoreStreakBlue = 0;
	}
}

void UScoreManager::UpdateStreakTime(int32& StreakValue, float& TimeValue, float DeltaTime)
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

void UScoreManager::ScoreTierBonusUpdate(EColorTypes ColorType)
{
	if (ColorType == EColorTypes::CT_Red)
	{
		ScoreTierBonus.Red = 0.0f;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		ScoreTierBonus.Blue = 0.0f;
	}
}

