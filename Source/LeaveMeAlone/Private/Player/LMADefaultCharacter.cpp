// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Player/LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/LMAHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"


// Sets default values
ALMADefaultCharacter::ALMADefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true); //– данное условие не позволит нашей камере
		//поворачиваться в момент поворота персонажа.В жанре Top - Down Shooter, камера обычно находится
		//статично над игроком.
	SpringArmComponent->TargetArmLength = ArmLength;
	SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));// -структура FRotator хранит аргументы
		//в следующей последовательности : Pitch, Yaw, Roll.Так как нам необходимо определить значения по оси Y, мы
		//устанавливаем Pitch аргумент.
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetFieldOfView(FOV);
	CameraComponent->bUsePawnControlRotation = false; //– данное условие запрещаем камере вращаться
		//относительно SpringArmComponent.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");
}

// Called when the game starts or when spawned
void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize,
			FVector(0));
	}
	this->TargetHeight = SpringArmComponent->TargetArmLength;

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &ALMADefaultCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ALMADefaultCharacter::OnHealthChanged);
}

// Called every frame
void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!(HealthComponent->IsDead()))
	{
		RotationPlayerOnCursor();
	}

	if(this->FlagZoom)
	{
		this->SetMouseZoom(DeltaTime);
	}
}

// Called to bind functionality to input
void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);
	PlayerInputComponent->BindAction("SetMouseWheelUp", IE_Pressed, this, &ALMADefaultCharacter::SetMouseWheelUp);
	PlayerInputComponent->BindAction("SetMouseWheelDown", IE_Pressed, this, &ALMADefaultCharacter::SetMouseWheelDown);
}

void ALMADefaultCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}
void ALMADefaultCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ALMADefaultCharacter::SetMouseWheelUp()
{
	if(SpringArmComponent->TargetArmLength > this->ZoomMin)
	{
		this->TargetHeight = FMath::Clamp(this->TargetHeight - this->ZoomStep, this->ZoomMin, this->ZoomMax);
		this->FlagZoom = true;
	}
	
}

void ALMADefaultCharacter::SetMouseWheelDown()
{
	if (SpringArmComponent->TargetArmLength < this->ZoomMax)
	{
		this->TargetHeight = FMath::Clamp(this->TargetHeight + this->ZoomStep, this->ZoomMin, this->ZoomMax);
		this->FlagZoom = true;
	}
}

void ALMADefaultCharacter::SetMouseZoom(float DeltaTime)
{
	if (SpringArmComponent->TargetArmLength > this->TargetHeight)
	{
		SpringArmComponent->TargetArmLength -= this->ZoomSpeed * DeltaTime * 100;
		if (SpringArmComponent->TargetArmLength <= this->TargetHeight)
		{
			SpringArmComponent->TargetArmLength = this->TargetHeight;
			this->FlagZoom = false;
		}
	}
	else if (SpringArmComponent->TargetArmLength < this->TargetHeight)
	{
		SpringArmComponent->TargetArmLength += this->ZoomSpeed * DeltaTime * 100;
		if (SpringArmComponent->TargetArmLength >= this->TargetHeight)
		{
			SpringArmComponent->TargetArmLength = this->TargetHeight;
			this->FlagZoom = false;
		}
	}
}

void ALMADefaultCharacter::OnDeath()
{
	CurrentCursor->DestroyRenderState_Concurrent();

	PlayAnimMontage(DeathMontage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ALMADefaultCharacter::RotationPlayerOnCursor()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
		if (CurrentCursor)
		{
			CurrentCursor->SetWorldLocation(ResultHit.Location);
		}
	}
}

void ALMADefaultCharacter::OnHealthChanged(float NewHealth)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"), NewHealth));
}