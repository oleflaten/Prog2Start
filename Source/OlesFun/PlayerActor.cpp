// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
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
}

void APlayerActor::Move_XAxis(float AxisValue)
{
    UE_LOG(LogTemp, Warning, TEXT("X speed %f!!"), AxisValue)
	MovementVector.X = MaxSpeed * AxisValue;
}

void APlayerActor::Move_YAxis(float AxisValue)
{
    UE_LOG(LogTemp, Warning, TEXT("Y speed %f!!"), AxisValue)
	MovementVector.Y = MaxSpeed * AxisValue;
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

