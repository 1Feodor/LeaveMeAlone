// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Components/LMAHealthComponent.h"
#include "Enemy/LMAEnemyCharacter.h"

// Sets default values
ALMAEnemyCharacter::ALMAEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponentEnemy = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");

}

// Called when the game starts or when spawned
void ALMAEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//HealthComponent->OnHealthChanged.AddUObject(this, &ALMAEnemyCharacter::OnHealthChanged11);
	
}

// Called every frame
void ALMAEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALMAEnemyCharacter::OnHealthChanged11(float NewHealth)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"), NewHealth));
}
