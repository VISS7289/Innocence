// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ShotProj.generated.h"

/**
 * 
 */
UCLASS()
class INNOCENCE_API UBTT_ShotProj : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	// �������Ϊ���ڵ��д���һ���ӵ���
	UPROPERTY(EditAnywhere, Category = "AI")
		TSubclassOf<AActor> ProjectileClass;

private:

	UPROPERTY(EditAnywhere, Category = "Attack")
		float MaxBulleSpread;

	// ����ִ�к���
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:

	UBTT_ShotProj();
};
