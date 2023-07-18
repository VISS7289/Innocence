// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SWeaponComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Item/Projectile/SProjectileBase.h"

// Sets default values for this component's properties
USWeaponComponent::USWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ǹе������
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	WeaponMesh->SetSimulatePhysics(true);
	// Ĭ��7���ӵ�
	BulletNumMax = 7;


}

// ����
// ѡ�����е��ӵ����ͣ����ӵ����͸�λ
TSubclassOf<AActor> USWeaponComponent::Fire()
{
	// ��֤���ӵ�
	if (BulletInGun.Num() <= 0)
	{
		return nullptr;
	}

	BulletInGun[0] = BulletType[NowBulletType];
	NowBulletType = 0;

	return BulletPop();
}

TSubclassOf<AActor> USWeaponComponent::BulletPop()
{
	TSubclassOf<AActor> PopBulletValue = BulletInGun[0];
	for (int i = 0; i < BulletInGun.Num() - 1; i++)
	{
		BulletInGun[i] = BulletInGun[i + 1];
	}
	BulletInGun.Pop();
	return PopBulletValue;
}

// װ��
void USWeaponComponent::AddBullet(TSubclassOf<AActor> ProjectileClass)
{
	// ���ܳ����ޣ�
	if (BulletInGun.Num() >= BulletNumMax)
	{
		return;
	}
	// ����������������������������������������������������������������������������������������������������������������������
	if (ProjectileClass)
	{
		BulletInGun.Add(ProjectileClass);
	}
	// ����������������������������������������������������������������������������������������������������������������������
}

// װ��
void USWeaponComponent::AddAll()
{
	// ���ܳ����ޣ�
	int32 delta = BulletNumMax - BulletInGun.Num();
	if (delta <= 0)
	{
		return;
	}

	if (ensure(DefaultBullet))
	{
		// ����������������������������������������������������������������������������������������������������������������������
		for (int i = 0; i < delta; i++)
		{
			BulletInGun.Add(DefaultBullet);
		}
		// ����������������������������������������������������������������������������������������������������������������������
	}
}


// Called when the game starts
void USWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	DefaultBullet = BulletType[0];
	AddAll();

}


// Called every frame
void USWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

USWeaponComponent* USWeaponComponent::GetWeaponComp(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USWeaponComponent>(FromActor->GetComponentByClass(USWeaponComponent::StaticClass()));
	}

	return nullptr;
}

bool USWeaponComponent::CanFire()
{
	return BulletInGun.Num() > 0;
}

// ������ת
void USWeaponComponent::BulletTypeRight()
{
	NowBulletType = (NowBulletType + 1) % BulletType.Num();
}

// ������ת
void USWeaponComponent::BulletTypeLeft()
{
	NowBulletType = (NowBulletType + BulletType.Num() - 1) % BulletType.Num();
}

TSubclassOf<AActor> USWeaponComponent::GetDefaultBullet()
{
	return DefaultBullet;
}
