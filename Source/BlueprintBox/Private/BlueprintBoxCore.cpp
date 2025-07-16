
#pragma once
#include "BlueprintBoxCore.h"

UBlueprintBoxCore* UBlueprintBoxCore::CreateBPBoxObject() {
	return NewObject<UBlueprintBoxCore>();
}


void UBlueprintBoxCore::PrecomputeHannWindows(int32 SamplesToRead, UBlueprintBoxCore* Ref)
{
	Ref->HannWindow.SetNumUninitialized(SamplesToRead);

	const float halfSTR = SamplesToRead * 0.5 - 1;

	for (int32 SampleIndex = 0; SampleIndex < SamplesToRead; ++SampleIndex)
	{
		float Hann = 0.5f * (1.f - FMath::Cos(TWO_PI * (static_cast<float>(SampleIndex) / (halfSTR))));
		Ref->HannWindow[SampleIndex] = Hann;
	}
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

			if (Ref->DoneCalculatingFFT.IsBound())
			{
				bBroadcasted = true;
				Ref->DoneCalculatingFFT.Broadcast(output);
			}

			if (!bBroadcasted)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to send!"));
			}
		});

}

void UBlueprintBoxCore::RunThreadType(const FThreadTypeSwitch& DelegateReturn, bool GameThread)
{
	ENamedThreads::Type type = ENamedThreads::AnyThread;

	if (GameThread) {
		type = ENamedThreads::GameThread;
	}
	
	AsyncTask(type, [DelegateReturn]()
		{
			DelegateReturn.ExecuteIfBound();
		}
	);
}

