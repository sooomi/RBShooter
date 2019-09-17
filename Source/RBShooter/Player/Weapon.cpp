// Copyright (c) 2019 PSQ Grupp 4 =)


#include "Weapon.h"
#include "PlayerCharacter.h"
#include "Combat/ProjectileBase.h"

#include "Kismet/GameplayStatics.h"
#include "Gameframework/Character.h"
#include "Engine/World.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	RateOfFire = 0.2f;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CachedPlayerOwner = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWeapon::TryToFireProjectile(EProjectileTypes ProjectileType, float ChargeAmount)
{
	// TODO check ammo amount and fire rate CD first
	OnWantsToFireProjectile(ProjectileType, ChargeAmount);

	return true;
}

