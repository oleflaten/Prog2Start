// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up the collider for this object
    OurCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("ColliderBox"));
    OurCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnOverlap);
 
	// Set OurCollider to be the RootComponent
    RootComponent = OurCollider;

    // Set up our visible mesh
    OurVisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));
    OurVisibleMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector NewLocation = GetActorLocation();
    NewLocation += GetActorForwardVector() * Speed * DeltaTime;
    SetActorLocation(NewLocation);


}

// https://docs.unrealengine.com/en-US/API/Runtime/Engine/Components/UPrimitiveComponent/OnComponentBeginOverlap/index.html
void AEnemyActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Enemy Overlaps %s"), *OtherActor->GetName())
 
    if (OtherActor->IsA(APlayerActor::StaticClass()))
    {
        Cast<APlayerActor>(OtherActor)->ImHit();


    //PartikkelFX: - you must the set up a ExplotionFX actor first!
    //    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplotionFX, GetTransform(), true);

        //SoundFX:  - you must the set up a ExplotionSound actor first!
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), CrashSound, GetActorLocation());

        //Destroy Enemy:
        Destroy();
    }
}