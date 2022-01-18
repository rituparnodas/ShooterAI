// Copyright DevDasTour 2021 All Right Reserved.

#include "WeaponBase.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshcomponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"
#include "DrawDebugHelpers.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(FName("DefaultRoot"));
	RootComponent = SceneRoot;

	WeaponVisual = CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponVisual"));
	WeaponVisual->SetupAttachment(SceneRoot);
	MuzzleLocation = CreateDefaultSubobject<UArrowComponent>(FName("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(WeaponVisual);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	OnFireRequested.AddDynamic(this, &AWeaponBase::FireRequested);
	
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AWeaponBase::ResetDOOnce()
{
	DoOnce_COND = true;
	OnWeaponFired.Broadcast();
}

void AWeaponBase::FireRequested()
{
	if (DoOnce_COND)
	{
		DoOnce_COND = false;
		FireRound();
		FTimerHandle Handle_FireCooldown;
		GetWorld()->GetTimerManager().SetTimer(Handle_FireCooldown, this, &AWeaponBase::ResetDOOnce, CycleRate);
	}
}


void AWeaponBase::FireRound()
{
	FTransform MuzzlePoint{ MuzzleLocation->GetComponentTransform() };
	if (BulletClass != nullptr)
	{
		AActor* Bullet{ GetWorld()->SpawnActor<AActor>(BulletClass, MuzzlePoint) };
	}
	
	if (FireSoundClass != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSoundClass, MuzzlePoint.GetLocation());
	}
	
	FHitResult HitResult;
	FVector TraceStart = MuzzlePoint.GetLocation();
	FVector TraceEnd = TraceStart + MuzzlePoint.GetRotation().Vector() * WeaponRange;
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		TraceStart,
		TraceEnd,
		ECC_Visibility
	);

	if (bHit)
	{
		UGameplayStatics::ApplyPointDamage(
			HitResult.GetActor(),
			WeaponDamage,
			MuzzlePoint.GetLocation().ForwardVector,
			HitResult,
			GetOwner()->GetInstigatorController(),
			GetOwner(),
			DamageType);

		UAISense_Damage::ReportDamageEvent(
			GetWorld(), 
			HitResult.GetActor(), 
			GetOwner()->GetInstigatorController(), 
			WeaponDamage, 
			HitResult.Location, 
			HitResult.Location);
	}

	DrawDebugLine(GetWorld(), TraceStart, HitResult.Location, FColor::Red, true, 1, 5, 5);

	UE_LOG(LogTemp, Warning, TEXT("Shooting"));
}