#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMagazine.generated.h"

UCLASS()
class THIRDPERSONCPP_API ACMagazine : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMagazine();

private:
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* MeshComp;

};
