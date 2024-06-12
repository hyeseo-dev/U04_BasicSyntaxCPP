#pragma once

#include "CoreMinimal.h"
#include "Assiment/Chest/CChestBase.h"
#include "CChestBase_Box.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChestOpened);

UCLASS()
class THIRDPERSONCPP_API ACChestBase_Box : public ACChestBase
{
	GENERATED_BODY()

public:
	ACChestBase_Box();

public:
	UFUNCTION(BlueprintCallable, Category = "Chest")
	void OpenChest();

	bool IsOpen() const { return bIsOpen; }

protected:
	UPROPERTY(BlueprintAssignable, Category = "Chest")
	FOnChestOpened OnChestOpened;

private:
	bool bIsOpen;
};
