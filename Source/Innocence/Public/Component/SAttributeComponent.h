// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

// ���Ըı��¼�
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigatordActor, USAttributeComponent*, OwningComp, float, NewValue, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INNOCENCE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static USAttributeComponent* GetAttributes(AActor* FromActor);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health; // ����ֵ

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float HealthMax; // �������ֵ

public:	

	// �Ƿ����
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool IsAlive() const;

	// �Ƿ���Ѫ
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool IsFullHealth() const;

	// ����ֵ�ı�
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool ApplyHealthChange(AActor* InstigatordActor, float Delta);

	// ����ֵ��ȡ
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealth();

	// �������ֵ��ȡ
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealthMax();

	// ����ֵ�ı��¼�
	UPROPERTY(BlueprintAssignable)
		FOnAttributeChanged OnHealthChanged;

		
};
