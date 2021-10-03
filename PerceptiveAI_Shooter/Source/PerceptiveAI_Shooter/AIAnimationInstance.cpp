// Copyright DevDasTour 2021 All Right Reserved.


#include "AIAnimationInstance.h"
#include "AICharacterBase.h"
#include "GameFramework/PawnMovementComponent.h"

void UAIAnimationInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	UE_LOG(LogTemp, Warning, L"Working")

	AAICharacterBase* AIGuard = Cast<AAICharacterBase>(TryGetPawnOwner());
	if (AIGuard && AIGuard->IsValidLowLevel())
	{
		UPawnMovementComponent* MovementComp = AIGuard->GetMovementComponent();
		if (MovementComp)
		{
			bIsInAir = MovementComp->IsFalling();
			Speed = AIGuard->GetVelocity().Size();
		}
	}
}

void UAIAnimationInstance::NotifyChangeState_Implementation(ENPCState NPCState)
{
	AINPCState = NPCState;
}

void UAIAnimationInstance::ModifyAimingStance_Implementation(bool bIsAimingParam)
{
	bIsAiming = bIsAimingParam;
}