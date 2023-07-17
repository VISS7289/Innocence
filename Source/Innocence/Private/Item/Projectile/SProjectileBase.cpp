// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Projectile/SProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Component/SAttributeComponent.h"

// Sets default values
ASProjectileBase::ASProjectileBase()
{

	//�����������Ϊ�����
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	//����Ч�������ʵ����
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

	//�����˶����
	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("MoveComp");
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->InitialSpeed = 4000;

	//Ĭ���˺�10��
	ProjectileDamage = -10.0f;

	//Ĭ���ӵ��������ʮ�����������
	DestoryPrjDelay = 10.0f;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	//���Է�����
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	//�����������ټ�ʱ��
	GetWorldTimerManager().SetTimer(FTimerHandle_DestoryPrjDelay, this, &ASProjectileBase::DestoryPrj, DestoryPrjDelay);
}

// Called every frame
void ASProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASProjectileBase::DestoryPrj()
{
	GetWorldTimerManager().ClearTimer(FTimerHandle_DestoryPrjDelay);
	Destroy();
}

void ASProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//ע�������ײ�¼�������
	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectileBase::OnActorHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASProjectileBase::OnActorOverlap);
}

void ASProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void ASProjectileBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{

		Explode();
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(GetInstigator(), ProjectileDamage);
			Destroy();
		}
	}
}

void ASProjectileBase :: Explode_Implementation()
{
	if (ensure(!IsPendingKill())) {
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		DestoryPrj();
	}
}


