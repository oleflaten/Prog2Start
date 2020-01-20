// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Set up the collider for this object
    OurCollider = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderSphere"));
    // https://docs.unrealengine.com/en-US/API/Runtime/Engine/Components/UPrimitiveComponent/OnComponentBeginOverlap/index.html
    OurCollider->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnOverlap);
    OurCollider->SetSphereRadius(50.f); //Diameter will be 100 = default mesh-size

	// Set OurCollider to be the RootComponent
    RootComponent = OurCollider;

    // Set up our visible mesh
    OurVisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));
    OurVisibleMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector NewLocation = GetActorLocation();
    NewLocation += GetActorForwardVector() * Speed * DeltaTime;
    SetActorLocation(NewLocation);
}

// https://docs.unrealengine.com/en-US/API/Runtime/Engine/Components/UPrimitiveComponent/OnComponentBeginOverlap/index.html
void ABulletActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Bullet Overlaps %s"), *OtherActor->GetName())
 
    Destroy();

    /*Things to come
    //if (OtherActor->IsA(AEnemy::StaticClass()))
    //{
    //    Cast<AEnemy>(OtherActor)->ImHit(); //OtherActor->Destroy();
    //    //PartikkelFX:
    //    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplotionFX, GetTransform(), true);

    //    //SoundFX
    //    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplotionSound, GetActorLocation());

    //    //Destroy Bullet:
    //    Destroy();
    //}*/
}