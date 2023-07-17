// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SActionComponent.h"


// ��ʼʱ�������õ�Action
void USActionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DefaultActions.Num() > 0)
	{
		for (int i = 0; i < DefaultActions.Num(); i++)
		{
			GiveAbility(FGameplayAbilitySpec(DefaultActions[i].Action.GetDefaultObject(), DefaultActions[i].Leve));
		}
	}

	InitAbilityActorInfo(GetOwner(), GetOwner());
}

// �����ж�
bool USActionComponent::StartActionByName(AActor* InstigatorActor, FName ActionName)
{
	for (FSingleAbilityInfo ActionInfo : DefaultActions)
	{
		if (ActionInfo.Action && ActionInfo.ActionName == ActionName)
		{
			return TryActivateAbilityByClass(ActionInfo.Action);
		}
	}
	return false;
}
