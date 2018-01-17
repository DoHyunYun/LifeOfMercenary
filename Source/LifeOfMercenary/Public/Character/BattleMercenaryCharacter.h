// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MercenaryCharacter.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Curves/CurveVector.h"
#include "BattleMercenaryCharacter.generated.h"


UENUM(BlueprintType)
enum class EMercenaryStateType : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Walk		UMETA(DisplayName = "Walk"),
	Roll		UMETA(DisplayName = "Roll"),
	Attack		UMETA(DisplayName = "Attack"),
	Block		UMETA(DisplayName = "Block"),
};

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API ABattleMercenaryCharacter : public AMercenaryCharacter
{
	GENERATED_BODY()
public:
	ABattleMercenaryCharacter();

	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void PlayRolling();
	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void PlayAttack();
	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void EndAttack();
	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void EndRolling();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void Rolling();
	void Attack();
	void Block();
	void UnBlock();
private:

public:
	UPROPERTY(VisibleAnywhere, Category = "BattleMercenaryCharacter")
		USpringArmComponent* cameraSpringArm;
	UPROPERTY(VisibleAnywhere, Category = "BattleMercenaryCharacter")
		UCameraComponent* camera;
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		EMercenaryStateType currentState;
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		FVector worldDir;
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bActiveRoll; //Ȱ��ȭ �ÿ��� ȸ�� ����
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bFreeAction; //���ݵ��߿� ������ Ʋ�� ���ֱ� ���ؼ�.
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bSaveRoll;   //���� ���߿� �����ٸ� ������ ���� �� �������� ���ֱ� ���ؼ�.
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bSaveBlock;  //�����̳� ȸ�� ���߿� ���и� ��ٸ� �ൿ�� ���� �Ŀ� ���и� ��� ���ֱ� ���ؼ�.
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bNextAttack; //���� ������ �����ٸ� ���� ������ ���ؼ�.

private:
	float m_baseTurnRate;
	float m_baseLookUpRate;
};