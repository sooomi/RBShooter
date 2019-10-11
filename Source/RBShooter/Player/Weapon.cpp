// Copyright (c) 2019 PSQ Grupp 4 =)


#include "Weapon.h"
#include "PlayerCharacter.h"
#include "Combat/ProjectileBase.h"

#include "Kismet/GameplayStatics.h"
#include "Gameframework/Character.h"
#include "Engine/World.h"
#include "TimerManager.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	FireInterval = 0.2f;
	bCanFire = true;

	MaxChargeDuration = 3.0f;
	bIsChargingWeapon = false;

	DamageRed = 0.0f;
	DamageBlue = 0.0f;
	DamageGeneric = 0.0f;

	bWantsToFireMagnetProjectile = false;
	bFireImmediatelyMaxCharge = true;
	bHasReachedMaxCharge = false;

	CurrentChargeAmount = 0.0f;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	// TODO there should be a better way to get the player pointer
	// since this class instance is in a child hierarchy where parent is the player
	CachedPlayerOwner = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Setup rate of fire timer
	GetWorldTimerManager().SetTimer(RoFTimerHandle, this, &AWeapon::RateOfFireUpdate, FireInterval, true, 0.0f);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AWeapon::GetDamage(EColorTypes ColorType)
{
	if (ColorType == EColorTypes::CT_Red)
	{
		return DamageGeneric + DamageRed;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		return DamageGeneric + DamageBlue;
	}

	return DamageGeneric;
}

float AWeapon::GetProjectileSpeedMultiplier(EColorTypes ColorType)
{
	if (ColorType == EColorTypes::CT_Red)
	{
		return ProjectileMultiplier.ValueRed * ProjectileMultiplier.ValueGlobal;
	}
	else if (ColorType == EColorTypes::CT_Blue)
	{
		return ProjectileMultiplier.ValueBlue * ProjectileMultiplier.ValueGlobal;
	}

	return ProjectileMultiplier.ValueGlobal;
}

bool AWeapon::LoadProjectile(EColorTypes ProjectileType)
{
	if (!bIsChargingWeapon)
	{
		ProjectileTypeToFire = ProjectileType;
		SetChargeTimer();
		bIsChargingWeapon = true;

		OnProjectileLoad(ProjectileType);

		return true;
	}

	return false;
}

bool AWeapon::ReleaseProjectile(EColorTypes ProjectileType)
{
	if (bIsChargingWeapon && ProjectileType == ProjectileTypeToFire)
	{
		TryToFireProjectile(ProjectileTypeToFire);
		GetWorldTimerManager().PauseTimer(ChargeTimerHandle);
		bIsChargingWeapon = false;

		return true;
	}

	return false;
}

bool AWeapon::TryToFireProjectile(EColorTypes ProjectileType)
{
	// TODO check ammo amount
	if (bCanFire)
	{
		if (!bHasReachedMaxCharge)
		{
			CurrentChargeAmount = FMath::Max(0.0f, GetWorldTimerManager().GetTimerElapsed(ChargeTimerHandle));
		}

		OnFireProjectileConfirmed(ProjectileType, CurrentChargeAmount);
		bCanFire = false;

		float ChargePercent = CurrentChargeAmount / MaxChargeDuration;
		OnProjectileReleased(ProjectileType, ChargePercent);

		bHasReachedMaxCharge = false;

		return true;
	}
	
	return false;
}

void AWeapon::SetChargeTimer()
{
	GetWorldTimerManager().SetTimer(ChargeTimerHandle, this, &AWeapon::ChargeUpdate, MaxChargeDuration, false, -1.0f);
}

void AWeapon::ChargeUpdate()
{
	bHasReachedMaxCharge = true;
	CurrentChargeAmount = FMath::Max(0.0f, GetWorldTimerManager().GetTimerElapsed(ChargeTimerHandle));

	if (bIsChargingWeapon && bFireImmediatelyMaxCharge)
	{
		TryToFireProjectile(ProjectileTypeToFire);
	}
}

void AWeapon::RateOfFireUpdate()
{
	bCanFire = true;
}
