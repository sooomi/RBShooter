// Copyright (c) 2019 PSQ Grupp 4 =)


#include "CombatPowerManager.h"
#include "TimerManager.h"

// Sets default values
ACombatPowerManager::ACombatPowerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxTime = 10.0f;
	
	NumRedBombPoints = 0;
	NumBlueBombPoints = 0;
	MaxNumBombPoints = 3;

	NumRedTimerIncreases = 0;
	NumBlueTimerIncreases = 0;
}

// Called when the game starts or when spawned
void ACombatPowerManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACombatPowerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ACombatPowerManager::GetTimeLeft(EColorTypes ColorType)
{
	FTimerHandle& RelevantTimerHandle = GetTimerHandleFromColor(ColorType);

	float Elapsed = GetWorldTimerManager().GetTimerElapsed(RelevantTimerHandle);
	float TimerRate = GetWorldTimerManager().GetTimerRate(RelevantTimerHandle);

	float TimeLeft = TimerRate - Elapsed;

	return TimeLeft;
}

float ACombatPowerManager::GetTimeLeftPercentage(EColorTypes ColorType)
{
	float TimeLeft = GetTimeLeft(ColorType);

	float TimeLeftPercentage = TimeLeft / MaxTime;

	return TimeLeftPercentage;
}

bool ACombatPowerManager::HasBombPoint(EColorTypes ColorType, int32 Amount)
{
	if (GetPointValueFromColor(ColorType) >= Amount)
	{
		return true;
	}

	return false;
}

bool ACombatPowerManager::IncreaseTimer(float Amount, EColorTypes ColorType)
{
	if (ColorType == EColorTypes::CT_Red)
	{
		NumRedTimerIncreases++;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		NumBlueTimerIncreases++;
	}

	// Get the appropriate timer handle from type
	FTimerHandle& RelevantTimerHandle = GetTimerHandleFromColor(ColorType);

	// Get if timer was active
	bool bTimerActive = GetWorldTimerManager().IsTimerActive(RelevantTimerHandle);

	// Calculate new time for timer based on current elapsed time
	float Elapsed = FMath::Max(GetWorldTimerManager().GetTimerElapsed(RelevantTimerHandle), 0.0f);
	float TimerRate = FMath::Max(GetWorldTimerManager().GetTimerRate(RelevantTimerHandle), 0.0f);
	float NewTime = (TimerRate - Elapsed) + Amount;

	// If new time exceeds max time, deduct MaxTime and add one bomb point
	if (NewTime >= MaxTime)
	{
		NewTime -= MaxTime;
		AddBombPoint(ColorType);
	}

	// Set the timer
	UE_LOG(LogTemp, Warning, TEXT("NewTime %f"), NewTime);
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("EnemyKillTimerUpdate"), ColorType);
	GetWorldTimerManager().SetTimer(RelevantTimerHandle, TimerDel, NewTime, false, -1.0f);

	if (bTimerActive)
	{
		OnTimerUpdated(ColorType);
	}
	else
	{
		OnTimerStarted(ColorType);
	}

	return bTimerActive;
}

bool ACombatPowerManager::AddBombPoint(EColorTypes ColorType)
{
	int32& PointValue = GetPointValueFromColor(ColorType);
	if (PointValue < MaxNumBombPoints)
	{
		PointValue = FMath::Clamp(++PointValue, 0, MaxNumBombPoints);
		OnBombPointAdded(ColorType, PointValue);

		return true;
	}

	return false;
}

bool ACombatPowerManager::RemoveBombPoint(EColorTypes ColorType)
{
	int32& PointValue = GetPointValueFromColor(ColorType);
	if (PointValue > 0)
	{
		PointValue = FMath::Clamp(--PointValue, 0, MaxNumBombPoints);
		OnBombPointRemoved(ColorType, PointValue);

		return true;
	}

	return false;
}

void ACombatPowerManager::EnemyKillTimerUpdate(EColorTypes ColorType)
{
	if (ColorType == EColorTypes::CT_Red)
	{
		NumRedTimerIncreases = 0;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		NumBlueTimerIncreases = 0;
	}

	OnTimerEnded(ColorType);
}

FTimerHandle& ACombatPowerManager::GetTimerHandleFromColor(EColorTypes ColorType)
{
	if (ColorType == EColorTypes::CT_Red)
	{
		return EnemyKillTimerHandleRed;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		return EnemyKillTimerHandleBlue;
	}

	return EnemyKillTimerHandleRed;
}

int32& ACombatPowerManager::GetPointValueFromColor(EColorTypes ColorType)
{
	if (ColorType == EColorTypes::CT_Red)
	{
		return NumRedBombPoints;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		return NumBlueBombPoints;
	}

	return NumRedBombPoints;
}

