// Fill out your copyright notice in the Description page of Project Settings.


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