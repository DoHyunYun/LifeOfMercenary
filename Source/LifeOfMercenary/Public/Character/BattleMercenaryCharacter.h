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
		bool bActiveRoll; //활성화 시에만 회피 가능
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bFreeAction; //공격도중에 방향을 틀게 해주기 위해서.
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bSaveRoll;   //공격 도중에 구른다면 공격이 끝난 후 구르도록 해주기 위해서.
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bSaveBlock;  //공격이나 회피 도중에 방패를 든다면 행동이 끝난 후에 방패를 들게 해주기 위해서.
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bNextAttack; //현재 공격이 끝난다면 다음 공격을 위해서.

private:
	float m_baseTurnRate;
	float m_baseLookUpRate;
};