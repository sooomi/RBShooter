// Copyright (c) 2019 PSQ Grupp 4 =)


#include "CombatPowerManager.h"
#include "TimerManager.h"

// Sets default values
ACombatPowerManager::ACombatPowerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxTime = 10.0f;
	NumBombPoints = 0;
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

float ACombatPowerManager::GetTimeLeft(EColorTypes EnemyType)
{
	float Elapsed = 0.0f;
	float TimerRate = 0.0f;
	if (EnemyType == EColorTypes::CT_Red)
	{
		Elapsed = GetWorldTimerManager().GetTimerElapsed(EnemyKillTimerHandleRed);
		TimerRate = GetWorldTimerManager().GetTimerRate(EnemyKillTimerHandleRed);
	}
	else if (EnemyType == EColorTypes::CT_Blue)
	{
		Elapsed = GetWorldTimerManager().GetTimerElapsed(EnemyKillTimerHandleBlue);
		TimerRate = GetWorldTimerManager().GetTimerRate(EnemyKillTimerHandleBlue);
	}

	float TimeLeft = TimerRate - Elapsed;

	return TimeLeft;
}

float ACombatPowerManager::GetTimeLeftPercentage(EColorTypes EnemyType)
{
	float TimeLeft = GetTimeLeft(EnemyType);

	float TimeLeftPercentage = TimeLeft / MaxTime;

	return TimeLeftPercentage;
}

bool ACombatPowerManager::IncreaseTimer(float Amount, EColorTypes EnemyType)
{
	// Set the appropriate timer handle ptr depending on type
	FTimerHandle* TimerHandleToUse = nullptr;

	if (EnemyType == EColorTypes::CT_Red)
	{
		TimerHandleToUse = &EnemyKillTimerHandleRed;
		NumRedTimerIncreases++;
	}
	else if (EnemyType == EColorTypes::CT_Blue)
	{
		TimerHandleToUse = &EnemyKillTimerHandleBlue;
		NumBlueTimerIncreases++;
	}

	// Get if timer was active
	bool bTimerActive = GetWorldTimerManager().IsTimerActive(*TimerHandleToUse);

	// Calculate new time for timer based on current elapsed time
	float Elapsed = FMath::Max(GetWorldTimerManager().GetTimerElapsed(*TimerHandleToUse), 0.0f);
	float TimerRate = FMath::Max(GetWorldTimerManager().GetTimerRate(*TimerHandleToUse), 0.0f);
	float NewTime = (TimerRate - Elapsed) + Amount;

	// If new time exceeds max time, deduct MaxTime and add one bomb point
	if (NewTime >= MaxTime)
	{
		NewTime -= MaxTime;
		AddBombPoint();
	}

	// Set the timer
	UE_LOG(LogTemp, Warning, TEXT("NewTime %f"), NewTime);
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("EnemyKillTimerUpdate"), EnemyType);
	GetWorldTimerManager().SetTimer(*TimerHandleToUse, TimerDel, NewTime, false, -1.0f);

	if (bTimerActive)
	{
		OnTimerStarted(EnemyType);
	}

	return bTimerActive;
}

bool ACombatPowerManager::AddBombPoint()
{
	if (NumBombPoints < MaxNumBombPoints)
	{
		NumBombPoints = FMath::Clamp(++NumBombPoints, 0, MaxNumBombPoints);
		OnBombPointAdded(NumBombPoints);

		return true;
	}

	return false;
}

bool ACombatPowerManager::RemoveBombPoint()
{
	if (NumBombPoints > 0)
	{
		NumBombPoints = FMath::Clamp(--NumBombPoints, 0, MaxNumBombPoints);
		OnBombPointRemoved(NumBombPoints);

		return true;
	}

	return false;
}

void ACombatPowerManager::EnemyKillTimerUpdate(EColorTypes EnemyType)
{
	if (EnemyType == EColorTypes::CT_Red)
	{
		NumRedTimerIncreases = 0;
	}
	else if (EnemyType == EColorTypes::CT_Blue)
	{
		NumBlueTimerIncreases = 0;
	}

	OnTimerEnded(EnemyType);
}

