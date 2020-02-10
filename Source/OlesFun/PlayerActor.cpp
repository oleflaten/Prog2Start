// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
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
}

// Called when the game starts or when spawned
void APlayerActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Hello World!!"))

	APlayerController* OurPlayerController = GetWorld()->GetFirstPlayerController();
	EnableInput(OurPlayerController);

	if (OurCamera)
		OurPlayerController->SetViewTarget(OurCamera);

	InputComponent->BindAction("MoveRight", IE_Pressed, this, &APlayerActor::MoveRight);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &APlayerActor::MoveLeft);
	InputComponent->BindAction("MoveForward", IE_Pressed, this, &APlayerActor::MoveForward);
	InputComponent->BindAction("MoveBackWard", IE_Pressed, this, &APlayerActor::MoveBackward);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerActor::Shoot);
}

// Called every frame
void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(MovementVector * DeltaTime);
}

void APlayerActor::MoveRight()
{
	UE_LOG(LogTemp, Warning, TEXT("Move Right!!"))
	MovementVector = (FVector(0.f, MaxSpeed, 0.f));
}

void APlayerActor::MoveLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("Move Left!!"))
	MovementVector = (FVector(0.f, -MaxSpeed, 0.f));
}

void APlayerActor::MoveForward()
{
	UE_LOG(LogTemp, Warning, TEXT("Move Forward!!"))
		MovementVector = (FVector(MaxSpeed, 0.f, 0.f));
}

void APlayerActor::MoveBackward()
{
	UE_LOG(LogTemp, Warning, TEXT("Move Back!!"))
		MovementVector = (FVector(-MaxSpeed, 0.f, 0.f));
}

void APlayerActor::Shoot()
{

	UWorld* World = GetWorld();	//Get the game world ( our level ) 
	if (World)					//test that it exists
	{
		World->SpawnActor<ABulletActor>(BulletBlueprint, GetActorLocation() + 
			FVector(BulletSpawnDistance, 0.f, 0.f), GetActorRotation());
	}
}

void APlayerActor::ImHit()
{
	Lifes--;

	if (Lifes < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player says: I'm dead!!"))
		Destroy();
	}
}

