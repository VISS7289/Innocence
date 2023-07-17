// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SWeaponComponent.h"
#include "Item/Projectile/SProjectileBase.h"

// Sets default values for this component's properties
USWeaponComponent::USWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ǹе������
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	WeaponMesh->SetSimulatePhysics(true);
	// Ĭ��7���ӵ�
	BulletNumMax = 7;


}

// Called when the game starts
void USWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// Ĭ��װ��
	AddAll();

}

// ����
TSubclassOf<AActor> USWeaponComponent::Fire()
{
	// ��֤���ӵ�
	if (BulletInGun.Num() <= 0)
	{
		return nullptr;
	}

	return BulletInGun.Pop();
	//return BulletInGun[0];
}

// װ��
void USWeaponComponent::AddBullet(TSubclassOf<AActor> ProjectileClass)
{
	// ���ܳ����ޣ�
	if (BulletInGun.Num() >= BulletNumMax)
	{
		return;
	}

	if (!ProjectileClass) {
		BulletInGun.Add(DefaultBullet);
		return;
	}

	if (ProjectileClass)
	{
		BulletInGun.Add(ProjectileClass);
	}
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
		//BulletInGun.Add(DefaultBullet);
		//BulletInGun.Init(DefaultBullet, delta);
		for (int i = 0; i < delta; i++)
		{
			BulletInGun.Add(DefaultBullet);
		}

	}
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