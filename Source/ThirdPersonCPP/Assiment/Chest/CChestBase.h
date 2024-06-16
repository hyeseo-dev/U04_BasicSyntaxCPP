#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CChestBase.generated.h"

UCLASS()
class THIRDPERSONCPP_API ACChestBase : public AActor
{
	GENERATED_BODY()
	
public:
	ACChestBase();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* TopMeshComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* BottomMeshComp;

	UMaterialInstanceDynamic* TopDynamicMaterial;

	UPROPERTY(EditAnywhere, Category = "MaterialParams")
	FLinearColor Emissive;
};
