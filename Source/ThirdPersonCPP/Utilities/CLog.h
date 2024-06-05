#pragma once

#include "CoreMinimal.h"

class THIRDPERSONCPP_API CLog
{
public:
	static void Print(int32 InValue, int32 Inkey = -1, float InDuration = 10.f, FColor InColor = FColor::Black);
	static void Print(float InValue, int32 Inkey = -1, float InDuration = 10.f, FColor InColor = FColor::Black);
	static void Print(const FString& InValue, int32 Inkey = -1, float InDuration = 10.f, FColor InColor = FColor::Black);
	static void Print(const FVector& InValue, int32 Inkey = -1, float InDuration = 10.f, FColor InColor = FColor::Black);
	static void Print(const FRotator& InValue, int32 Inkey = -1, float InDuration = 10.f, FColor InColor = FColor::Black);

};
