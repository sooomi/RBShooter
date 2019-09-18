// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyBase.generated.h"

UENUM(BlueprintType)
enum class EEnemyTypes : uint8
{
	ET_None UMETA(DisplayName = "None"),
	ET_Red UMETA(DisplayName="Red Enemy"),
	ET_Blue UMETA(DisplayName = "Blue Enemy")
};

class UCharacterMovementComponent;

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
	UCharacterMovementComponent* EditorCharacterMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Basic")
	EEnemyTypes EnemyType;

};
