// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Combat/ProjectileBase.h"
#include "Weapon.generated.h"

class APlayerCharacter;

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

	UFUNCTION(BlueprintCallable, Category = "Weapon Fire")
	bool TryToFireProjectile(EProjectileTypes ProjectileType, float ChargeAmount);

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Fire")
	void OnFireProjectileConfirmed(EProjectileTypes ProjectileType, float ChargeAmount);

private:

	UPROPERTY(EditAnywhere, Category="Weapon Fire")
	float RateOfFire;
	
private:

	APlayerCharacter* CachedPlayerOwner;

};
