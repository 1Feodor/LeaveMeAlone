// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

DECLARE_MULTICAST_DELEGATE(FZeroBullets)

UCLASS()
class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALMABaseWeapon();

	void Fire();
	void OffFire();
	void ChangeClip();
	bool BulletsMax() const;

	FZeroBullets ZeroBullets;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon AmmoWeapon{ 5, 0, true };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint", meta = (ClampMin = "0.05", ClampMax = "1.0", AllowPrivateAccess = true))
	float SpeedShoot = 0.5f;

	void Shoot();
	void AvtoShoot();
	void AvtoFire();
	void OneShoot();

	FTimerHandle TimerShoot;

	void DecrementBullets();
	bool IsCurrentClipEmpty() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FAmmoWeapon GetCurrentAmmoWeapon() const { return CurrentAmmoWeapon; }

private:
	FAmmoWeapon CurrentAmmoWeapon;
};
