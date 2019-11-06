// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameUtility.generated.h"

UENUM(BlueprintType)
enum class EColorTypes : uint8
{
	CT_None UMETA(DisplayName = "No Color"),
	CT_Red UMETA(DisplayName = "Red Color"),
	CT_Blue UMETA(DisplayName = "Blue Color")
};

UENUM(BlueprintType)
enum class EEnemyHitTypes : uint8
{
	EHT_Unknown UMETA(DisplayName = "Unknown"),
	EHT_Head UMETA(DisplayName = "Head"),
	EHT_Chest UMETA(DisplayName = "Chest"),
	EHT_LegLeft UMETA(DisplayName = "LegLeft"),
	EHT_LegRight UMETA(DisplayName = "LegRight")
};

UENUM(BlueprintType)
enum class EPowerTiesTypes : uint8
{
	PTT_TierNone UMETA(DisplayName = "No Tier"),
	PTT_Tier1 UMETA(DisplayName = "Magnet Projectile"),
	PTT_Tier2 UMETA(DisplayName = "Magnet Grenade"),
	PTT_Tier3 UMETA(DisplayName = "Board Clear")
};


USTRUCT(BlueprintType)
struct FKillCount
{
	GENERATED_BODY()

	FKillCount()
	{
		KillCountRed = 0;
		KillCountBlue = 0;
		KillCountTotal = 0;
	}

	UPROPERTY(BlueprintReadOnly, Category="KillCount")
	int32 KillCountRed;

	UPROPERTY(BlueprintReadOnly, Category = "KillCount")
	int32 KillCountBlue;

	UPROPERTY(BlueprintReadOnly, Category = "KillCount")
	int32 KillCountTotal;
};

USTRUCT(BlueprintType)
struct FWeaponColorAttribute
{
	GENERATED_BODY()

	FWeaponColorAttribute()
	{
		ValueRed = 1.0f;
		ValueBlue = 1.0f;
		ValueGlobal = 1.0f;
	}

	UPROPERTY(BlueprintReadOnly, Category = "Projectile Multiplier")
	float ValueRed;

	UPROPERTY(BlueprintReadOnly, Category = "Projectile Multiplier")
	float ValueBlue;

	UPROPERTY(BlueprintReadOnly, Category = "Projectile Multiplier")
	float ValueGlobal;
};

USTRUCT(BlueprintType)
struct FColorFloatGroup
{
	GENERATED_BODY()

	FColorFloatGroup()
	{
		Red = 0.0f;
		Blue = 0.0f;
	}

	UPROPERTY(BlueprintReadOnly, Category = "FColorFloatGroup")
	float Red;

	UPROPERTY(BlueprintReadOnly, Category = "FColorFloatGroup")
	float Blue;
};

/**
 * 
 */
UCLASS()
class RBSHOOTER_API UGameUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/* FKillCount Functions */

	UFUNCTION(BlueprintCallable, Category = "KillCount")
	static void IncrementKillCount(UPARAM(ref) FKillCount& KillCountObject, int32 Amount = 1, EColorTypes Type = EColorTypes::CT_None);

	UFUNCTION(BlueprintCallable, Category = "KillCount")
	static void DecrementKillCount(UPARAM(ref) FKillCount& KillCountObject, int32 Amount = 1, EColorTypes Type = EColorTypes::CT_None);

	UFUNCTION(BlueprintCallable, Category = "KillCount")
	static void ResetKillcount(UPARAM(ref) FKillCount& KillCountObject);

	/* FWeaponColorAttribute Functions */

	UFUNCTION(BlueprintCallable, Category = "WeaponColorAttribute")
	static void SetValue(UPARAM(ref) FWeaponColorAttribute& WeaponColorAttributeObject, float Value = 1.0f, EColorTypes ColorType = EColorTypes::CT_None);

	/* FColorFloatGroup Functions */
	UFUNCTION(BlueprintCallable, Category = "ColorFloatGroup")
	static void SetFloat(UPARAM(ref) FColorFloatGroup& ColorFloatGroupObject, float Value = 1.0f, EColorTypes ColorType = EColorTypes::CT_None);

	UFUNCTION(BlueprintCallable, Category = "ColorFloatGroup")
	static float GetFloat(UPARAM(ref) FColorFloatGroup& ColorFloatGroupObject, EColorTypes ColorType);
};
