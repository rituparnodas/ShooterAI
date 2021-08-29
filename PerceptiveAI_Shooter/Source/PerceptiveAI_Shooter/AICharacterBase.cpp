// Copyright DevDasTour 2021 All Right Reserved.

#include "AICharacterBase.h"
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "WeaponBase.h"
#include "AIFunctionLibrary.h"
#include "AIAnimationInstance.h"

AAICharacterBase::AAICharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));
}

void AAICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	HealthComp->OnDeath.AddDynamic(this, &AAICharacterBase::HandleDeath);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, UAIFunctionLibrary::GetIdentityTransform(), SpawnParams);
	if (Weapon)
	{
		Weapon->SetOwner(this);
		Weapon->SetInstigator(this);

		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("WeaponSocket"));
	}
}

void AAICharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAICharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacterBase::HandleDeath()
{
	if (DoOnce_COND)
	{
		DoOnce_COND = false;
		UE_LOG(LogTemp, Warning, TEXT("HandleDeath Occur"));
		GetMesh()->SetCollisionProfileName("Ragdoll");
		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->WakeAllRigidBodies();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}	
}

bool AAICharacterBase::GetIsDead_Implementation()
{
	return HealthComp->IsDead();
}

void AAICharacterBase::NotifyChangeState_Implementation(ENPCState NPCState)
{
	UAIAnimationInstance* ABP = Cast<UAIAnimationInstance>(GetMesh()->GetAnimInstance());
	if (ABP)
	{
		Execute_NotifyChangeState(ABP, NPCState);
	}
}

bool AAICharacterBase::GetTeamID_Implementation()
{
	return false;
}
