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

/**
 * 
 */
UCLASS()
class RBSHOOTER_API UGameUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "KillCount")
	static void IncrementKillCount(UPARAM(ref) FKillCount& KillCountObject, int32 Amount = 1, EColorTypes Type = EColorTypes::CT_None);

	UFUNCTION(BlueprintCallable, Category = "KillCount")
	static void DecrementKillCount(UPARAM(ref) FKillCount& KillCountObject, int32 Amount = 1, EColorTypes Type = EColorTypes::CT_None);

	UFUNCTION(BlueprintCallable, Category = "KillCount")
	static void ResetKillcount(UPARAM(ref) FKillCount& KillCountObject);
};
