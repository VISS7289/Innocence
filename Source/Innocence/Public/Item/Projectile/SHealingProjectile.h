// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Projectile/SProjectileBase.h"
#include "SHealingProjectile.generated.h"

/**
 *
 */
UCLASS()
class INNOCENCE_API ASHealingProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "HealingSphere")
		TSubclassOf<AActor> HealingClass;
	ASHealingProjectile();


protected:

	//��ײ������
	virtual void  OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//���ú���
	//virtual void Explode_Implementation() override;
};
