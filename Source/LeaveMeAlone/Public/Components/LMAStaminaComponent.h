// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAStaminaComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnStamina)
DECLARE_MULTICAST_DELEGATE_OneParam(FIsStaminaTime, bool);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULMAStaminaComponent();

	FOnStamina OnStamina;
	FIsStaminaTime IsStaminaTime;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint", meta = (ClampMin = "10.0", ClampMax = "500.0", AllowPrivateAccess = true))
	float MaxStaminaSprint = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint", meta = (ClampMin = "0.05", ClampMax = "1.0", AllowPrivateAccess = true))
	float SpawnTimerRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint", meta = (ClampMin = "0.05", ClampMax = "1.0", AllowPrivateAccess = true))
	float DestroyTimerRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint", meta = (ClampMin = "0.1", ClampMax = "10.0", AllowPrivateAccess = true))
	float StaminaMinus = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint", meta = (ClampMin = "0.1", ClampMax = "10.0", AllowPrivateAccess = true))
	float StaminaPlus = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint", meta = (ClampMin = "0", ClampMax = "100", AllowPrivateAccess = true))
	int32 PausaStamina = 30;

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
	int32 StaminaPlusPause = 0;
};
