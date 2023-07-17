// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SpawnWall.generated.h"

/**
 * 
 */
UCLASS()
class INNOCENCE_API USpawnWall : public UBTTaskNode
{
	GENERATED_BODY()

private:

	// �������Ϊ���ڵ��д���һ���ӵ���
	UPROPERTY(EditAnywhere, Category = "AI")
		TSubclassOf<AActor> WallClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
		float MaxBulleSpread;

	// ����ִ�к���
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:

	USpawnWall();
};
