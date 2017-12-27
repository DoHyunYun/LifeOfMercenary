// Fill out your copyright notice in the Description page of Project Settings.

#include "MercenaryCharacter.h"
#include "LifeOfMercenary/Public/Functions/Calendar.h"

AMercenaryCharacter::AMercenaryCharacter() : equipment(nullptr), playerStatus(nullptr)
{
	equipment = CreateDefaultSubobject<UEquipmentComponent>(TEXT("equipment"));
	playerStatus = CreateDefaultSubobject<UPlayerStatusComponent>(TEXT("playerStatus"));

	body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("body"));
	hands = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("hands"));
	bottoms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("bottoms"));
	feets = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("feets"));
	helmet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("helmet"));
	rightHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("righthand"));
	leftHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leftHand"));

	body->SetMasterPoseComponent(GetMesh());
	hands->SetMasterPoseComponent(GetMesh());
	feets->SetMasterPoseComponent(GetMesh());
	bottoms->SetMasterPoseComponent(GetMesh());

	body->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	hands->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	feets->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	bottoms->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	helmet->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "helmet_socket");
	rightHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "rightHand_socket");
	leftHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "leftHand_socket");
	
	playerStatus->equipment = equipment;
}

void AMercenaryCharacter::BeginPlay()
{
	Super::BeginPlay();


	//장비 아이템 장착 시 호출
	equipment->OnEquipItem.AddDynamic(this, &AMercenaryCharacter::OnEquipItem);
	//장비 아이템 해제 시 호출
	equipment->OnDisarmItem.AddDynamic(this, &AMercenaryCharacter::OnDisarmItem);

	//날짜 세팅
	date = UCalendar::ConvertFStoi("11015");
	//퀘스트 세팅
	questManager = NewObject<UQuestManager>();
	currentQuest = INDEX_NONE;
}

void AMercenaryCharacter::OnEquipItem_Implementation(EEquipmentPartsType _type)
{
	UItem* item = equipment->GetEquipmentArray()[(int32)_type];
	FString stringPath = "/Game/Resources/Item/Meshes/"
		+ item->GetMeshCode() + "." + item->GetMeshCode();

	switch (_type) {
	case EEquipmentPartsType::HEAD:
		helmet->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *stringPath));
		break;
	case EEquipmentPartsType::TOP:
		body->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *stringPath));
		break;
	case EEquipmentPartsType::BOTTOMS:
		bottoms->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *stringPath));
		break;
	case EEquipmentPartsType::HAND:
		hands->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *stringPath));
		break;
	case EEquipmentPartsType::FEET:
		feets->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *stringPath));
		break;
	case EEquipmentPartsType::ONE:
		rightHand->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *stringPath));
		break;
	case EEquipmentPartsType::TWO:
		rightHand->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *stringPath));
		break;
	case EEquipmentPartsType::ASSIST:
		if (item->ToWeapon()->GetWeaponType() == EWeaponType::SHIELD) {
			leftHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "shield_socket");
		}
		else {
			leftHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "leftHand_socket");
		}
		leftHand->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *stringPath));
		break;
	}

}

void AMercenaryCharacter::OnDisarmItem_Implementation(EEquipmentPartsType _type)
{
	UItem* item = equipment->GetEquipmentArray()[(int32)_type];

	switch (_type) {
	case EEquipmentPartsType::HEAD:
		helmet->SetStaticMesh(nullptr);
		break;
	case EEquipmentPartsType::TOP:
		body->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr,
			TEXT("/Game/Characters/Mercenary/SkeletalMeshes/SK_Top.SK_Top")));
		break;
	case EEquipmentPartsType::BOTTOMS:
		bottoms->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr,
			TEXT("/Game/Characters/Mercenary/SkeletalMeshes/SK_Bottoms.SK_Bottoms")));
		break;
	case EEquipmentPartsType::HAND:
		hands->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr,
			TEXT("/Game/Characters/Mercenary/SkeletalMeshes/SK_Hands.SK_Hands")));
		break;
	case EEquipmentPartsType::FEET:
		feets->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr,
			TEXT("/Game/Characters/Mercenary/SkeletalMeshes/SK_Feet.SK_Feet")));
		break;
	case EEquipmentPartsType::ONE:
		rightHand->SetStaticMesh(nullptr);
		break;
	case EEquipmentPartsType::TWO:
		rightHand->SetStaticMesh(nullptr);
		break;
	case EEquipmentPartsType::ASSIST:
		leftHand->SetStaticMesh(nullptr);
		break;
	}
}