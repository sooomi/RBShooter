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
	CachedSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnProjectileHit);

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

void AProjectileBase::Fire(ACharacter* CharOwner, AWeapon* Weapon)
{
	CharacterOwner = CharOwner;
	WeaponOwner = Weapon;

	DamageBonus = WeaponOwner->GetDamage(ProjectileType);

	OnProjectileFired();
}

void AProjectileBase::OnProjectileHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* EnemyActor = Cast<AEnemy>(OtherActor);
	if (EnemyActor)
	{
		if (EnemyActor->EnemyType == ProjectileType) // Colors match
		{
			OnProjectileHitEnemy(EnemyActor, true, GetDamage());
		}
		else // Colors don't match
		{
			OnProjectileHitEnemy(EnemyActor, false, GetDamage());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile Collision with no enemy"));
	}
}

void AProjectileBase::LifeTimeUpdate()
{
	Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Projectile destroyed due to lifetime"));
}
