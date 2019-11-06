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
	AttractFromSphere(CachedOuterSphereComponent, DeltaTime, OuterAttractionPull);

	// Inner
	AttractFromSphere(CachedInnerSphereComponent, DeltaTime, InnerAttractionPull);
}

void AEnemyMagnetEffect::AttractFromSphere(USphereComponent* SphereComponent, float DeltaTime, float AttractionPull)
{
	if (SphereComponent)
	{
		TArray<AActor*> OverLappingEnemies;
		SphereComponent->GetOverlappingActors(OverLappingEnemies, AEnemy::StaticClass());

		for (int32 i = 0; i < OverLappingEnemies.Num(); i++)
		{
			AEnemy* Enemy = Cast<AEnemy>(OverLappingEnemies[i]);
			if (Enemy && (Enemy->EnemyType == EnemyType || EnemyType == EColorTypes::CT_None))
			{
				FVector Position(Enemy->GetActorLocation());

				Enemy->SetActorLocation(FMath::Lerp(Position, GetActorLocation(), DeltaTime * AttractionPull));
			}
		}
	}
}
