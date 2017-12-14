// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIFEOFMERCENARY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	//UPROPERTY(BlueprintReadWrite, Category = Inventory)
	//	TArray<UItem*> ItemArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryComponent")
		int32 gold;
};
