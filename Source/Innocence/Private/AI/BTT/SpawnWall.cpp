// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTT/SpawnWall.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"
#include "Component/SAttributeComponent.h"

USpawnWall::USpawnWall()
{
	MaxBulleSpread = 8.0f;
}

EBTNodeResult::Type USpawnWall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		// ��ȡǽ������λ��
		FVector WallEndLocation = AICharacter->GetMesh()->GetSocketLocation("EndOfWall");
		// ��ȡ��������
		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		ACharacter* PlayerCharacter = Cast<ACharacter>(TargetActor);

		FVector PlayerLocation = TargetActor->GetActorLocation();

		// ��������Ӧ�û���
		//if (!USAttributeComponent::IsAlive(TargetActor))
		//{
		//	return EBTNodeResult::Failed;
		//}

		// ����ǽ��������ָ��Ŀ����������λ��
		FVector Direction = WallEndLocation - PlayerLocation;
		FRotator WallRotator = Direction.Rotation();
		FVector WallStartLocation = PlayerLocation - WallRotator.Vector() * 1000.f;
		// ���һЩ�Ŷ�
		//WallRotator.Pitch += FMath::RandRange(0.0f, MaxBulleSpread);
		//WallRotator.Yaw += FMath::RandRange(-MaxBulleSpread, MaxBulleSpread);

		//UE_LOG(LogTemp, Log, TEXT("---------------"));
		//UE_LOG(LogTemp, Log, TEXT("Location: %s"), *WallEndLocation.ToString());
		//UE_LOG(LogTemp, Log, TEXT("Rotator: %s"), *WallRotator.ToString());

		// �����������������ײ��Ϣ����������������Ϣ
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.Instigator = AICharacter;

		// ����ǽ
		AActor* NewWall = GetWorld()->SpawnActor<AActor>(WallClass, WallStartLocation, WallRotator, Params);
		// �������ɽ��
		return NewWall ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;;
}

