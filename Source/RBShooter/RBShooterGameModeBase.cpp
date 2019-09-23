// Copyright (c) 2019 PSQ Grupp 4 =)


#include "RBShooterGameModeBase.h"

ARBShooterGameModeBase::ARBShooterGameModeBase()
{

}

ARBShooterGameModeBase::~ARBShooterGameModeBase()
{

}

EEnemySpawnTypes ARBShooterGameModeBase::GetRandomEnemySpawnType()
{
	return (EEnemySpawnTypes)FMath::RandRange(1, (int32)EEnemySpawnTypes::EST_COUNT);
}
