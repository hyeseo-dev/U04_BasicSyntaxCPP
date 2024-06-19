#include "CMagazine.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/StaticMeshComponent.h"


ACMagazine::ACMagazine()
{

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
    SetRootComponent(MeshComp);

    ConstructorHelpers::FObjectFinder<UStaticMesh> MagMeshAsset(TEXT("/Game/Weapons/Meshes/AR4/SM_AR4_Mag"));
    if (MagMeshAsset.Succeeded())
    {
        MeshComp->SetStaticMesh(MagMeshAsset.Object);
    }

    MeshComp->SetSimulatePhysics(true);
}

