// Copyright (c) 2019 PSQ Grupp 4 =)


#include "EnemyMagnetEffect.h"
#include "Enemy/Enemy.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyMagnetEffect::AEnemyMagnetEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsAttractingEnemies = true;

	OuterAttractionPull = 0.5f;
	InnerAttractionPull = 5.0f;
}

// Called when the game starts or when spawned
void AEnemyMagnetEffect::BeginPlay()
{
	Super::BeginPlay();

	CachedOuterSphereComponent = Cast<USphereComponent>(GetComponentsByTag(USphereComponent::StaticClass(), "Outer")[0]);
	CachedInnerSphereComponent = Cast<USphereComponent>(GetComponentsByTag(USphereComponent::StaticClass(), "Inner")[0]);
	
}

// Called every frame
void AEnemyMagnetEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAttractingEnemies)
	{
		AttractEnemies(DeltaTime);
	}
}

void AEnemyMagnetEffect::AttractEnemies(float DeltaTime)
{
	// Outer
	TArray<AActor*> OuterOverlappingEnemies;
	CachedOuterSphereComponent->GetOverlappingActors(OuterOverlappingEnemies, AEnemy::StaticClass());

	for (int32 i = 0; i < OuterOverlappingEnemies.Num(); i++)
	{
		AEnemy* Enemy = Cast<AEnemy>(OuterOverlappingEnemies[i]);
		if (Enemy && Enemy->EnemyType == EnemyType)
		{
			FVector Position(Enemy->GetActorLocation());

			Enemy->SetActorLocation(FMath::Lerp(Position, GetActorLocation(), DeltaTime * OuterAttractionPull));
		}
	}

	// Inner
	TArray<AActor*> InnerOverlappingEnemies;
	CachedInnerSphereComponent->GetOverlappingActors(InnerOverlappingEnemies, AEnemy::StaticClass());

	for (int32 i = 0; i < InnerOverlappingEnemies.Num(); i++)
	{
		AEnemy* Enemy = Cast<AEnemy>(InnerOverlappingEnemies[i]);
		if (Enemy && Enemy->EnemyType == EnemyType)
		{
			FVector Position(Enemy->GetActorLocation());

			Enemy->SetActorLocation(FMath::Lerp(Position, GetActorLocation(), DeltaTime * InnerAttractionPull));
		}
	}
}

