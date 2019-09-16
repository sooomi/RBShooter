// Copyright (c) 2019 PSQ Grupp 4 =)


#include "Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	RateOfFire = 0.2f;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWeapon::FireProjectile_Red(float ChargeAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Fire Red Projectile, Charge amount %f"), ChargeAmount);

	return true;
}

bool AWeapon::FireProjectile_Blue(float ChargeAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Fire Blue Projectile, Charge amount %f"), ChargeAmount);

	return true;
}

