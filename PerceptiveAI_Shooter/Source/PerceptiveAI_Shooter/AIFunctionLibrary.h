// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AIFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API UAIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	static FTransform GetIdentityTransform();
	
};
