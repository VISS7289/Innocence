// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTT/BTT_ShotProj.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"
#include "Component/SAttributeComponent.h"

UBTT_ShotProj::UBTT_ShotProj()
{
	MaxBulleSpread = 8.0f;
}

// ִ�й���
EBTNodeResult::Type UBTT_ShotProj::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// ��ȡAIController
	AAIController* MyController = OwnerComp.GetAIOwner();

	if (ensure(MyController))
	{
		// ��ȡAICharacter
		ACharacter* AICharacter = Cast<ACharacter>(MyController->GetPawn());
		if (AICharacter == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		// ��ȡAI���ֹ������
		FVector MuzzleLocation = AICharacter->GetMesh()->GetSocketLocation("Muzzle_01");
		// ��ȡ��������
		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		// ��������Ӧ�û���
		//if (!USAttributeComponent::IsAlive(TargetActor))
		//{
		//	return EBTNodeResult::Failed;
		//}

		// �����ӵ���������ָ��Ŀ����������λ��
		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotator = Direction.Rotation();
		// ���һЩ�Ŷ�
		//MuzzleRotator.Pitch += FMath::RandRange(0.0f, MaxBulleSpread);
		//MuzzleRotator.Yaw += FMath::RandRange(-MaxBulleSpread, MaxBulleSpread);

		//UE_LOG(LogTemp, Log, TEXT("---------------"));
		//UE_LOG(LogTemp, Log, TEXT("Location: %s"), *MuzzleLocation.ToString());
		//UE_LOG(LogTemp, Log, TEXT("Rotator: %s"), *MuzzleRotator.ToString());

		// �����������������ײ��Ϣ����������������Ϣ
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.Instigator = AICharacter;

		// ����������
		AActor* NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotator, Params);
		// �������ɽ��
		return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;;
}
