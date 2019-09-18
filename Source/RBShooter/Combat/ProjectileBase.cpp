// Copyright (c) 2019 PSQ Grupp 4 =)


#include "ProjectileBase.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EditorSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	EditorProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	RootComponent = EditorSphereComponent;

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	CachedProjectileComponent = Cast<UProjectileMovementComponent>(GetComponentByClass(UProjectileMovementComponent::StaticClass()));

	CachedSphereComponent = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));

	CachedSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnProjectileHit);
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::OnProjectileFired()
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile Fired"));
}

void AProjectileBase::OnProjectileHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile Collision"));
}
