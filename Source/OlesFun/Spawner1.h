// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner1.generated.h"

UCLASS()
class OLESFUN_API ASpawner1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner1();
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "Spawn-parameters")
    TSubclassOf<class AEnemyActor> EnemyBlueprint;    //The blueprint version of the bullet - hopefully with a visible mesh!
    
    UPROPERTY(EditAnywhere, Category = "Spawn-parameters")
    float TimeBetweenSpawning = 4.f;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    //this is set to 4 to get a spawn at startup!
    float TimeSinceLastSpawn = 4.f; 


};
