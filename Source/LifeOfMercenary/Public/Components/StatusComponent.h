// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIFEOFMERCENARY_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStatusComponent();

	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetHealthPower() const { return m_healthPower; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetDefensivePower() const { return m_defensivePower; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetAttackPower() const { return m_attackPower; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetStaminaPower() const { return m_staminaPower; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetResistancePower() const { return m_resistancePower; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetHealthRecuperation() const { return m_healthRecuperation; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetAttackSpeed() const { return m_attackSpeed; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetMoveSpeed() const { return m_moveSpeed; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetStaminaRecuperation() const { return m_staminaRecuperation; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetCurrentHealthPower() const { return m_currentHealthPower; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetCurrentStaminaPower() const { return m_currentStaminaPower; }

	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		void SetHealthPower(float _value) { m_healthPower = _value; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		void SetDefensivePower(float _value) { m_defensivePower = _value; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		void SetAttackPower(float _value) { m_attackPower = _value; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		void SetStaminaPower(float _value) { m_staminaPower = _value; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		void SetResistancePower(float _value) { m_resistancePower = _value; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		void SetHealthRecuperation(float _value) { m_healthRecuperation = _value; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		void SetAttackSpeed(float _value) { m_attackSpeed = _value; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		void SetMoveSpeed(float _value) { m_moveSpeed = _value; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		void SetStaminaRecuperation(float _value) { m_staminaRecuperation = _value; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		void SetCurrentHealthPower(float _value) { m_currentHealthPower = _value; }
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		void SetCurrentStaminaPower(float _value) { m_currentStaminaPower = _value; }

	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		void AddCurrentHealthPower(float _value);
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		void AddCurrentStaminaPower(float _value);

protected:
	virtual void BeginPlay() override;

protected:
	float m_healthPower; 		//체력
	float m_defensivePower;		//방어력
	float m_attackPower;		//공격력
	float m_staminaPower;		//기력
	float m_resistancePower;	//저항력
	float m_healthRecuperation;	//회복력
	float m_attackSpeed;		//공격속도
	float m_moveSpeed;			//이동속도
	float m_staminaRecuperation;//기력 회복속도

	float m_currentHealthPower;  //현재 체력
	float m_currentStaminaPower; //현재 기력
};
