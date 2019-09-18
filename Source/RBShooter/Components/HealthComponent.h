// Copyright (c) 2019 PSQ Grupp 4 =)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


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

	void AddHealth(int32 Health, AActor* InvokeActor = nullptr);
	void RemoveHealth(int32 Health, AActor* InvokeActor = nullptr);
	void Kill(AActor* InvokeActor = nullptr);
	void Revive(int32 ReviveStartHealth, AActor* InvokeActor = nullptr);

public: // Blueprint-specific events

	UFUNCTION(BlueprintImplementableEvent, Category = "Health Event")
	void OnHealthAdded(int32 Amount, AActor* InvokeActor = nullptr);

	UFUNCTION(BlueprintImplementableEvent, Category = "Health Event")
	void OnHealthRemoved(int32 Amount, AActor* InvokeActor = nullptr);

	UFUNCTION(BlueprintImplementableEvent, Category = "Health Event")
	void OnDeath(AActor* InvokeActor = nullptr);

	UFUNCTION(BlueprintImplementableEvent, Category = "Health Event")
	void OnRevive(int32 ReviveStartHealth, AActor* InvokeActor = nullptr);

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
