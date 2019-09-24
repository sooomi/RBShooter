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
enum class EEnemySpawnTypes : uint8
{
	EST_Random = 0 UMETA(DisplayName = "Random Enemy"),
	EST_Red UMETA(DisplayName = "Red Enemy"),
	EST_Blue UMETA(DisplayName = "Blue Enemy"),

	EST_COUNT
};

/**
 * 
 */
UCLASS()
class RBSHOOTER_API UGameUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
