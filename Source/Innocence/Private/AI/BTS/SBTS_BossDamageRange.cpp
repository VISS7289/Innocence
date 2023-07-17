// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTS/SBTS_BossDamageRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

// ��������Ŀ���ǲ�ѯAI��Player֮��ľ���
void USBTS_BossDamageRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// ��ȡ��Ϊ���ڵ�ĺڰ����
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp))
	{
		// ��ȡĿ�����
		AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController))
			{
				// ��ȡAI�Ķ���
				APawn* AIPawn = MyController->GetPawn();
				if (ensure(AIPawn))
				{
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					//bool bWithinRange = DistanceTo < 2000.f;

					//bool bHasLOS = false;
					//if (bWithinRange)
					//{
					//	bHasLOS = MyController->LineOfSightTo(TargetActor);
					//}

					// ��ʹ��Ӳ���룬�������Ƿ��ڷ�Χ��
					BlackBoardComp->SetValueAsFloat(AttackRangeKey.SelectedKeyName, DistanceTo);
				}

			}
		}
	}
}