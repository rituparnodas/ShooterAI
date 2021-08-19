// Copyright DevDasTour 2021 All Right Reserved.


#include "AICGuard.h"

void AAICGuard::BeginPlay()
{
	Super::BeginPlay();

	UBlackboardComponent* BlackBoardComponent = nullptr;
	UseBlackboard(BlackBoardData, BlackBoardComponent);

	RunBehaviorTree(AIBehavior);
}

void AAICGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}