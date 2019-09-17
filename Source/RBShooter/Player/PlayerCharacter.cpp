// Copyright (c) 2019 PSQ Grupp 4 =)

#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Weapon.h"

APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraLookSensitivity = 1.0f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CachedMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	
	TArray<UActorComponent*> Components = GetComponentsByTag(UChildActorComponent::StaticClass(), "Weapon");
	UChildActorComponent* ActorComponent = Cast<UChildActorComponent>(Components[0]);
	
	CachedWeaponActor = Cast<AWeapon>(ActorComponent->GetChildActor());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveFromInput();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind weapon actions
	PlayerInputComponent->BindAction(TEXT("FireProjectileRed"), IE_Pressed, this, &APlayerCharacter::InputCallback_FireRedProjectile);
	PlayerInputComponent->BindAction(TEXT("FireProjectileBlue"), IE_Pressed, this, &APlayerCharacter::InputCallback_FireBlueProjectile);

	// Bind axis actions
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &APlayerCharacter::InputCallback_MoveLeftRight);
	PlayerInputComponent->BindAxis(TEXT("MoveForwardBack"), this, &APlayerCharacter::InputCallback_MoveForwardBack);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRight"), this, &APlayerCharacter::InputCallback_LookLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpDown"), this, &APlayerCharacter::InputCallback_LookUpDown);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRightRate"), this, &APlayerCharacter::InputCallback_LookLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpDownRate"), this, &APlayerCharacter::InputCallback_LookUpDown);
}

void APlayerCharacter::MoveFromInput()
{
	const FTransform& Transform = GetActorTransform();
	const FVector& TransformedMovementDirection = UKismetMathLibrary::TransformDirection(Transform, MovementInput);

	CachedMovementComponent->AddInputVector(TransformedMovementDirection);
}

void APlayerCharacter::InputCallback_MoveLeftRight(float Axis)
{
	MovementInput.Y = Axis;
}

void APlayerCharacter::InputCallback_MoveForwardBack(float Axis)
{
	MovementInput.X = Axis;
}

void APlayerCharacter::InputCallback_LookLeftRight(float Axis)
{
	AddControllerYawInput(Axis * CameraLookSensitivity);
}

void APlayerCharacter::InputCallback_LookUpDown(float Axis)
{
	AddControllerPitchInput(Axis * CameraLookSensitivity);
}

void APlayerCharacter::InputCallback_FireRedProjectile()
{
	// The firing of the projectile is handled in blueprints
}

void APlayerCharacter::InputCallback_FireBlueProjectile()
{
	// The firing of the projectile is handled in blueprints
}
