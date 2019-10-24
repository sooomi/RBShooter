// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameUtility.h"
#include "EnemyMagnetEffect.generated.h"

class USphereComponent;

UCLASS()
class RBSHOOTER_API AEnemyMagnetEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyMagnetEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category="Magnet")
	EColorTypes EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Magnet")
	float OuterAttractionPull;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Magnet")
	float InnerAttractionPull;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Magnet")
	bool bIsAttractingEnemies;

private:

	UPROPERTY()
	USphereComponent* CachedOuterSphereComponent;

	UPROPERTY()
	USphereComponent* CachedInnerSphereComponent;

private:

	void AttractEnemies(float DeltaTime);
	void AttractFromSphere(USphereComponent* SphereComponent, float DeltaTime, float AttractionPull);
};
