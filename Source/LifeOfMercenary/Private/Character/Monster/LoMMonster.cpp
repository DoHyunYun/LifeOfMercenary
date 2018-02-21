// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Monster/LoMMonster.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "LoMGameInstance.h"

ALoMMonster::ALoMMonster() : attackRange(0.f), targetActor(nullptr), currentState(EMonsterStateType::Idle),
bGoBack(false), Status(nullptr)
{
	Status = CreateDefaultSubobject<UStatusComponent>(TEXT("Status"));
}

void ALoMMonster::BeginPlay()
{
	Super::BeginPlay();
	//this->GetCapsuleComponent()->GetScaledCapsuleRadius()
	attackRange = this->GetCapsuleComponent()->GetScaledCapsuleRadius()+120.f;
	targetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void ALoMMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALoMMonster::SetMonsterDataFromName(FString _monsterName)
{
	FMonsterData* MD = Cast<ULoMGameInstance>(GetWorld()->GetGameInstance())->
		GetDataTableManager()->GetMonsterDataTable()->FindRow<FMonsterData>(*_monsterName, FString(""));

	if (MD != nullptr) {
		Status->SetAttackPower(MD->AttackPower);
		Status->SetDefensivePower(MD->DefensivePower);
		Status->SetHealthPower(MD->HealthPower);
		Status->SetCurrentHealthPower(MD->HealthPower);
		Status->SetResistancePower(MD->ResistancePower);
		Status->SetStaminaPower(MD->StaminaPower);
		Status->SetCurrentStaminaPower(MD->StaminaPower);
		Status->SetHealthRecuperation(MD->HealthRecuperation);
		Status->SetStaminaRecuperation(MD->StaminaRecuperation);
	}
	else {
		UE_LOG(LogClass, Log, TEXT("ALoMMonster::SetMonsterDataFromName - None Monster Code!! - %s"), *_monsterName);
	}
}