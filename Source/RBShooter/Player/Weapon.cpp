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

bool AWeapon::TryToFireProjectile(EProjectileTypes ProjectileType, float ChargeAmount)
{
	// TODO check ammo amount
	if (bCanFire)
	{
		OnFireProjectileConfirmed(ProjectileType, ChargeAmount);
		bCanFire = false;

		return true;
	}
	
	return false;
}

void AWeapon::RateOfFireUpdate()
{
	bCanFire = true;
}

