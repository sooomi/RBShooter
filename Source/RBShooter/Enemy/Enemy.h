// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameUtility.h"
#include "Enemy.generated.h"

class UCharacterMovementComponent;
class UCapsuleComponent;

UCLASS()
class RBSHOOTER_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Basic")
	EColorTypes EnemyType;

private:

	UCharacterMovementComponent* CachedMovementComponent;

	UCapsuleComponent* CachedCapsuleComponent;

};
