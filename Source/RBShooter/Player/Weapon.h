// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Combat/ProjectileBase.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EPowerTiesTypes : uint8
{
	PTT_TierNone UMETA(DisplayName = "No Tier"),
	PTT_Tier1 UMETA(DisplayName = "Magnet Projectile"),
	PTT_Tier2 UMETA(DisplayName = "Magnet Grenade"),
	PTT_Tier3 UMETA(DisplayName = "Board Clear")
};

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

	float GetProjectileSpeedMultiplier(EColorTypes ColorType);

	UFUNCTION(BlueprintPure, Category="Weapon Charging")
	float GetChargeFraction();

	UFUNCTION(BlueprintPure, Category = "Weapon Power")
	EPowerTiesTypes GetPowerTierFromColor(EColorTypes ColorType);

	UFUNCTION(BlueprintPure, Category="Weapon Damage")
	float GetDamage(EColorTypes ColorType);

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

	UFUNCTION(BlueprintCallable, Category = "Weapon Power")
	void SetPowerTier(EColorTypes ColorType, EPowerTiesTypes PowerTier);

	UFUNCTION(BlueprintCallable, Category = "Weapon Fire")
	void SetFireInterval(float Interval, bool bResetInterval = true);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Fire")
	float FireInterval;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Damage")
	float CurrentChargeAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Damage")
	FWeaponColorAttribute DamageBonus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Damage")
	FWeaponColorAttribute ProjectileMultiplier;

	UPROPERTY(BlueprintReadWrite, Category="Weapon Fire")
	bool bWantsToFirePowerAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Fire Immediately Upon Reaching Max Charge"), Category="Weapon Fire")
	bool bFireImmediatelyMaxCharge;

	UPROPERTY(BlueprintReadOnly, Category="Weapon Charging")
	bool bIsChargingWeapon;

	UPROPERTY(BlueprintReadWrite, Category="Power Tier")
	EPowerTiesTypes PowerTierRed;

	UPROPERTY(BlueprintReadWrite, Category = "Power Tier")
	EPowerTiesTypes PowerTierBlue;

	UPROPERTY(BlueprintReadOnly, Category = "Power Tier")
	EColorTypes ProjectileTypeToFire;

private: // Weapon charging

	UPROPERTY(EditAnywhere, Category="Weapon Charging")
	float MaxChargeDuration;

	FTimerHandle ChargeTimerHandle;

	bool bHasReachedMaxCharge;

	void SetChargeTimer();
	void ChargeUpdate();
	void UpdateChargeAmount();

private: // Rate of fire

	FTimerHandle RoFTimerHandle;

	bool bCanFire;

	void RateOfFireUpdate();
	
private:

	APlayerCharacter* CachedPlayerOwner;

	bool TryToFireProjectile(EColorTypes ProjectileType);

};
