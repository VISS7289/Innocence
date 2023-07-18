// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SAction.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "Component/SActionComponent.h"
#include "Game/SGameplayFunctionLibrary.h"
#include "Net/UnrealNetwork.h"


void USAction::Initialize(USActionComponent* NewActionComp)
{
	ActionComp = NewActionComp;
}


// �ж��Ƿ���Կ�ʼ
// ���ݲ鿴��ǰ��ǩ���Ƿ�������BlockedTags������Running�Ƿ���ȷ
bool USAction::CanStart_Implementation(AActor* InstigatorActor)
{
	USActionComponent* Comp = GetOwningComponent();
	if (Comp->ActiveGameplayTags.HasAny(BlockedTags) || RepData.Running > 0)
	{
		return false;
	}
	return true;
}

// ��ʼ�ж�
// ��ʼ�ж����Ҹ��±�ǩ��RepData
void USAction::StartAction_Implementation(AActor* InstigatorActor)
{
	UE_LOG(LogTemp, Log, TEXT("Running:%s"), *GetNameSafe(this));
	//USGameplayFunctionLibrary::LogOnScreen(this, FString::Printf(TEXT("Running:%s"), *GetNameSafe(this)), FColor::Green);

	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	RepData.Running++;
	RepData.InstigatorActor = InstigatorActor;
}

///////////////////////////////////////////////////////////////����Ҫ��///////////////////////////////////////////////////////
// �����ж�
// �����ж����Ҹ��±�ǩ��RepData
void USAction::StopAction_Implementation(AActor* InstigatorActor)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped:%s"), *GetNameSafe(this));
	//USGameplayFunctionLibrary::LogOnScreen(this, FString::Printf(TEXT("Stopped:%s"), *GetNameSafe(this)), FColor::White);

	//ensure(Running > 0); ����Ҫ��

	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	//Running--; ����Ҫ��
	RepData.Running = 0;
	RepData.InstigatorActor = InstigatorActor;
}
///////////////////////////////////////////////////////////////����Ҫ��///////////////////////////////////////////////////////

// ����UWorld
// �����ȷ����SAction�Ļ�������Actor�ض��ǿ�
UWorld* USAction::GetWorld() const
{
	/*UActorComponent* ActorComp = Cast<UActorComponent>(GetOuter());*/
	AActor* Actor = Cast<AActor>(GetOuter());
	if (Actor)
	{
		return Actor->GetWorld();
	}
	return nullptr;
}

// �������ڵ�ActionComponent
USActionComponent* USAction::GetOwningComponent() const
{
	return ActionComp;
}

// ͬ������ʱ
// ����ͬ���󣬸���RepData.Runningִ�п�ʼ�����
void USAction::OnRep_RepData()
{
	if (RepData.Running)
	{
		StartAction(RepData.InstigatorActor);
	}
	else
	{
		StopAction(RepData.InstigatorActor);
	}
}

void USAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USAction, RepData);
	DOREPLIFETIME(USAction, ActionComp);
}

bool USAction::IsRunning() const
{
	return RepData.Running > 0;
}

