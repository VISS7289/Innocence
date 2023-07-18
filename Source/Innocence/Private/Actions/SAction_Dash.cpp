// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SAction_Dash.h"
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
        StopAction(DashActor);
    }
}

// TimeLine���Ž���
void USAction_Dash::TimelineCallbackFunction()
{
    StopAction(DashActor);
}

// ��ʼAction
void USAction_Dash::StartAction_Implementation(AActor* InstigatorActor)
{
    Super::StartAction_Implementation(InstigatorActor);
    // ��ʼ��
    if (!DashActor)
    {
        DashActor = InstigatorActor;
    }
    if (!HasInit)
    {
        SetupTimeline();
    }

    // ��������յ�
    StartPos = InstigatorActor->GetActorLocation();

    FVector Fwd = InstigatorActor->GetActorForwardVector();
    EndPos = StartPos + Fwd * DashLength;

    // ����TiemLine
    CurveTimeline.PlayFromStart();
}

// ÿTick����Timeline
void USAction_Dash::Tick(float DeltaTime)
{
    CurveTimeline.TickTimeline(DeltaTime);
}