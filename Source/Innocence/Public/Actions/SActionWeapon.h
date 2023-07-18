// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/SAction.h"
#include "SActionWeapon.generated.h"

class USWeaponComponent;

/**
 * 
 */
UCLASS()
class INNOCENCE_API USActionWeapon : public USAction
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		USWeaponComponent* WeaponComp;

	UPROPERTY(EditAnywhere, Category = "Attack")
		UAnimMontage* AttackAnim; // ��ͨ������̫��

	UPROPERTY(EditAnywhere, Category = "Attack")
		FName HandSocketName; // ����������������

	FTimerHandle TimerHandle_PrimaryAttack; // ��ʱ

	// ʵʩ����
	UFUNCTION()
		virtual void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);

public:

	virtual bool CanStart_Implementation(AActor* InstigatorActor) override;

	USActionWeapon();
	
};
