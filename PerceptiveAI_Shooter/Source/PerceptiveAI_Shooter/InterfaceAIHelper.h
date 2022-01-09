// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AIFunctionLibrary.h"
#include "AIFunctionLibrary.h"
#include "PatrolRoute.h"
#include "InterfaceAIHelper.generated.h"

// This class does not need to be modified.
//UINTERFACE(meta = (CannotImplementInterfaceInBlueprint = true))
UINTERFACE(MinimalAPI)
class UInterfaceAIHelper : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class PERCEPTIVEAI_SHOOTER_API IInterfaceAIHelper
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:

	UFUNCTION(BlueprintNativeEvent,  BlueprintCallable)
		bool GetIsDead();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void NotifyChangeState(ENPCState NPCState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool GetTeamID(); // True If Player

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ModifyAimingStance(bool bIsAimingParam);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ModifyMovementSpeed(ENPCState NPCState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		class APatrolRoute* GetPatrolRoute();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		float GetWeaponRange();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		class AWeaponBase* GetWeapon();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TryShootEquipWeapon();
};
