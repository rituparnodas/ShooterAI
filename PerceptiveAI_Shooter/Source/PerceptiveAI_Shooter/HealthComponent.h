// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageTaken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERCEPTIVEAI_SHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthData")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthData")
		float MaxHealth;

	UFUNCTION()
		void OnReceivingDamage(AActor* DamagedActor, float Damage,
			const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(BlueprintAssignable)
		FOnDamageTaken OnDamageTaken;

	UPROPERTY(BlueprintAssignable)
		FOnDamageTaken OnDeath;

	UFUNCTION(BlueprintPure)
		bool IsDead();
};
