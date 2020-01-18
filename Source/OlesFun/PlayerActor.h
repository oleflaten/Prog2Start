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

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* OurVisibleMesh;

	UPROPERTY(EditAnywhere)
	float MaxForce = 10000.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void MoveRight();
	void MoveLeft();
	void MoveForward();
	void MoveBackward();
};
