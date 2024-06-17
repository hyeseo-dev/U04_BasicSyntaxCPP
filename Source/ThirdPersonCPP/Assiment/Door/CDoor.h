#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDoor.generated.h"

class UBoxComponent;
class UTextRenderComponent;

UCLASS()
class THIRDPERSONCPP_API ACDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDoor();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
	void OpenDoor(const TArray<bool>& AcquiredKeys);

private:
	void ShowMessage(FString Message);
	void HideMessage();

public:
	// 0: Red, 1: Green, 2: Blue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	int32 RequiredKeyIndex;

protected:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* DoorMeshComp;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* FraneMeshComp;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* BoxCollision;

	UMaterialInstanceDynamic* DoorDynamicMaterial;
	UMaterialInstanceDynamic* FraneDynamicMaterial;

	UPROPERTY(EditInstanceOnly, Category = "MaterialParams")
	FLinearColor DoorColor;

protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Door")
    bool bIsOpened;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Door")
	UTextRenderComponent* TextRenderer;

private:
	FTimerHandle TimerHandle_MessageTimeout;
};
