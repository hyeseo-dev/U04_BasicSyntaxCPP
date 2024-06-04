#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMeshBase.generated.h"

UCLASS()
class THIRDPERSONCPP_API ACStaticMeshBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACStaticMeshBase();

private:
	UFUNCTION()
	void UpdateParameters();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere) // or VisibleDefault
	UStaticMeshComponent* MeshComp;

	UMaterialInstanceDynamic* DynamicMaterial;
};
