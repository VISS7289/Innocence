// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SAction_Accumulate.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"


USAction_Accumulate::USAction_Accumulate()
{
    MaxAccumulateTime = 2.0f;
    CameraAccumulate = 100.0f;
}

// ��ʼ��Timeline
void USAction_Accumulate::SetupTimeline()
{
    FOnTimelineFloat TimelineProgressFunction;
    TimelineProgressFunction.BindUFunction(this, FName("TimelineProgressFunction"));

    CurveTimeline.SetLooping(false);
    CurveTimeline.SetTimelineLength(MaxAccumulateTime);
    if (ensure(Curve))
    {
        CurveTimeline.AddInterpFloat(Curve, TimelineProgressFunction);
        HasInit = true;
    }
}

// TimeLine���Ź����о۽����
void USAction_Accumulate::TimelineProgressFunction(float Value)
{
    CurrentAccumulateTime = Value;

    NowPos = UKismetMathLibrary::VLerp(StartPos, EndPos, Value);
    SpringArmComp->SocketOffset = NowPos;
}

// Action��ʼ
void USAction_Accumulate::StartAction_Implementation(AActor* InstigatorActor)
{
    Super::StartAction_Implementation(InstigatorActor);
    // ��ʼ���������
    if (!SpringArmComp)
    {
        SpringArmComp = Cast<USpringArmComponent>(InstigatorActor->GetComponentByClass(USpringArmComponent::StaticClass()));
        if (ensure(SpringArmComp))
        {

            StartPos = SpringArmComp->SocketOffset;
            EndPos = StartPos + FVector(1, 0, 0) * CameraAccumulate;
        }
    }
    if (!HasInit)
    {
        SetupTimeline();
    }

    // ����TiemLine
    CurveTimeline.PlayFromStart();
}

// Action����
void USAction_Accumulate::StopAction_Implementation(AActor* InstigatorActor)
{
    Super::StopAction_Implementation(InstigatorActor);
    // ֹͣTiemLine
    CurveTimeline.Stop();
    // �����ӵ�
    ACharacter* Character = Cast<ACharacter>(InstigatorActor);
    if (Character)
    {
        AttackDelay_Elapsed(Character);
    }
    // ����ָ�
    SpringArmComp->SocketOffset = StartPos;
}

// ÿTick����Timeline
void USAction_Accumulate::Tick(float DeltaTime)
{
    CurveTimeline.TickTimeline(DeltaTime);
}

