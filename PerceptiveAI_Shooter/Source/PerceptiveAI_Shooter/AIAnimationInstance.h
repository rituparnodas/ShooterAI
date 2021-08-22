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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ENPCState>  AINPCState;

	virtual void NotifyChangeState_Implementation(ENPCState NPCState) override;
	
};
