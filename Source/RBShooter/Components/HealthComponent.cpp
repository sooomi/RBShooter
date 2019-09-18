// Copyright (c) 2019 PSQ Grupp 4 =)


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 10;
	StartHealth = MaxHealth;
	CurrentHealth = MaxHealth;

	bStartDead = false;
	bIsDead = false;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = StartHealth;
	bIsDead = bStartDead;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::AddHealth(int32 Health, AActor* InvokeActor)
{
	CurrentHealth += Health;

	ClampHealth();
	OnHealthAdded.Broadcast(Health, InvokeActor);

	if (CurrentHealth <= 0)
	{
		Kill(InvokeActor);
	}
}

void UHealthComponent::RemoveHealth(int32 Health, AActor* InvokeActor)
{
	CurrentHealth -= Health;

	ClampHealth();
	OnHealthRemoved.Broadcast(Health, InvokeActor);

	if (CurrentHealth <= 0)
	{
		Kill(InvokeActor);
	}
}

void UHealthComponent::Kill(AActor* InvokeActor)
{
	if (!bIsDead)
	{
		CurrentHealth = 0;
		bIsDead = true;

		OnDeath.Broadcast(InvokeActor);
	}
}

void UHealthComponent::Revive(int32 ReviveStartHealth, AActor* InvokeActor)
{
	if (bIsDead)
	{
		CurrentHealth = ReviveStartHealth;
		bIsDead = false;

		ClampHealth();
		OnRevive.Broadcast(StartHealth, InvokeActor);
	}
}

void UHealthComponent::ClampHealth()
{
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
}

