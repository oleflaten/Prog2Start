// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class OLESFUN_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* OurCollider;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* OurVisibleMesh;

	UPROPERTY(EditAnywhere)
	float Speed{ 400.f };

	UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* ExplotionSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
