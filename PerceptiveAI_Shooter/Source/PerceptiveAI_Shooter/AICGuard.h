// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InterfaceAIHelper.h"
#include "AIController.h"
#include "AICGuard.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API AAICGuard : public AAIController, public IInterfaceAIHelper
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName AIStateName = FName("State");

	UFUNCTION(BlueprintPure)
	ENPCState GetNPCState();

	UFUNCTION(BlueprintCallable)
	void SetStateAsPassive();

	//virtual void NotifyChangeState_Implementation(ENPCState NPCState) override;

};
