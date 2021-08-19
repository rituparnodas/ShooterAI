// Copyright DevDasTour 2021 All Right Reserved.

#include "AIFunctionLibrary.h"

FTransform UAIFunctionLibrary::GetIdentityTransform()
{
	FTransform TransformBuff;
	TransformBuff.SetLocation(FVector(0.f, 0.f, 0.f));
	TransformBuff.SetRotation(FQuat(FRotator(0.f, 0.f, 0.f)));
	TransformBuff.SetScale3D(FVector(1.f, 1.f, 1.f));

	return TransformBuff;
}