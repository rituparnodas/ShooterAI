// Copyright DevDasTour 2021 All Right Reserved.


#include "AIAnimationInstance.h"

void UAIAnimationInstance::NotifyChangeState_Implementation(ENPCState NPCState)
{
	AINPCState = NPCState;
}