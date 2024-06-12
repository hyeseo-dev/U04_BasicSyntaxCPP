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
	UStaticMeshComponent* TopMeshComp;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* BottomMeshComp;

	UMaterialInstanceDynamic* TopDynamicMaterial;

	UPROPERTY(EditInstanceOnly, Category = "MaterialParams")
	FLinearColor Emissive;
};
