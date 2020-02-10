// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner1.h"
#include "EnemyActor.h"

// Sets default values
ASpawner1::ASpawner1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    TimeEnemiesHaveSpawned += DeltaTime;

    //Adding time to the TimeSinceLastSpawn, so we can spawn at TimeBetweenSpawning
    TimeSinceLastSpawn += DeltaTime;

    if(TimeEnemiesHaveSpawned < TimeBeforeStopSpawning)
    {
    
        if (TimeBetweenSpawning < TimeSinceLastSpawn)
        {
            UWorld* World = GetWorld();    //Get the game world ( our level )
            if (World)                    //test that it exists
            {
                World->SpawnActor<AEnemyActor>(EnemyBlueprint, GetActorLocation(), GetActorRotation());
            }
        
            //Resetting TimeSinceLastSpawn for next spawn
            TimeSinceLastSpawn = 0.f;
        }
    }

}

