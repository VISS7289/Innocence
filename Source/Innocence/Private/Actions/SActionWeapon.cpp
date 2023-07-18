// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SActionWeapon.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "Component/SWeaponComponent.h"



USActionWeapon::USActionWeapon()
{
	HandSocketName = "Muzzle_02"; // ���ַ����������
}

// �ж��Ƿ���Թ���
bool USActionWeapon::CanStart_Implementation(AActor* InstigatorActor)
{
	if (!Super::CanStart_Implementation(InstigatorActor))
	{
		return false;
	}

	if (!WeaponComp)
	{
		WeaponComp = USWeaponComponent::GetWeaponComp(InstigatorActor);
	}

	if (ensure(WeaponComp))
	{
		return WeaponComp->CanFire();
	}

	return false;
}

// ʵʩ����
// ���ý��Ҽ��ȷ����Ļ�м�ɽӴ����ĵ�һ��Ŀ���λ�ã��ٴ����ַ���������
void USActionWeapon::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{

	TSubclassOf<AActor> ProjectileBaseClass = WeaponComp->Fire(); // ������

	if (ProjectileBaseClass)
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
}

