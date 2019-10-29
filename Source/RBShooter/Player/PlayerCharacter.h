// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCharacterMovementComponent;
class UChildActorComponent;
class AWeapon;

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

public:

	/* Default sensitivity. This is set by options loader and should not be changed after. Use SetCameraSensitivityMultiplier instead. */
	UFUNCTION(BlueprintCallable, Category="Camera")
	void SetDefaultCameraSensitivity(float SensitivityDefault = 1.0f);

	/* Set camera sensivity multiplier. */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraSensitivityMultiplier(float Multiplier = 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float CameraSensitivityDefault;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float CameraSensitivityMultiplier;

private: // Camera

	float CameraSensitivityFinal;

private: // Movement

	FVector MovementInput;

	UCharacterMovementComponent* CachedMovementComponent;

	void MoveFromInput();

private: // Input callbacks

	// Movement
	void InputCallback_MoveLeftRight(float Axis);
	void InputCallback_MoveForwardBack(float Axis);

	// Camera movement
	void InputCallback_LookLeftRight(float Axis);
	void InputCallback_LookUpDown(float Axis);

	// Weapon actions
	void InputCallback_FireRedProjectile();
	void InputCallback_FireBlueProjectile();
};
