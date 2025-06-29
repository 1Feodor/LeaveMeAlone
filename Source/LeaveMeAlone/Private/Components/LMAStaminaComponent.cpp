// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Components/LMAStaminaComponent.h"
#include "TimerManager.h"


// Sets default values for this component's properties
ULMAStaminaComponent::ULMAStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void ULMAStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	this->StaminaSprint = this->MaxStaminaSprint;
	
}


// Called every frame
void ULMAStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULMAStaminaComponent::OnTimeToSpawn()
{
	if (this->StaminaSprint < this->MaxStaminaSprint)
	{
		if (StaminaPlusPause < PausaStamina)
		{
			++StaminaPlusPause;
		}
		else
		{
			this->StaminaSprint = FMath::Clamp(this->StaminaSprint + this->StaminaPlus, 0.0f, this->MaxStaminaSprint);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Health = %f"), this->StaminaSprint));
		}
		
	}
	else
	{
		StaminaPlusPause = 0;
		GetWorld()->GetTimerManager().ClearTimer(this->SpawnTimerStamina);	
	}
}

void ULMAStaminaComponent::OnTimeToDestroy()
{
	if (this->StaminaSprint > 0.0f)
	{
		this->StaminaSprint = FMath::Clamp(this->StaminaSprint - this->StaminaMinus, 0.0f, this->MaxStaminaSprint);
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"), this->StaminaSprint));
	}
	else 
	{
		GetWorld()->GetTimerManager().ClearTimer(this->DestroyTimerStamina);
		OnStamina.Broadcast();
		IsStaminaTime.Broadcast(true);
	}
	
}

void ULMAStaminaComponent::SprintTrue()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(this->SpawnTimerStamina))
	{
		StaminaPlusPause = 0;
		GetWorld()->GetTimerManager().ClearTimer(this->SpawnTimerStamina);
	}
	if (!GetWorld()->GetTimerManager().IsTimerActive(this->DestroyTimerStamina))
	{
		IsStaminaTime.Broadcast(false);
		GetWorld()->GetTimerManager().SetTimer(this->DestroyTimerStamina, this, &ULMAStaminaComponent::OnTimeToDestroy, this->DestroyTimerRate, true);
	}
}

void ULMAStaminaComponent::SprintFalse()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(this->DestroyTimerStamina))
	{
		GetWorld()->GetTimerManager().ClearTimer(this->DestroyTimerStamina);
		IsStaminaTime.Broadcast(true);
	}
	if (!GetWorld()->GetTimerManager().IsTimerActive(this->SpawnTimerStamina) && this->StaminaSprint < this->MaxStaminaSprint)
	{
		GetWorld()->GetTimerManager().SetTimer(this->SpawnTimerStamina, this, &ULMAStaminaComponent::OnTimeToSpawn, this->SpawnTimerRate, true);
	}
}