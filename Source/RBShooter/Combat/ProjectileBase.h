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
	void Fire();

	UFUNCTION(BlueprintImplementableEvent, Category = "Projectile")
	void OnProjectileFired();

	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	EProjectileTypes ProjectileType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USphereComponent* EditorSphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UProjectileMovementComponent* EditorProjectileComponent;

protected:

	UProjectileMovementComponent* CachedProjectileComponent;

	USphereComponent* CachedSphereComponent;

};
