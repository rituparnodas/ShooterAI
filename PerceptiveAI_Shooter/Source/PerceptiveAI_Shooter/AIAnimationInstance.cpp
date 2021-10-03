// Copyright DevDasTour 2021 All Right Reserved.


#include "AIAnimationInstance.h"
#include "AICharacterBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UAIAnimationInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//UE_LOG(LogTemp, Warning, L"Working")

	AAICharacterBase* AIGuard = Cast<AAICharacterBase>(TryGetPawnOwner());
	if (AIGuard && AIGuard->IsValidLowLevel())
	{
		UPawnMovementComponent* MovementComp = AIGuard->GetMovementComponent();
		if (MovementComp)
		{
			bIsInAir = MovementComp->IsFalling();
			Speed = AIGuard->GetVelocity().Size();

			FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(AIGuard->GetControlRotation(), AIGuard->GetActorRotation());
			FRotator RInterpValue = UKismetMathLibrary::RInterpTo(FRotator(AimPitch, AimYaw, 0.f), DeltaRotator, GetWorld()->DeltaTimeSeconds, 15.f);
			AimPitch = FMath::Clamp(AimPitch, -90.f, 90.f);
			AimYaw = FMath::Clamp(AimYaw, -90.f, 90.f);
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