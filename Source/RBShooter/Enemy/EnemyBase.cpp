// Copyright (c) 2019 PSQ Grupp 4 =)


#include "EnemyBase.h"
#include "Gameframework/MovementComponent.h"
#include "Combat/ProjectileBase.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	EditorMovement = CreateDefaultSubobject<UMovementComponent>(TEXT("Movement"));
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::OnProjectileHit(AProjectileBase* Projectile)
{
	if (Projectile->ProjectileType == EnemyType) // Colors match
	{
		OnProjectileHitEnemy(Projectile, true);
	}
	else // Colors don't match
	{
		OnProjectileHitEnemy(Projectile, false);
	}
}
