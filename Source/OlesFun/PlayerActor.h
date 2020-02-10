// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerActor.generated.h"

UCLASS()
class OLESFUN_API APlayerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* OurVisibleMesh;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* OurCollider;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "The Bullet")
	TSubclassOf<class ABulletActor> BulletBlueprint;	//The blueprint version of the bullet - hopefully with a visible mesh!

	UPROPERTY(EditAnywhere, Category = "The Bullet")
	float BulletSpawnDistance = 1.f;

	UPROPERTY(EditAnywhere, Category = "Our Camera")
	AActor* OurCamera;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector MovementVector{};

	void ImHit();

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	int Lifes{3};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void MoveRight();
	void MoveLeft();
	void MoveForward();
	void MoveBackward();
	void Shoot();
};
