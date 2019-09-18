// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameUtility.h"
#include "EnemyBase.generated.h"

class UMovementComponent;
class AProjectileBase;

UCLASS()
class RBSHOOTER_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMovementComponent* EditorMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Basic")
	EColorTypes EnemyType;

};
