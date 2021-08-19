// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireRequested);

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


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnFireRequested OnFireRequested;

private:

	void FireRound();

};
