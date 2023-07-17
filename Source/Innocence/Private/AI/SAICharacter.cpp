// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "BrainComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/SAttributeComponent.h"
//#include "Component/SActionComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{

	// ����������
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	// ���û�����ʱ�Զ����AI������
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// ����ע�⵽�����������ı�
void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ASAICharacter::GetHealthChange);
}

// ����ֵ�ı�ʱ
// ����ܵ�������ִ�в����ܻ�Ч�����л�����Ŀ���������ж�
void ASAICharacter::GetHealthChange(AActor* InstigatordActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// �ܻ��ж�
	if (Delta <= 0.0f)
	{
		// �����ж�
		if (NewHealth <= 0.0f)
		{
			// ֹͣ��Ϊ��
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}
			//// ��������ģ�⣨���йؽ��������岢�໥֮��ģ��������������Զ����µ�Ч����
			//GetMesh()->SetAllBodiesSimulatePhysics(true);
			//GetMesh()->SetCollisionProfileName("Ragdoll");
			// ȡ����������ײ
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();
			// 10s����������
			SetLifeSpan(10.0f);
		}
	}
}