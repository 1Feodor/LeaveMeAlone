// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;
class UAnimMontage;


UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALMADefaultCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
	ULMAHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;


	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	ULMAHealthComponent* GetHealthComponent() const { return HealthComponent; }

private:
	float YRotation = -75.0f; // Ц отвечает за поворот камеры по оси Y.
	float ArmLength = 1400.0f; // Ц отвечает за длину штатива.
	float FOV = 55.0f; //  Ц отвечает за поле зрени€ камеры.
	void MoveForward(float Value); // Ц будет отвечать за движение персонажа по оси X.
	void MoveRight(float Value); // Ц будет отвечать за движение персонажа по оси Y.

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom", meta = (ClampMin = "1.0", ClampMax = "50.0", AllowPrivateAccess = true))
	float ZoomSpeed = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom", meta = (ClampMin = "10.0", ClampMax = "1000.0", AllowPrivateAccess = true))
	float ZoomStep = 100.0f;
	//EditAnywhere, BlueprintReadWrite, Category = Camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom", meta = (ClampMin = "200.0", ClampMax = "600.0", AllowPrivateAccess = true))
	float ZoomMin = 500.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom", meta = (ClampMin = "1800.0", ClampMax = "2200.0", AllowPrivateAccess = true))
	float ZoomMax = 2000.0f;
	bool FlagZoom{ false };
	float TargetHeight;
	void SetMouseWheelUp();
	void SetMouseWheelDown();
	void SetMouseZoom(float DeltaTime);
	void OnDeath();
	void RotationPlayerOnCursor();
	void OnHealthChanged(float NewHealth);
};
