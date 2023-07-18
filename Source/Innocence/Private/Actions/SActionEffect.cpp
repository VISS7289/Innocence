// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SActionEffect.h"
#include "TimerManager.h"
#include "Component/SActionComponent.h"



USActionEffect::USActionEffect()
{
	bAutoStart = true; // BUFFĬ���Զ�����
}

// BUFF����
// ���ó���ʱ��������Ч������ʱ��
void USActionEffect::StartAction_Implementation(AActor* InstigatorActor)
{
	Super::StartAction_Implementation(InstigatorActor);
	// ����ʱ��,����һ��ʱ���ֹͣ
	if (Duration > 0)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "StopAction", InstigatorActor);

		GetWorld()->GetTimerManager().SetTimer(DurationHandle, Delegate, Duration, false);
	}
	// ����Ч��������һ��ʱ���ִ������Ч��
	if (Period > 0)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "ExecutePeriodicEffect", InstigatorActor);

		GetWorld()->GetTimerManager().SetTimer(PeriodHandle, Delegate, Period, true);
	}
}

// BUFF����
// �����ʱ������ж�
void USActionEffect::StopAction_Implementation(AActor* InstigatorActor)
{
	// ��������3s����ʱ��Ҳ��3s�������ͻ���3s��ʱ��ִ��Ч���ٽ���
	if (GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle) < KINDA_SMALL_NUMBER)
	{
		ExecutePeriodicEffect(InstigatorActor);
	}

	Super::StopAction_Implementation(InstigatorActor);

	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);
	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);

	USActionComponent* Comp = GetOwningComponent();
	if (Comp)
	{
		Comp->RemoveAction(this);
	}
}

// BUFF����Ч��ִ��
// ������������
void USActionEffect::ExecutePeriodicEffect_Implementation(AActor* InstigatorActor)
{

}
