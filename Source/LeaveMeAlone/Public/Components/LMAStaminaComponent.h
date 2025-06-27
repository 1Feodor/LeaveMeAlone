// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAStaminaComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnStamina)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULMAStaminaComponent();

	FOnStamina OnStamina;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxStaminaSprint = 100.0f;

	UPROPERTY(EditAnywhere)
	float SpawnTimerRate = 0.1f;

	UPROPERTY(EditAnywhere)
	float DestroyTimerRate = 0.1f;

	UPROPERTY(EditAnywhere)
	float StaminaMinus = 5.0f;

	UPROPERTY(EditAnywhere)
	float StaminaPlus = 1.0f;

	UPROPERTY(EditAnywhere)
	int8 StaminaPlusPause = 0;

	FTimerHandle SpawnTimerStamina;
	FTimerHandle DestroyTimerStamina;

	void OnTimeToSpawn();
	void OnTimeToDestroy();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetStaminaSprint() const { return StaminaSprint; }

	void SprintTrue();
	void SprintFalse();

private:
	float StaminaSprint = 0.0f;
};
