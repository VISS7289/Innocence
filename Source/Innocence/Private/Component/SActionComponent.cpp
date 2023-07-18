// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SActionComponent.h"
#include "Actions/SAction.h"
#include "Game/SGameplayFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"


// Sets default values for this component's properties
USActionComponent::USActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

void USActionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USActionComponent, Actions);
}

// ��ʼ��Ϸʱ���ڷ�������ʼ��Actions
void USActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ֻ�ڷ�������ʼ��
	if (GetOwner()->HasAuthority())
	{
		for (TSubclassOf<USAction> ActionClass : DefaultActions)
		{
			AddAction(GetOwner(), ActionClass);
		}
	}

}


// Debug�鿴Action״̬
void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, DebugMsg);

	//// Debug�鿴Action״̬
	//for (USAction* Action : Actions)
	//{
	//	FColor TextColor = Action->IsRunning() ? FColor::Blue : FColor::White;
	//	FString ActionMsg = FString::Printf(TEXT("[%s] Action: %s ; Outer: %s"),
	//		*GetNameSafe(GetOwner()),
	//		*GetNameSafe(Action),
	//		*GetNameSafe(Action->GetOuter()));

	//	USGameplayFunctionLibrary::LogOnScreen(this, ActionMsg, TextColor, 0.0f);
	//}
}

// ����ж�
// ��������������������Ӿ�����ж�
void USActionComponent::AddAction(AActor* InstigatorActor, TSubclassOf<USAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	// �����ͻ���
	if (!GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Client Attempting to Add Action. [Class: %s]"), *GetNameSafe(ActionClass));
		return;
	}

	USAction* NewAction = NewObject<USAction>(GetOwner(), ActionClass);
	if (ensure(NewAction))
	{
		NewAction->Initialize(this);
		Actions.Add(NewAction);

		if (NewAction->bAutoStart && ensure(NewAction->CanStart(InstigatorActor)))
		{
			NewAction->StartAction(InstigatorActor);
		}
	}

}

// �Ƴ��ж�
// �ж��ж�����ȷ�Ժ�����Ƴ�
void USActionComponent::RemoveAction(USAction* ActionToRemove)
{
	if (ensure(ActionToRemove))
	{
		Actions.Remove(ActionToRemove);
	}
}

// �����ж�
// �������п����ж��������ж�����ִ�ж�Ӧ�ж������Ҹ��ݱ�ǩ�����ж��Ƿ����ִ��
bool USActionComponent::StartActionByName(AActor* InstigatorActor, FName ActionName)
{
	for (USAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->CanStart(InstigatorActor))
			{

				// �ͻ���
				if (!GetOwner()->HasAuthority())
				{
					ServerStartAction(InstigatorActor, ActionName);
				}
				Action->StartAction(InstigatorActor);
				return true;
			}
			else
			{
				FString DebugMsg = FString::Printf(TEXT("Failed To Run: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMsg);
			}
		}
	}
	return false;
}

void USActionComponent::ServerStartAction_Implementation(AActor* InstigatorActor, FName ActionName)
{
	StartActionByName(InstigatorActor, ActionName);
}

// �����ж�
// �������п����ж��������ж����ƽ�����Ӧ�ж������Ҹ�������״̬�ж��Ƿ����ִ��
bool USActionComponent::StopActionByName(AActor* InstigatorActor, FName ActionName)
{
	for (USAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->IsRunning())
			{
				// �ͻ���
				if (!GetOwner()->HasAuthority())
				{
					ServerStopAction(InstigatorActor, ActionName);
				}

				Action->StopAction(InstigatorActor);
				return true;
			}
			else
			{
				FString DebugMsg = FString::Printf(TEXT("Failed To Stop: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMsg);
			}

		}
	}
	return false;
}

void USActionComponent::ServerStopAction_Implementation(AActor* InstigatorActor, FName ActionName)
{
	StopActionByName(InstigatorActor, ActionName);
}

// ����Action�����仯��ʱ��������
bool USActionComponent::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (USAction* Action : Actions)
	{
		if (Action)
		{
			WroteSomething |= Channel->ReplicateSubobject(Action, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}