// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "BulletActor.h"
#include "GameFramework/PlayerController.h"

// Sets default values
APlayerActor::APlayerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Set up the collider for this object
	OurCollider = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerCollider"));
  	OurCollider->SetSphereRadius(50.f); //Diameter will be 100 = default mesh-size
	OurCollider->SetGenerateOverlapEvents(true);
	RootComponent = OurCollider;

	OurVisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));
	OurVisibleMesh->SetupAttachment(RootComponent);

	OurAttack = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerAttack"));
  	OurAttack->InitBoxExtent(FVector(300.f, 300.f, 300.f));
	OurAttack->SetupAttachment(RootComponent);
	OurAttack->SetGenerateOverlapEvents(false);
}

// Called when the game starts or when spawned
void APlayerActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Hello World!!"))

   	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	APlayerController* OurPlayerController = GetWorld()->GetFirstPlayerController();

	if (OurCamera)
		OurPlayerController->SetViewTarget(OurCamera);

}

// Called to bind functionality to input
void APlayerActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
    InputComponent->BindAxis("MoveForward", this, &APlayerActor::Move_XAxis);
    InputComponent->BindAxis("MoveRight", this, &APlayerActor::Move_YAxis);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerActor::Shoot);
	InputComponent->BindAction("Attack", IE_Pressed, this, &APlayerActor::Attack);
}

// Called every frame
void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	    // Handle movement based on our "MoveX" and "MoveY" axes
  
	if (!MovementVector.IsZero())
  	{
		FVector NewLocation = GetActorLocation() + (MovementVector * DeltaTime);
		SetActorLocation(NewLocation);
  	}

	//Super crude win state
	if (EnemiesHit >= 10)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player says: I WON!!"))
		this->SetActorHiddenInGame(true);
	}

	//OurAttack->SetGenerateOverlapEvents(false);
}

void APlayerActor::Move_XAxis(float AxisValue)
{
    //UE_LOG(LogTemp, Warning, TEXT("X speed %f!!"), AxisValue)
	MovementVector.X = MaxSpeed * AxisValue;
}

void APlayerActor::Move_YAxis(float AxisValue)
{
    //UE_LOG(LogTemp, Warning, TEXT("Y speed %f!!"), AxisValue)
	MovementVector.Y = MaxSpeed * AxisValue;
}

void APlayerActor::Shoot()
{
	//Shoot only if not lost or won
	if (Lives > 0 && EnemiesHit < 10)
	{
		UWorld* World = GetWorld();	//Get the game world ( our level ) 
		if (World)					//test that it exists
		{
			World->SpawnActor<ABulletActor>(BulletBlueprint, GetActorLocation() + 
			FVector(BulletSpawnDistance, 0.f, 0.f), GetActorRotation());
		}
	}
	OurAttack->SetGenerateOverlapEvents(false);
}

void APlayerActor::Attack()
{
	OurAttack->SetGenerateOverlapEvents(true);
}

void APlayerActor::ImHit()
{
	Health -= 10.f;

	if (Health <= 0.f)
	{
		Lives--;
		Health = 100.f;
	}
	//Super crude loose state
	if (Lives <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player says: I'm dead!!"))
		//Destroy();	//can not do this because then camera is lost
		this->SetActorHiddenInGame(true);
	}
}

