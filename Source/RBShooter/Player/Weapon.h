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
	bool TryToFireProjectile(EColorTypes ProjectileType, float ChargeAmount);

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Fire")
	void OnFireProjectileConfirmed(EColorTypes ProjectileType, float ChargeAmount);

private: // Rate of fire

	UPROPERTY(EditAnywhere, Category="Weapon Fire")
	float RateOfFire;

	FTimerHandle RoFTimerHandle;

	bool bCanFire;

	void RateOfFireUpdate();
	
private:

	APlayerCharacter* CachedPlayerOwner;

};
