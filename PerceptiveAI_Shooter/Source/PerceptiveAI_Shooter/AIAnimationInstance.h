// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InterfaceAIHelper.h"
#include "Animation/AnimInstance.h"
#include "AIAnimationInstance.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API UAIAnimationInstance : public UAnimInstance, public IInterfaceAIHelper
{
	GENERATED_BODY()

public:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ENPCState>  AINPCState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsAiming = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AimPitch = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AimYaw = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsInAir = false;

	virtual void NotifyChangeState_Implementation(ENPCState NPCState) override;
	virtual void ModifyAimingStance_Implementation(bool IsAiming) override;
};
