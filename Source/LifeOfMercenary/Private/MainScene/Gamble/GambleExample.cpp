// Fill out your copyright notice in the Description page of Project Settings.

#include "GambleExample.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

void AGambleExample::BeginPlay()
{
	Super::BeginPlay();

	randNumber = 0;
}

void AGambleExample::SetNumber()
{
	randNumber = UKismetMathLibrary::RandomIntegerInRange(0, 1);
}

void AGambleExample::GameFinish(int32 _num)
{
	if (randNumber == _num) {
		SetPlayerGold(100);
	}
	else {
		SetPlayerGold(-100);
	}
}
