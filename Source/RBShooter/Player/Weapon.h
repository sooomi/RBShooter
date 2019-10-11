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

	UFUNCTION(BlueprintPure, Category="Weapon Damage")
	float GetDamage(EColorTypes ColorType);

	UFUNCTION(BlueprintPure, Category = "Weapon Fire")
	float GetProjectileSpeedMultiplier(EColorTypes ColorType);

	UFUNCTION(BlueprintCallable, Category="Weapon Fire")
	bool LoadProjectile(EColorTypes ProjectileType);

	UFUNCTION(BlueprintCallable, Category = "Weapon Fire")
	bool ReleaseProjectile(EColorTypes ProjectileType);

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Events")
	void OnFireProjectileConfirmed(EColorTypes ProjectileType, float ChargeAmount);

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Events")
	void OnProjectileLoad(EColorTypes ProjectileType);

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Events")
	void OnProjectileReleased(EColorTypes ProjectileType, float ChargeFraction);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Damage")
	float DamageRed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Damage")
	float DamageBlue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Damage")
	float DamageGeneric;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Damage")
	FWeaponColorAttribute ProjectileMultiplier;

	UPROPERTY(BlueprintReadWrite, Category="Weapon Fire")
	bool bWantsToFireMagnetProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Fire Immediately Upon Reaching Max Charge"), Category="Weapon Fire")
	bool bFireImmediatelyMaxCharge;

private: // Weapon charging

	UPROPERTY(EditAnywhere, Category="Weapon Charging")
	float MaxChargeDuration;

	FTimerHandle ChargeTimerHandle;

	bool bIsChargingWeapon;
	bool bHasReachedMaxCharge;

	float CurrentChargeAmount;

	void SetChargeTimer();
	void ChargeUpdate();

private: // Rate of fire

	UPROPERTY(EditAnywhere, Category="Weapon Fire")
	float FireInterval;

	FTimerHandle RoFTimerHandle;

	bool bCanFire;

	void RateOfFireUpdate();
	
private:

	APlayerCharacter* CachedPlayerOwner;

	EColorTypes ProjectileTypeToFire;

	bool TryToFireProjectile(EColorTypes ProjectileType);

};
