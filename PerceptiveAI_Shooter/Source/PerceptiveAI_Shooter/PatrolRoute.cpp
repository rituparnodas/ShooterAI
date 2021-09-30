// Copyright DevDasTour 2021 All Right Reserved.


#include "PatrolRoute.h"
#include "Components/SplineComponent.h"

APatrolRoute::APatrolRoute()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(FName("SceneComp"));
	RootComponent = SceneComp;

	PatrolPath = CreateDefaultSubobject<USplineComponent>(FName("PatrolPath"));
	PatrolPath->SetupAttachment(RootComponent);
}

void APatrolRoute::BeginPlay()
{
	Super::BeginPlay();
	
}

void APatrolRoute::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APatrolRoute::IncrementPatrolPath()
{
	++PatrolIndex;
	PatrolIndex %= PatrolPath->GetNumberOfSplinePoints();
}

FVector APatrolRoute::GetNextPointAsWorldPosition()
{
	return PatrolPath->GetLocationAtSplinePoint(PatrolIndex, ESplineCoordinateSpace::World);
}