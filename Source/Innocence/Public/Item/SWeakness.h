// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeakness.generated.h"

class USAttributeComponent; // ����������
class UStaticMeshComponent; // ��̬������

UCLASS()
class INNOCENCE_API ASWeakness : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASWeakness();

	void SetAttrComp(USAttributeComponent* AttrComp);

protected:

	UPROPERTY(VisibleAnywhere)
	USAttributeComponent* AttributeComp; // �����������

	UPROPERTY()
	USAttributeComponent* OwnerAttributeComp; // �����������

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp; // ��̬������

	UPROPERTY(EditDefaultsOnly)
	float DamageMultiply;

	// �����˺�����
	UFUNCTION()
	void GetHealthChange(AActor* InstigatordActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

};
