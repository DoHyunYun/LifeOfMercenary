// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LoMCharacter.h"
#include "Components/EquipmentComponent.h"
#include "Components/PlayerStatusComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Item/Weapon.h"
#include "LifeOfMercenary/Public/Quest/QuestManager.h"
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

	UFUNCTION(BlueprintNativeEvent, Category = MainMercenary)
		void OnEquipItem(EEquipmentPartsType _type);

	UFUNCTION(BlueprintNativeEvent, Category = MainMercenary)
		void OnDisarmItem(EEquipmentPartsType _type);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		UEquipmentComponent* equipment;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		UPlayerStatusComponent* playerStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		USkeletalMeshComponent* body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		USkeletalMeshComponent* hands;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		USkeletalMeshComponent* bottoms;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		USkeletalMeshComponent* feets;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		UStaticMeshComponent* helmet;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		UStaticMeshComponent* rightHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		UStaticMeshComponent* leftHand;

	//³¯Â¥
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		int32 date;
	
	//--------
	//Äù½ºÆ®
	//--------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		UQuestManager* questManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MercenaryCharacter")
		int32 currentQuest;
};
