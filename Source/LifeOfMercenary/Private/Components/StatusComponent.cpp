// Fill out your copyright notice in the Description page of Project Settings.

#include "StatusComponent.h"


// Sets default values for this component's properties
UStatusComponent::UStatusComponent() :m_healthPower(0.f), m_defensivePower(0.f), m_attackPower(0.f), m_staminaPower(0.f),
m_resistancePower(0.f), m_healthRecuperation(0.f), m_attackSpeed(1.f), m_moveSpeed(1.f), m_staminaRecuperation(0.f),
m_currentHealthPower(0.f), m_currentStaminaPower(0.f)
{

}

void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStatusComponent::AddCurrentHealthPower(float _value)
{
	m_currentHealthPower += _value;
}	

void UStatusComponent::AddCurrentStaminaPower(float _value)
{
	m_currentStaminaPower += _value;
}