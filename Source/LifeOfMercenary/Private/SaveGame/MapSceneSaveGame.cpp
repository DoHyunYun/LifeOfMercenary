// Fill out your copyright notice in the Description page of Project Settings.

#include "MapSceneSaveGame.h"
#include "MapPoint.h"
#include "MapRouteSpline.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

UMapSceneSaveGame::UMapSceneSaveGame() : saveSlotName("MapSceneSaveSlot"), userIndex(0)
{
	m_hasPoint = 0;
	m_hasSpline = 0;
	m_targetPoint = 0;

	m_characterTransform = FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::ZeroVector);
}

void UMapSceneSaveGame::SaveCharacter(const AMapCharacter* const _mapChar)
{
	if(_mapChar->hasPoint != nullptr)	
		m_hasPoint = UKismetSystemLibrary::GetObjectName(_mapChar->hasPoint);
	if (_mapChar->hasSpline != nullptr)
		m_hasSpline = UKismetSystemLibrary::GetObjectName(_mapChar->hasSpline);
	if (_mapChar->targetPoint != nullptr)
		m_targetPoint = UKismetSystemLibrary::GetObjectName(_mapChar->targetPoint);

	m_characterTransform = _mapChar->GetActorTransform();

	for (int i = 0; i < _mapChar->SFT.Num(); i++) {
		m_SFT.Add(_mapChar->SFT[i]->GetUniqueID());
	}
	


	UGameplayStatics::SaveGameToSlot(this, saveSlotName, userIndex);
}


void UMapSceneSaveGame::LoadCharacter(const UObject* _world, AMapCharacter* const _mapChar)
{
	//���� ������Ʈ ������.
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(_world, AActor::StaticClass(), foundActors);

	/*
	//���� ������Ʈ�� ���� �׸� ���.
	TMultiMap<FString, AActor**> loadObjectList;

	if(m_hasSpline != 0)
	loadObjectList.Add(m_hasSpline, (&_mapChar->hasSpline));
	if (m_hasPoint != 0)
	loadObjectList.Add(m_hasPoint, (&_mapChar->hasPoint));
	if (m_targetPoint != 0)
	loadObjectList.Add(m_targetPoint, (&_mapChar->targetPoint));
	*/

	//���忡�� ���� ������Ʈ�� üũ�Ͽ� �ε��� �׸� ����.
	for (int i = 0; i < foundActors.Num(); i++) {
		/*
		AActor*** tempActor = loadObjectList.Find(UKismetSystemLibrary::GetObjectName(foundActors[i]));

		if (tempActor != nullptr) {
			**tempActor = foundActors[i];
			loadObjectList.Remove(UKismetSystemLibrary::GetObjectName(foundActors[i]));
			i--;
		}*/
		UKismetSystemLibrary::GetObjectName(_mapChar->hasPoint);
		if(_mapChar->hasSpline != nullptr)
			if (UKismetSystemLibrary::GetObjectName(foundActors[i]) == m_hasSpline)
				_mapChar->hasSpline = Cast<AMapRouteSpline>(foundActors[i]);
		if (_mapChar->hasPoint != nullptr)
			if (UKismetSystemLibrary::GetObjectName(foundActors[i]) == m_hasPoint)
				_mapChar->hasPoint = Cast<AMapPoint>(foundActors[i]);
		if (_mapChar->targetPoint != nullptr)
			if (UKismetSystemLibrary::GetObjectName(foundActors[i]) == m_targetPoint)
				_mapChar->targetPoint = Cast<AMapPoint>(foundActors[i]);

	}

	//ĳ���� ��ġ ����
	if (m_characterTransform.GetLocation() != FVector::ZeroVector) {
		m_characterTransform.SetLocation(FVector(m_characterTransform.GetLocation().X, m_characterTransform.GetLocation().Y, m_characterTransform.GetLocation().Z + 50.0f));
		_mapChar->SetActorTransform(m_characterTransform);
	}
}