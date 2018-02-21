// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LoMCharacter.h"
#include "StatusComponent.h"
#include "LoMMonster.generated.h"

UENUM(BlueprintType)
enum class EMonsterStateType : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	AttackReady	UMETA(DisplayName = "AttackReady"),
	Attack		UMETA(DisplayName = "Attack"),
	Damage		UMETA(DisplayName = "Damage"),
	Die			UMETA(DisplayName = "Die"),
};

USTRUCT(BlueprintType)
struct FMonsterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FMonsterData() : HealthPower(0.f), DefensivePower(0.f), AttackPower(0.f), StaminaPower(0.f), ResistancePower(0.f),
		HealthRecuperation(0.f), StaminaRecuperation(0.f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
		float HealthPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
		float DefensivePower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
		float AttackPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
		float StaminaPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
		float ResistancePower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
		float HealthRecuperation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
		float StaminaRecuperation;
};

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API ALoMMonster : public ALoMCharacter
{
	GENERATED_BODY()
public:
	ALoMMonster();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	void SetMonsterDataFromName(FString _monsterName);
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LoMMonster")
		UStatusComponent* Status;
	UPROPERTY(BlueprintReadWrite, Category = "LoMMonster")
		float attackRange;
	UPROPERTY(BlueprintReadWrite, Category = "LoMMonster")
		AActor* targetActor;
	UPROPERTY(BlueprintReadWrite, Category = "LoMMonster")
		EMonsterStateType currentState;
	UPROPERTY(BlueprintReadWrite, Category = "LoMMonster")
		bool bGoBack;


};
