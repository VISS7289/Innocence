// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Projectile/GravitationalProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/SphereComponent.h"
AGravitationalProjectile::AGravitationalProjectile()
{
	// ��Ӿ��������
	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(RootComponent);
	ForceComp->ForceStrength = -8000000.0f;
	ForceComp->Radius = 500.0f;
}

void AGravitationalProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (OtherComp->IsSimulatingPhysics("None"))
	{
		OtherActor->Destroy();
	}*/
}//�����ӵ�������static���͵����岻���κ��޸ģ�Ҳ�����ôݻٺ�����
