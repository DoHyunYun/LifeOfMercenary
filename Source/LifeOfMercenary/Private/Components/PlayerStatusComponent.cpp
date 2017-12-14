// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStatusComponent.h"

UPlayerStatusComponent::UPlayerStatusComponent() : m_strength(20.f), m_endurance(20.f), m_mentalStrength(20.f),
m_stress(0.f), m_fame(0.f), m_maxWeight(0.f)
{

}

void UPlayerStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	UpdateStatus();
}

void UPlayerStatusComponent::UpdateStatus()
{
	m_healthPower = m_endurance * 100.f;
	m_defensivePower = 0;	//����
	m_attackPower = m_strength;	//���ݷ�
	m_staminaPower = m_endurance * 9.f;	//���
	m_resistancePower = (m_endurance*0.01f) + (m_mentalStrength*0.01f);//���׷�
	m_healthRecuperation = m_healthPower*0.01f;	//ȸ����
	m_attackSpeed = 1.f;	//���ݼӵ�
	m_moveSpeed = 1.f;		//�̵��ӵ�
	m_staminaRecuperation = m_endurance + (m_mentalStrength*0.1f);//��� ȸ���ӵ�
}