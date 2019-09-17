// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EProjectileTypes : uint8
{
	PT_Red UMETA(DisplayName="Red"),
	PT_Blue UMETA(DisplayName = "Blue")
};

UCLASS()
class RBSHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AWeapon();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Weapon Fire")
	bool FireProjectileRed(float ChargeAmount);

	UFUNCTION(BlueprintCallable, Category = "Weapon Fire")
	bool FireProjectileBlue(float ChargeAmount);

private:

	UPROPERTY(EditAnywhere, Category="Weapon Fire")
	float RateOfFire;

};
