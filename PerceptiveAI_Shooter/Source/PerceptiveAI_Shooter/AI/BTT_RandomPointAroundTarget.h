// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_RandomPointAroundTarget.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API UBTT_RandomPointAroundTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTT_RandomPointAroundTarget();

	class AAIController* AIController = nullptr;
	class APawn* AIPawn = nullptr;

	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector MoveToKey;

	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector POIKey;

	UPROPERTY(EditAnywhere)
		float Radius = 50.f;

	UPROPERTY(EditAnywhere)
		FVector BoxExtent = FVector(1.f, 1.f, 1.f);

	UPROPERTY(EditAnywhere)
		bool bIsAMoveLocation;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
