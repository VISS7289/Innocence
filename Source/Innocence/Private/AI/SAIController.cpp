// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ASAIController::ASAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
}

void ASAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!IsValid(InPawn))
	{
		return;
	}

	EnemyCharacter = Cast<ACharacter>(InPawn);

	if (!IsValid(EnemyCharacter))
	{
		return;
	}

	if (IsValid(BlackboardComponent->GetBlackboardAsset()))
	{
		BlackboardComponent->InitializeBlackboard(*(BlackboardComponent->GetBlackboardAsset()));
		BehaviorTreeComponent->StartLogic();
	}
}

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	// UGameplayStatics������ȡ�����ؿ������ԣ�GetPlayerPawn�ǻ�ȡ��ҵĺ���
	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (MyPawn)
	{
		// ��ȡ�ڰ�Ԫ�ص�ֵ�������úڰ��MoveToLocationΪ��ҵ�λ��(ֻ�����һ��)
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());

		// ���������λ�õĸ�������Ѱ�����
		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}
}