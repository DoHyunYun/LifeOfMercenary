// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LoMCharacter.h"
#include "Components/EquipmentComponent.h"
#include "Components/PlayerStatusComponent.h"
#include "MercenaryCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API AMercenaryCharacter : public ALoMCharacter
{
	GENERATED_BODY()
public:
	AMercenaryCharacter();
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		UEquipmentComponent* Equipment;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		UPlayerStatusComponent* PlayerStatus;
};
