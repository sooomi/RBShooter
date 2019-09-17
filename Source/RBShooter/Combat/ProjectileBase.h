// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UENUM(BlueprintType)
enum class EProjectileTypes : uint8
{
	PT_Red UMETA(DisplayName = "Red"),
	PT_Blue UMETA(DisplayName = "Blue")
};

class UProjectileMovementComponent;

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

	UFUNCTION(BlueprintCallable, Category="Projectile")
	void Fire(FVector Direction);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	EProjectileTypes ProjectileType;

private:

	UProjectileMovementComponent* CachedProjectileComponent;

};
