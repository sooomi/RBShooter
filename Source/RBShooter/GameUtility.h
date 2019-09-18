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

/**
 * 
 */
UCLASS()
class RBSHOOTER_API UGameUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
