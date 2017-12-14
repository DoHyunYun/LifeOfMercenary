// Fill out your copyright notice in the Description page of Project Settings.

#include "MercenaryCharacter.h"

AMercenaryCharacter::AMercenaryCharacter() : Equipment(nullptr), PlayerStatus(nullptr)
{
	Equipment = CreateDefaultSubobject<UEquipmentComponent>(TEXT("Equipment"));
	PlayerStatus = CreateDefaultSubobject<UPlayerStatusComponent>(TEXT("PlayerStatus"));
}

void AMercenaryCharacter::BeginPlay()
{

}