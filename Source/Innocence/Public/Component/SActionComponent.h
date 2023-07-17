// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SActionComponent.generated.h"


USTRUCT()
struct FSingleAbilityInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Action;

	UPROPERTY(EditDefaultsOnly)
	int32 Leve;

	UPROPERTY(EditDefaultsOnly)
	FName ActionName;

};

/**
 * 
 */
UCLASS()
class INNOCENCE_API USActionComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	// �����ж�
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StartActionByName(AActor* InstigatorActor, FName ActionName);

	//// �����ж�
	//UFUNCTION(BlueprintCallable, Category = "Action")
	//bool StopActionByName(AActor* InstigatorActor, FName ActionName);

protected:

	UPROPERTY(EditAnywhere, Category = "Action")
	TArray<FSingleAbilityInfo> DefaultActions;

	// Called when the game starts
	virtual void BeginPlay() override;
	
};
