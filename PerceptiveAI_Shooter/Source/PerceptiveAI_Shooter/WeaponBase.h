// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireRequested);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFired);

UCLASS()
class PERCEPTIVEAI_SHOOTER_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USceneComponent* SceneRoot = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USkeletalMeshComponent* WeaponVisual = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* MuzzleLocation = nullptr;

	UPROPERTY(EditAnywhere, Category = "WeaponData")
		UClass* BulletClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "WeaponData")
		class USoundBase* FireSoundClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "WeaponData")
		float WeaponRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "WeaponData")
		float WeaponDamage = 10.f;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CycleRate = 0.1f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void FireRequested();

	UPROPERTY(BlueprintAssignable)
	FOnFireRequested OnFireRequested;

	UPROPERTY(BlueprintAssignable)
		FOnWeaponFired OnWeaponFired;

	float GetWeaponRange() { return WeaponRange; }

	void ResetDOOnce();


private:

	void FireRound();
	bool DoOnce_COND = true;
};
