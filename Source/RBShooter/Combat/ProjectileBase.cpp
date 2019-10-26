// Copyright (c) 2019 PSQ Grupp 4 =)


#include "ProjectileBase.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "Enemy/Enemy.h"
#include "Player/Weapon.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EditorSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	EditorProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	RootComponent = EditorSphereComponent;

	MaxLifeTime = 20.0f;
	BaseDamage = 1.0f;
	DamageBonus = 0.0f;
	ChargeAmount = 0.0f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	CachedProjectileComponent = Cast<UProjectileMovementComponent>(GetComponentByClass(UProjectileMovementComponent::StaticClass()));

	CachedSphereComponent = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));

	// Lifetime timer
	GetWorldTimerManager().SetTimer(LifeTimeTimerHandle, this, &AProjectileBase::LifeTimeUpdate, MaxLifeTime, false, -1.0f);
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AProjectileBase::GetDamage()
{
	return BaseDamage + DamageBonus;
}

void AProjectileBase::Fire(APlayerCharacter* Player, AWeapon* Weapon)
{
	PlayerOwner = Player;
	WeaponOwner = Weapon;

	// Apply weapon damage to projectile
	DamageBonus = WeaponOwner->GetDamage(ProjectileType);

	// Apply weapon projectile speed to projectile using time dilation
	float SpeedMultiplier = Weapon->GetProjectileSpeedMultiplier(ProjectileType);
	CustomTimeDilation = SpeedMultiplier;
	//CachedProjectileComponent->SetVelocityInLocalSpace(FVector(SpeedMultiplier * CachedProjectileComponent->InitialSpeed, 0.0f, 0.0f));

	OnProjectileFired();
}

void AProjectileBase::LifeTimeUpdate()
{
	Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Projectile destroyed due to lifetime"));
}
