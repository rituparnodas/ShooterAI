// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICGuard.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API AAICGuard : public AAIController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		float AcceptanceRadius = 200;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		class UBehaviorTree* AIBehavior = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		class UBlackboardData* BlackBoardData;

public:

	virtual void Tick(float DeltaTime) override;

};
