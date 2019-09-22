// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthAddedDelegate, float, Health, AActor*, InvokeActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthRemovedDelegate, float, Health, AActor*, InvokeActor);
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

	UFUNCTION(BlueprintCallable, Category="Health Functions")
	void AddHealth(float Health, AActor* InvokeActor = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void AddMaxHealth(float Health, AActor* InvokeActor = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void AddCurrentAndMaxHealth(float CurrentHealth, float MaxHealth, AActor* InvokeActor = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void RemoveHealth(float Health, AActor* InvokeActor = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void RemoveMaxHealth(float Health, AActor* InvokeActor = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void RemoveCurrentAndMaxHealth(float CurrentHealth, float MaxHealth, AActor* InvokeActor = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void Kill(AActor* InvokeActor = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void Revive(float ReviveStartHealth, AActor* InvokeActor = nullptr);

public: // Blueprint-specific events

	UPROPERTY(BlueprintAssignable, Category = "Health Event")
	FHealthAddedDelegate OnHealthAdded;

	UPROPERTY(BlueprintAssignable, Category = "Health Event")
	FHealthRemovedDelegate OnHealthRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Health Event")
	FDeathDelegate OnDeath;

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
