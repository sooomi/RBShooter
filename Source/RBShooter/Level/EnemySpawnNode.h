// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameUtility.h"
#include "EnemySpawnNode.generated.h"

class AEnemy;

UCLASS()
class RBSHOOTER_API AEnemySpawnNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Spawning")
	AEnemy* ActivateSpawn();

public:

	/* Pool of possible enemies that can spawn from this node. Will randomly choose between them. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning")
	TArray<TSubclassOf<AActor>> EnemyActorPool;

	/* Minimum wave count required to be activated. 0 means it can activate at any wave, any number above means it can only activate if the current round is at that number or higher. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning")
	int32 MinimumWaveCount;

};
