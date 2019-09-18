// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthAddedDelegate, int32, Health, AActor*, InvokeActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthRemovedDelegate, int32, Health, AActor*, InvokeActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeathDelegate, AActor*, InvokeActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReviveDelegate, int32, ReviveHealth, AActor*, InvokeActor);

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
	void AddHealth(int32 Health, AActor* InvokeActor = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void RemoveHealth(int32 Health, AActor* InvokeActor = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void Kill(AActor* InvokeActor = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Health Functions")
	void Revive(int32 ReviveStartHealth, AActor* InvokeActor = nullptr);

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
	int32 StartHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	int32 MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category="Health")
	int32 CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health")
	bool bStartDead;

	UPROPERTY(BlueprintReadOnly, Category="Health")
	bool bIsDead;

private:

	void ClampHealth();
};
