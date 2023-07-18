// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SWeakness.h"
#include "Components/StaticMeshComponent.h"
#include "Component/SAttributeComponent.h"

// Sets default values
ASWeakness::ASWeakness()
{
	// ���������
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(false);
	MeshComp->SetCollisionProfileName("Weakness");
	// �������������
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASWeakness::GetHealthChange);

	DamageMultiply = 2.0f;
}

void ASWeakness::SetAttrComp(USAttributeComponent* AttrComp)
{
	OwnerAttributeComp = AttrComp;
}


// �����˺�����
// ��ɫ�ܵ��˺�������ò�λΪ���㣬׷���˺�
void ASWeakness::GetHealthChange(AActor* InstigatordActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta > 0)
	{
		return;
	}

	// ��֤���㱾�����Ե��޵�
	AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax());

	if (InstigatordActor == GetInstigator())
	{
		return;
	}

	OwnerAttributeComp->ApplyHealthChange(InstigatordActor, Delta * DamageMultiply);

}