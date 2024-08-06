
#pragma once
#include "BlueprintBoxCore.h"

UBlueprintBoxCore* UBlueprintBoxCore::CreateBPBoxObject() {
	return NewObject<UBlueprintBoxCore>();
}

void UBlueprintBoxCore::DoneCalculatingFFT_Internal(FSpectrogramOutput output, UBlueprintBoxCore* Ref)
{

	AsyncTask(ENamedThreads::GameThread, [Ref, output]()
		{

			if (!Ref->IsValidLowLevel())
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pointer is invalid"));
				return;
			}

			bool bBroadcasted{ false };

			if (Ref->DoneCalculating.IsBound())
			{
				bBroadcasted = true;
				Ref->DoneCalculating.Broadcast(output);
			}

			if (!bBroadcasted)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to send!"));
			}
		});

}