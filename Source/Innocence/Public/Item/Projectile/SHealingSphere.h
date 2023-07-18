// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "SHealingSphere.generated.h"



UCLASS()
class INNOCENCE_API ASHealingSphere : public AActor
{
	GENERATED_BODY()

public:

	ASHealingSphere();

	//����������İ뾶
	void SetRadius(float Radius);

	//����������ײ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USphereComponent* SphereComp;

	//����Ч�����(����)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* EffectComp;

	//�����������Ĵ����¼�
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

};
