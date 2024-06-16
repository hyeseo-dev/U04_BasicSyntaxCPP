#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CKey.generated.h"

UCLASS()
class THIRDPERSONCPP_API ACKey : public AActor
{
	GENERATED_BODY()
	
public:	
	ACKey();

protected:
	virtual void BeginPlay() override;

public:
	// 0: Red, 1: Green, 2: Blue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	int32 KeyIndex;
};
