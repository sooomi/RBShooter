// Copyright (c) 2019 PSQ Grupp 4 =)


#include "EnemySpawnNode.h"

// Sets default values
AEnemySpawnNode::AEnemySpawnNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MinimumWaveCount = 0;
	bIsSpawnInProgress = false;

}

// Called when the game starts or when spawned
void AEnemySpawnNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawnNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

