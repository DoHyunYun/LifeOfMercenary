// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeOfMercenary/Public/Camera/MainSceneCamera.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Kismet/KismetMathLibrary.h"

AMainSceneCamera::AMainSceneCamera()
{
	bAllowTickBeforeBeginPlay = true;

	m_beginPos = FVector::ZeroVector;
	m_beginLookPos = FVector::ZeroVector;
	m_pastPos = FVector::ZeroVector;
	m_pastLookPos = FVector::ZeroVector;
	m_targetPos = FVector::ZeroVector;
	m_targetLookPos = FVector::ZeroVector;

	m_moveTime = 2.0f;
	m_tick = 0.0f;
}

void AMainSceneCamera::BeginPlay()
{
	Super::BeginPlay();

	m_beginPos = GetActorLocation();
	m_beginLookPos = GetActorLocation() + (GetActorForwardVector() * 10);
	SetActorTickEnabled(false);//InActive Tick
}

void AMainSceneCamera::Tick(float _deltaSeconds)
{
	Super::Tick(_deltaSeconds);

	MoveFunc(_deltaSeconds);
}

bool AMainSceneCamera::CameraMoveTo(FVector _gotoPos, FVector _lookPos)
{
	if (IsActorTickEnabled()) return false;

	cameraMoveEnter.Broadcast();

	m_pastPos = GetActorLocation();
	m_pastLookPos = GetActorLocation() + (GetActorForwardVector() * 10);
	m_targetPos = _gotoPos;
	m_targetLookPos = _lookPos;

	m_tick = 0.0f;

	SetActorTickEnabled(true); //Active Tick

	return true;
}

void AMainSceneCamera::CameraMoveBegin()
{
	if (IsActorTickEnabled()) return;

	cameraMoveEnter.Broadcast();

	m_pastPos = GetActorLocation();
	m_pastLookPos = GetActorLocation() + (GetActorForwardVector() * 10);
	m_targetPos = m_beginPos;
	m_targetLookPos = m_beginLookPos;

	m_tick = 0.0f;

	SetActorTickEnabled(true); //Active Tick
}

void AMainSceneCamera::MoveFunc(float _deltaSeconds)
{
	m_tick += (_deltaSeconds / m_moveTime);

	SetActorLocation(FMath::Lerp(m_pastPos, m_targetPos, m_tick));
	SetActorRotation(UKismetMathLibrary::REase(
		FRotationMatrix::MakeFromX((m_pastLookPos - m_pastPos)).Rotator(),
		FRotationMatrix::MakeFromX((m_targetLookPos - m_targetPos)).Rotator(),
		m_tick, true, EEasingFunc::Linear));

	if (m_tick >= 1.0f) {
		SetActorTickEnabled(false);//Active Tick
		cameraMoveExit.Broadcast();
	}
}