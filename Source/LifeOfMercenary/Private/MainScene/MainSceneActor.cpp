// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeOfMercenary/Public/MainScene/MainSceneActor.h"


// Sets default values
AMainSceneActor::AMainSceneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	boxCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	boxCollision->SetCollisionProfileName("UI");

	targetLocation = FVector(0, 0, 0);
	targetView = FVector(0, 0, 0);
}

// Called when the game starts or when spawned
void AMainSceneActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainSceneActor::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

