#pragma once

#include "CoreMinimal.h"
#include "Assiment/Chest/CChestBase.h"
#include "CChestBase_Box.generated.h"

class UTextRenderComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChestOpened);

UCLASS()
class THIRDPERSONCPP_API ACChestBase_Box : public ACChestBase
{
	GENERATED_BODY()

public:
	ACChestBase_Box();

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Chest")
	void OpenChest();

	bool IsOpen() const { return bIsOpen; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest")
	int32 KeyIndex;

protected:
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "Chest")
	FOnChestOpened OnChestOpened;

	UPROPERTY(VisibleDefaultsOnly)
	UTextRenderComponent* BoxTextRenderer;

private:
	bool bIsOpen;
};
