// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InterfaceAIHelper.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AICGuard.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API AAICGuard : public AAIController, public IInterfaceAIHelper
{
	GENERATED_BODY()

protected:

	AAICGuard();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		float AcceptanceRadius = 200;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		class UBehaviorTree* AIBehavior = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		class UBlackboardData* BlackBoardData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAIPerceptionComponent* AIPerceptioncomp = nullptr;

public:

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "State")
	ENPCState GetNPCState();

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetStateAsPassive();

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetStateAsInvestigating(FVector MoveToLocation, FVector PointOfLocation);

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetStateAsAttack(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetStateAsSeeking(FVector Search);

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetStateAsDead();

	UFUNCTION(BlueprintCallable, Category = "State")		
		void SetStateAs(TEnumAsByte<ENPCState> NPCState, FVector Seeking_Search = FVector::ZeroVector,
			FVector Investigating_MoveToLocation = FVector::ZeroVector, FVector Investigating_PointOfLocation = FVector::ZeroVector, AActor* Attack_Target = nullptr);

	//virtual void NotifyChangeState_Implementation(ENPCState NPCState) override;

	UFUNCTION()
		void OnUpdatedPerception(const TArray<AActor*>& UpdatedActors);

	void ProcessLastVisionStimuli();
	void ProcessLastHearingStimuli();

	UPROPERTY(BlueprintReadWrite, Category = "AI")
		class AActor* SensedActor = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "AI")
		FAIStimulus ActorSensedStimulus;
};
