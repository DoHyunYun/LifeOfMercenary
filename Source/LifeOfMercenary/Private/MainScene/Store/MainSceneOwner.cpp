// Fill out your copyright notice in the Description page of Project Settings.

#include "MainSceneOwner.h"
#include "Camera/MainSceneCamera.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


AMainSceneOwner::AMainSceneOwner() : Inventory(nullptr)
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AMainSceneOwner::BeginPlay()
{
	Super::BeginPlay();

}


void AMainSceneOwner::InputTouchBegin(ETouchIndex::Type _type, UPrimitiveComponent* _primityive)
{
	AMainSceneCamera* camera = Cast<AMainSceneCamera>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget());

	camera->CameraMoveTo(UKismetMathLibrary::TransformLocation(this->GetActorTransform(), targetLocation),
		UKismetMathLibrary::TransformLocation(this->GetActorTransform(), targetView));
}