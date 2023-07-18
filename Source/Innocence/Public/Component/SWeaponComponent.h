// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SWeaponComponent.generated.h"

// ע���ӵ��л��ı��¼�
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBulletChanged, int32, NewBullet);

class UStaticMeshComponent; // ��̬������

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INNOCENCE_API USWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USWeaponComponent();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	static USWeaponComponent* GetWeaponComp(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	TSubclassOf<AActor> Fire(); // ����

protected:

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UStaticMeshComponent* WeaponMesh; // ǹе������

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<AActor> DefaultBullet; // Ĭ���ӵ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	int32 BulletNumMax; // �ӵ�����

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	TArray<TSubclassOf<AActor>> BulletInGun; // ǹе���ִ��ӵ�

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AddBullet(TSubclassOf<AActor> ProjectileClass); // װ��

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AddAll(); // װ��

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnBulletChanged OnBulletChangedRight; // �ӵ�����ı��¼�

	UPROPERTY(BlueprintAssignable)
	FOnBulletChanged OnBulletChangedLeft; // �ӵ�����ı��¼�

		
};
