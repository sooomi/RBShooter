// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameUtility.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class AEnemy;
class ACharacter;

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
	void Fire(ACharacter* CharacterOwner);

	UFUNCTION(BlueprintImplementableEvent, Category = "Projectile Event")
	void OnProjectileFired();

	UFUNCTION(BlueprintImplementableEvent, Category = "Projectile Event")
	void OnProjectileHitEnemy(AEnemy* Enemy, bool bColorMatch);

	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	UPROPERTY(BlueprintReadOnly, Category="Projectile")
	ACharacter* CharacterOwner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	EColorTypes ProjectileType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	float MaxLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float ProjectileDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USphereComponent* EditorSphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UProjectileMovementComponent* EditorProjectileComponent;

protected: // Inherited components

	UProjectileMovementComponent* CachedProjectileComponent;

	USphereComponent* CachedSphereComponent;

private:

	FTimerHandle LifeTimeTimerHandle;

	void LifeTimeUpdate();

};
