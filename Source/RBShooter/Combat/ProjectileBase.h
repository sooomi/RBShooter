// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UENUM(BlueprintType)
enum class EProjectileTypes : uint8
{
	PT_None UMETA(DisplayName="None"),
	PT_Red UMETA(DisplayName = "Red"),
	PT_Blue UMETA(DisplayName = "Blue")
};

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class RBSHOOTER_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

	// Called from weapon blueprint when this actor
	// is spawned in the world
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	virtual void OnProjectileFired();

	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	EProjectileTypes ProjectileType;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* EditorSphereComponent;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* EditorProjectileComponent;

protected:

	UProjectileMovementComponent* CachedProjectileComponent;

	USphereComponent* CachedSphereComponent;

};
