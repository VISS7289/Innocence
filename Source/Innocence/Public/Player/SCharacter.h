// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" 
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "SCharacter.generated.h"

class USpringArmComponent; // ���ɱ����
class UCameraComponent; // ��������
class USAttributeComponent; // �������
class USWeaponComponent; // �������
class USActionComponent; // �ж����

// �������
class UInputMappingContext;
class UInputAction;
class UInputComponent;

UCLASS()
class INNOCENCE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp; // ���ɱ����

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp; // ��������

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USAttributeComponent* AttributeComp; // �������

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USWeaponComponent* WeaponComp; // �������

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USActionComponent* AbilityComp; // ASC


protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext; // ����ӳ��

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction; // ��Ծ

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction; // �ƶ�

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction; // ��ɫ�ӽ�

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PrimaryAttackAction; // �����ͨ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PrimaryDashAction; // ���

	// �ƶ�
	void Move(const FInputActionValue& Value);

	// ��ɫ�ӽ�
	void Look(const FInputActionValue& Value);

	// ��ͨ����
	void PrimaryAttack();

	// ���
	void PrimaryDash();

protected:

	// �����ж�
	UFUNCTION()
	void GetHealthChange(AActor* InstigatordActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ע���¼��󶨺���
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
