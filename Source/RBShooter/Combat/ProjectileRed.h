// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "Combat/ProjectileBase.h"
#include "ProjectileRed.generated.h"

/**
 * 
 */
UCLASS()
class RBSHOOTER_API AProjectileRed : public AProjectileBase
{
	GENERATED_BODY()

public:
	AProjectileRed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
