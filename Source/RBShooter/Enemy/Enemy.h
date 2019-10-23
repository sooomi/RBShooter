// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameUtility.h"
#include "Enemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyHitTypes : uint8
{
	EHT_Unknown UMETA(DisplayName = "Unknown"),
	EHT_Head UMETA(DisplayName = "Head"),
	EHT_Chest UMETA(DisplayName = "Chest"),
	EHT_Legs UMETA(DisplayName = "Legs")
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Damage")
	float BaseDamage;

	UPROPERTY(BlueprintReadWrite, Category = "Enemy Damage")
	int32 WaveCountSpawnedAt;

	UPROPERTY(BlueprintReadWrite, Category = "Enemy Damage")
	int32 BurstCountSpawnedAt;

private:

	UCharacterMovementComponent* CachedMovementComponent;

	UCapsuleComponent* CachedCapsuleComponent;

};
