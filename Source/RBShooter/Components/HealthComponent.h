// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthAddedDelegate, float, Health, AActor*, InvokeActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthRemovedDelegate, float, Health, AActor*, InvokeActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthChangedDelegate, float, Health, AActor*, InvokeActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeathDelegate, AActor*, InvokeActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReviveDelegate, float, ReviveHealth, AActor*, InvokeActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RBSHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* Returns the current health percentage relative to max health. Value is between 0 and 1. */
	UFUNCTION(BlueprintPure, Category="Health Functions")
	float GetHealthPercentage();

	/* Set current health */
	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void SetHealth(float Health, AActor* InvokeActor);

	/* Set max health */
	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void SetMaxHealth(float Health, AActor* InvokeActor);

	/* Adds to current health */
	UFUNCTION(BlueprintCallable, Category="Health Functions")
	void AddHealth(float Health, AActor* InvokeActor = nullptr);

	/* Adds to max health */
	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void AddMaxHealth(float Health, AActor* InvokeActor = nullptr);

	/* Adds to current and max health */
	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void AddCurrentAndMaxHealth(float CurrentHealth, float MaxHealth, AActor* InvokeActor = nullptr);

	/* Removes from current health */
	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void RemoveHealth(float Health, AActor* InvokeActor = nullptr);

	/* Removes from max health */
	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void RemoveMaxHealth(float Health, AActor* InvokeActor = nullptr);

	/* Removes from current and max health */
	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void RemoveCurrentAndMaxHealth(float CurrentHealth, float MaxHealth, AActor* InvokeActor = nullptr);

	/* Kills the actor, regardless of health */
	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void Kill(AActor* InvokeActor = nullptr);

	/* Revives a dead actor */
	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void Revive(float ReviveStartHealth, AActor* InvokeActor = nullptr);

public: // Blueprint-specific events

	/* On Current Health Added */
	UPROPERTY(BlueprintAssignable, Category = "Health Event")
	FHealthAddedDelegate OnHealthAdded;

	/* On current health removed */
	UPROPERTY(BlueprintAssignable, Category = "Health Event")
	FHealthRemovedDelegate OnHealthRemoved;

	/* On current or max health changed */
	UPROPERTY(BlueprintAssignable, Category = "Health Event")
	FHealthChangedDelegate OnHealthChanged;

	/* On Death */
	UPROPERTY(BlueprintAssignable, Category = "Health Event")
	FDeathDelegate OnDeath;

	/* On Revive */
	UPROPERTY(BlueprintAssignable, Category = "Health Event")
	FReviveDelegate OnRevive;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health")
	float StartHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category="Health")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health")
	bool bStartDead;

	UPROPERTY(BlueprintReadOnly, Category="Health")
	bool bIsDead;

private:

	void ClampHealth();
};
