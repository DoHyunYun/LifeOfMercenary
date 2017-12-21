// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoMCamera.h"
#include "MainSceneCamera.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API AMainSceneCamera : public ALoMCamera
{
	GENERATED_BODY()
public:
	AMainSceneCamera();

	virtual void Tick(float _deltaSeconds) override;

	//이동중이라면 작동하지 않음.
	UFUNCTION(BlueprintCallable, Category = "MainSceneCamera")
		bool CameraMoveTo(FVector _gotoPos, FVector _lookPos);

	UFUNCTION(BlueprintCallable, Category = "MainSceneCamera")
		bool CameraMoveBegin();

	UFUNCTION(BlueprintCallable, Category = "MainSceneCamera")
		bool GetIsBegin() { return m_bBegin; }

protected:
	virtual void BeginPlay() override;

private:
	void MoveFunc(float _deltaSeconds);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainSceneCamera")
		float moveTime;

private:
	FVector m_beginPos;
	FVector m_beginLookPos;

	FVector m_pastPos;
	FVector m_pastLookPos;

	FVector m_targetPos;
	FVector m_targetLookPos;

	bool m_bBegin;

	float m_tick;

};
