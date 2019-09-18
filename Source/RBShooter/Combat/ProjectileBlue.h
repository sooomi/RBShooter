// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "Combat/ProjectileBase.h"
#include "ProjectileBlue.generated.h"

/**
 * 
 */
UCLASS()
class RBSHOOTER_API AProjectileBlue : public AProjectileBase
{
	GENERATED_BODY()
	
public:
	AProjectileBlue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
