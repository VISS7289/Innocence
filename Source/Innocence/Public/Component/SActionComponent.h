// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "SActionComponent.generated.h"


class USAction;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INNOCENCE_API USActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// �����ı�ǩ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
		FGameplayTagContainer ActiveGameplayTags;

	// ����ж�
	UFUNCTION(BlueprintCallable, Category = "Action")
		void AddAction(AActor* InstigatorActor, TSubclassOf<USAction> ActionClass);

	// �Ƴ��ж�
	UFUNCTION(BlueprintCallable, Category = "Action")
		void RemoveAction(USAction* ActionToRemove);

	// �����ж�
	UFUNCTION(BlueprintCallable, Category = "Action")
		bool StartActionByName(AActor* InstigatorActor, FName ActionName);

	// �����ж�
	UFUNCTION(BlueprintCallable, Category = "Action")
		bool StopActionByName(AActor* InstigatorActor, FName ActionName);

	// Sets default values for this component's properties
	USActionComponent();

protected:

	UFUNCTION(Server, Reliable)
		void ServerStartAction(AActor* InstigatorActor, FName ActionName);

	UFUNCTION(Server, Reliable)
		void ServerStopAction(AActor* InstigatorActor, FName ActionName);

	UPROPERTY(EditAnywhere, Category = "Action")
		TArray<TSubclassOf<USAction>> DefaultActions;

	UPROPERTY(Replicated)
		TArray<USAction*> Actions; // �����ж�

	// Called when the game starts
	virtual void BeginPlay() override;

public:

	bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	// Debug�鿴Action״̬
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
