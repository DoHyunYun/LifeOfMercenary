// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h" //boxcollision
#include "MainSceneActor.generated.h"

UCLASS()
class LIFEOFMERCENARY_API AMainSceneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainSceneActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float _deltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MainSceneActor")
		UBoxComponent* boxCollision;

	//Camera Position
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainSceneActor", Meta = (MakeEditWidget = true))
		FVector targetLocation;

	//Camera LookTarget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainSceneActor", Meta = (MakeEditWidget = true))
		FVector targetView;
};
