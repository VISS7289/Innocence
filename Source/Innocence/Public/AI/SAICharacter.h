// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class USAttributeComponent; // �������
class UUserWidget; // UI
class USWorldUserWidget; // AIѪ��UI

UCLASS()
class INNOCENCE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAICharacter();

protected:

	USWorldUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> HealthBarWidgetClass; // ����Ѫ��UI

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		USAttributeComponent* AttributeComp; // �������

	// ע���¼��ص�����
	virtual void PostInitializeComponents() override;

	// ����ֵ�ı�ʱ
	UFUNCTION()
		void GetHealthChange(AActor* InstigatordActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

};
