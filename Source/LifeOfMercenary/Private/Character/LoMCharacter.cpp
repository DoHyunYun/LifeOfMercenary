// Fill out your copyright notice in the Description page of Project Settings.

#include "LoMCharacter.h"


ALoMCharacter::ALoMCharacter() : Inventory(nullptr)
{
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

void ALoMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALoMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALoMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

