// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "Math/Vector2D.h"
#include "Component/SAttributeComponent.h"
#include "Component/SWeaponComponent.h"
#include "Component/SActionComponent.h"



// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��ӵ��ɱ����
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true; // �������Pawn��תͬ��
	// ���������
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	// ����������
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	// ����������
	WeaponComp = CreateDefaultSubobject<USWeaponComponent>("WeaponComp");
	// ���ASC
	AbilityComp = CreateDefaultSubobject<USActionComponent>(TEXT("AbilitySystem"));

	GetCharacterMovement()->bOrientRotationToMovement = true;//���˶������޸Ľ�ɫ�ĳ���
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// �����ı�ʱ�����ж�
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASCharacter::GetHealthChange);
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	// �������ӳ��
	APlayerController* MyPlayerController = Cast<APlayerController>(Controller);
	if (MyPlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MyPlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		// ��Ծ
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		// �ƶ�
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASCharacter::Move);
		// ��ɫ�ӽ�
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASCharacter::Look);
		// ��ͨ����
		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Triggered, this, &ASCharacter::PrimaryAttack);
		// ���
		EnhancedInputComponent->BindAction(PrimaryDashAction, ETriggerEvent::Triggered, this, &ASCharacter::PrimaryDash);
		// ������ʼ
		EnhancedInputComponent->BindAction(AccumulateDown, ETriggerEvent::Started, this, &ASCharacter::AccumulateStart);
		// ��������
		EnhancedInputComponent->BindAction(AccumulateRelease, ETriggerEvent::Triggered, this, &ASCharacter::AccumulateEnd);
		// ����
		EnhancedInputComponent->BindAction(PrimaryReloadAction, ETriggerEvent::Triggered, this, &ASCharacter::PrimaryReload);
		// �ӵ������л�
		EnhancedInputComponent->BindAction(BulletTypeRightAction, ETriggerEvent::Triggered, this, &ASCharacter::BulletTypeRight);
		// �ӵ������л�
		EnhancedInputComponent->BindAction(BulletTypeLeftAction, ETriggerEvent::Triggered, this, &ASCharacter::BulletTypeLeft);

	}
	
}

// ��ɫ�ƶ�����
void ASCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

// ��ɫ��꿴����
void ASCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

// ��ͨ����
void ASCharacter::PrimaryAttack()
{
	AbilityComp->StartActionByName(this, "BaseAttack");
}

// ���
void ASCharacter::PrimaryDash()
{
	AbilityComp->StartActionByName(this, "BaseDash");
}

// ������ʼ
void ASCharacter::AccumulateStart()
{
	UE_LOG(LogTemp, Log, TEXT("Accumulate Start"));
	AbilityComp->StartActionByName(this, "Accumulate");
}
// ��������
void ASCharacter::AccumulateEnd()
{
	UE_LOG(LogTemp, Log, TEXT("Accumulate End"));
	AbilityComp->StopActionByName(this, "Accumulate");
}

// ����
void ASCharacter::PrimaryReload()
{
	UE_LOG(LogTemp, Log, TEXT("Reload Start"));
	AbilityComp->StartActionByName(this, "Reload");
}

// �ӵ������л�
void ASCharacter::BulletTypeRight()
{
	UE_LOG(LogTemp, Log, TEXT("BulletTypeRight"));
	AbilityComp->StartActionByName(this, "BulletTypeRight");
}
// �ӵ������л�
void ASCharacter::BulletTypeLeft()
{
	UE_LOG(LogTemp, Log, TEXT("BulletTypeLeft"));
	AbilityComp->StartActionByName(this, "BulletTypeLeft");
}

// �����ж�
void ASCharacter::GetHealthChange(AActor* InstigatordActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// ȷ���������������
	if (NewHealth <= 0.0f && Delta <= 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);

		SetLifeSpan(5.0f);
	}
}
