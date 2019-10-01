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

	RateOfFire = 0.2f;
	bCanFire = true;

	MaxChargeDuration = 3.0f;
	bIsChargingWeapon = false;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	// TODO there should be a better way to get the player pointer
	// since this class instance is in a child hierarchy where parent is the player
	CachedPlayerOwner = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Setup rate of fire timer
	GetWorldTimerManager().SetTimer(RoFTimerHandle, this, &AWeapon::RateOfFireUpdate, RateOfFire, true, 0.0f);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
		float ChargeAmount = FMath::Max(0.0f, GetWorldTimerManager().GetTimerElapsed(ChargeTimerHandle));
		OnFireProjectileConfirmed(ProjectileType, ChargeAmount);
		bCanFire = false;

		float ChargePercent = ChargeAmount / MaxChargeDuration;
		OnProjectileReleased(ProjectileType, ChargePercent);

		return true;
	}
	
	return false;
}

void AWeapon::SetChargeTimer()
{
	GetWorldTimerManager().SetTimer(ChargeTimerHandle, this, &AWeapon::ChargeUpdate, MaxChargeDuration, true, -1.0f);
}

void AWeapon::ChargeUpdate()
{
	if (bIsChargingWeapon)
	{
		TryToFireProjectile(ProjectileTypeToFire);
	}
}

void AWeapon::RateOfFireUpdate()
{
	bCanFire = true;
}
