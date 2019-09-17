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

public: // Weapon

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	AWeapon* WeaponActor;

private: // Camera

	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraLookSensitivity;

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
