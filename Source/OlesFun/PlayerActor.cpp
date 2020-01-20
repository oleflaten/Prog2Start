// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "BulletActor.h"

// Sets default values
APlayerActor::APlayerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OurVisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));
	RootComponent = OurVisibleMesh;
}

// Called when the game starts or when spawned
void APlayerActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Hello World!!"))

	APlayerController* OurPlayerController = GetWorld()->GetFirstPlayerController();
	EnableInput(OurPlayerController);

	InputComponent->BindAction("MoveRight", IE_Repeat, this, &APlayerActor::MoveRight);
	InputComponent->BindAction("MoveLeft", IE_Repeat, this, &APlayerActor::MoveLeft);
	InputComponent->BindAction("MoveForward", IE_Repeat, this, &APlayerActor::MoveForward);
	InputComponent->BindAction("MoveBackWard", IE_Repeat, this, &APlayerActor::MoveBackward);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerActor::Shoot);
}

// Called every frame
void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerActor::MoveRight()
{
	UE_LOG(LogTemp, Warning, TEXT("Move Right!!"))
	OurVisibleMesh->AddForce(FVector(0.f, MaxForce, 0.f));
}

void APlayerActor::MoveLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("Move Left!!"))
	OurVisibleMesh->AddForce(FVector(0.f, -MaxForce, 0.f));
}

void APlayerActor::MoveForward()
{
	UE_LOG(LogTemp, Warning, TEXT("Move Forward!!"))
	OurVisibleMesh->AddForce(FVector(MaxForce, 0.f, 0.f));
}

void APlayerActor::MoveBackward()
{
	UE_LOG(LogTemp, Warning, TEXT("Move Back!!"))
	OurVisibleMesh->AddForce(FVector(-MaxForce, 0.f, 0.f));
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

