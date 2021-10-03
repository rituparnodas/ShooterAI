// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InterfaceAIHelper.h"
#include "GameFramework/Character.h"
#include "AICharacterBase.generated.h"

UCLASS()
class PERCEPTIVEAI_SHOOTER_API AAICharacterBase : public ACharacter, public IInterfaceAIHelper
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UHealthComponent* HealthComp = nullptr;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(BlueprintReadWrite, Category = "Weapons")
	class AWeaponBase* Weapon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	class APatrolRoute* PatrolRoute = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		class UAnimMontage* AnimMontageAsset = nullptr;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void HandleDeath();

	UFUNCTION()
		void OnDamageTaken();

	virtual bool GetIsDead_Implementation() override;
	virtual void NotifyChangeState_Implementation(ENPCState NPCState) override;
	virtual bool GetTeamID_Implementation() override;
	virtual void ModifyMovementSpeed_Implementation(ENPCState NPCState) override;
	virtual class APatrolRoute* GetPatrolRoute_Implementation() override;
	virtual void ModifyAimingStance_Implementation(bool bIsAimingParam) override;

private:

	bool DoOnce_COND = true;
};
