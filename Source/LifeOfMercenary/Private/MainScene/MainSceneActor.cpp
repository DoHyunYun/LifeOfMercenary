// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeOfMercenary/Public/MainScene/MainSceneActor.h"


// Sets default values
AMainSceneActor::AMainSceneActor() : targetLocation(0,0,0), targetView(0,0,0)
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	boxCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	boxCollision->SetCollisionProfileName("UI");
}

// Called when the game starts or when spawned
void AMainSceneActor::BeginPlay()
{
	Super::BeginPlay();
	boxCollision->OnInputTouchEnd.AddDynamic(this, &AMainSceneActor::InputTouchEnd);
}

// Called every frame
void AMainSceneActor::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

void AMainSceneActor::InputTouchEnd(ETouchIndex::Type _type, UPrimitiveComponent* _primityive)
{
	UE_LOG(LogTemp, Log, TEXT("testhihihihi"));
}
