#pragma once

#include "CoreMinimal.h"
#include "Assiment/Chest/CChestBase.h"
#include "CChestBase_Box.generated.h"

class UTextRenderComponent;

UCLASS()
class THIRDPERSONCPP_API ACChestBase_Box : public ACChestBase
{
	GENERATED_BODY()

public:
	ACChestBase_Box();

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Chest")
	void OpenChest();

	bool IsOpen() const { return bIsOpen; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest")
	int32 KeyIndex;

protected:
	UPROPERTY(VisibleDefaultsOnly)
	UTextRenderComponent* BoxTextRenderer;

private:
	bool bIsOpen;

	FRotator InitialRotation;
};
