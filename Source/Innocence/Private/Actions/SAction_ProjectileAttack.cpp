// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SAction_ProjectileAttack.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"



USAction_ProjectileAttack::USAction_ProjectileAttack()
{
	HandSocketName = "Muzzle_02"; // ���ַ����������
}

// ��ʼԶ�̹����ж�
// ��ȡ��ִ�н�ɫ�󣬽������ִ�иý�ɫ���Ź�����̫�沢��ʱ��������
void USAction_ProjectileAttack::StartAction_Implementation(AActor* InstigatorActor)
{
	Super::StartAction_Implementation(InstigatorActor);

	ACharacter* Character = Cast<ACharacter>(InstigatorActor);
	if (Character)
	{
		if (ensure(AttackAnim))
		{
			Character->PlayAnimMontage(AttackAnim);

			if (Character->HasAuthority())
			{
				FTimerHandle TimerHandle_AttackDelay;
				FTimerDelegate Delegate;
				Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

				float AttackDelay = 0.2f;

				GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackDelay, false);
			}

		}
	}

}

// ʵʩ����
// ���ý��Ҽ��ȷ����Ļ�м�ɽӴ����ĵ�һ��Ŀ���λ�ã��ٴ����ַ���������
void USAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if (ensureAlways(ProjectileBaseClass))
	{
		// ����λ��
		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);

		// ���Ҽ��������
		FCollisionShape Shape;
		Shape.SetSphere(20.0f);
		// ������ײ
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);
		// ���ü����
		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);
		// ��������յ�
		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();
		FVector TraceEnd = TraceStart + (InstigatorCharacter->GetControlRotation().Vector() * 5000);
		// ���Ҽ��
		FHitResult Hit;
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			TraceEnd = Hit.ImpactPoint;
		}
		// ���ݼ����������ת����
		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

		// ��ɫǰ��λ��
		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		// �������������
		FActorSpawnParameters SpawnParames;
		SpawnParames.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParames.Instigator = InstigatorCharacter;
		// ����������
		GetWorld()->SpawnActor<AActor>(ProjectileBaseClass, SpawnTM, SpawnParames);
	}

	StopAction(InstigatorCharacter);
}