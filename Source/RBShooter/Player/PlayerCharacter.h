// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCharacterMovementComponent;

UCLASS()
class RBSHOOTER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	APlayerCharacter();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private: // Movement

	FVector MovementInput;

	UCharacterMovementComponent* CachedMovementComponent;

	void MoveFromInput();

private: // Input callbacks

	void InputCallback_MoveLeftRight(float Axis);
	void InputCallback_MoveForwardBack(float Axis);

	void InputCallback_LookLeftRight(float Axis);
	void InputCallback_LookUpDown(float Axis);
};
