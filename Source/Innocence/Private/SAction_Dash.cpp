// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_Dash.h"
#include "Kismet/KismetMathLibrary.h"


USAction_Dash::USAction_Dash()
{
    DashLength = 500.0f; // ��̾���
}

// ���TimeLine����
void USAction_Dash::SetupTimeline()
{
    FOnTimelineEvent TimelineCallback;
    TimelineCallback.BindUFunction(this, FName("TimelineCallbackFunction"));

    FOnTimelineFloat TimelineProgressFunction;
    TimelineProgressFunction.BindUFunction(this, FName("TimelineProgressFunction"));

    CurveTimeline.SetLooping(false);
    CurveTimeline.SetTimelineLength(0.2f);
    CurveTimeline.SetTimelineFinishedFunc(TimelineCallback);
    if (ensure(Curve))
    {
        CurveTimeline.AddInterpFloat(Curve, TimelineProgressFunction);
        HasInit = true;
    }
}

// TimeLine���Ź�����
void USAction_Dash::TimelineProgressFunction(float Value)
{
    // ��ֵ
    NowPos = UKismetMathLibrary::VLerp(StartPos, EndPos, Value);
    // ʵʱ�������λ��
    if (!DashActor->SetActorLocation(NowPos, true))
    {
        CurveTimeline.Stop();
        //StopAction(DashActor);
    }
}

// TimeLine���Ž���
void USAction_Dash::TimelineCallbackFunction()
{
    //StopAction(DashActor);
}

// ��ʼAction
void USAction_Dash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    //ACharacter* InstigatorCharacter = Cast<ACharacter>(ActorInfo->OwnerActor);
    //if (!InstigatorCharacter)
    //{
    //    return;
    //}

    if (!HasInit)
    {
        SetupTimeline();
    }

    // ��������յ�
    StartPos = ActorInfo->OwnerActor->GetActorLocation();

    FVector Fwd = ActorInfo->OwnerActor->GetActorForwardVector();
    EndPos = StartPos + Fwd * DashLength;

    // ����TiemLine
    CurveTimeline.PlayFromStart();
}

// ÿTick����Timeline
void USAction_Dash::Tick(float DeltaTime)
{
    CurveTimeline.TickTimeline(DeltaTime);
}
