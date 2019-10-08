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
	FTimerHandle& RelevantTimerHandle = GetTimerHandleFromColor(EnemyType);

	float Elapsed = GetWorldTimerManager().GetTimerElapsed(RelevantTimerHandle);
	float TimerRate = GetWorldTimerManager().GetTimerRate(RelevantTimerHandle);

	float TimeLeft = TimerRate - Elapsed;

	return TimeLeft;
}

float ACombatPowerManager::GetTimeLeftPercentage(EColorTypes EnemyType)
{
	float TimeLeft = GetTimeLeft(EnemyType);

	float TimeLeftPercentage = TimeLeft / MaxTime;

	return TimeLeftPercentage;
}

bool ACombatPowerManager::HasBombPoint(int32 Amount)
{
	if (NumBombPoints >= Amount)
	{
		return true;
	}

	return false;
}

bool ACombatPowerManager::IncreaseTimer(float Amount, EColorTypes EnemyType)
{
	if (EnemyType == EColorTypes::CT_Red)
	{
		NumRedTimerIncreases++;
	}
	else if (EnemyType == EColorTypes::CT_Blue)
	{
		NumBlueTimerIncreases++;
	}

	// Get the appropriate timer handle from type
	FTimerHandle& RelevantTimerHandle = GetTimerHandleFromColor(EnemyType);

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
		AddBombPoint();
	}

	// Set the timer
	UE_LOG(LogTemp, Warning, TEXT("NewTime %f"), NewTime);
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("EnemyKillTimerUpdate"), EnemyType);
	GetWorldTimerManager().SetTimer(RelevantTimerHandle, TimerDel, NewTime, false, -1.0f);

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

