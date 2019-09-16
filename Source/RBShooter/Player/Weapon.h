// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

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
	bool FireProjectile_Red(float ChargeAmount);

	UFUNCTION(BlueprintCallable, Category = "Weapon Fire")
	bool FireProjectile_Blue(float ChargeAmount);

private:

	UPROPERTY(EditAnywhere, Category="Weapon Fire")
	float RateOfFire;

};
