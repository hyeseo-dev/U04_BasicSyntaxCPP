#include "CMagazine.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/StaticMeshComponent.h"


ACMagazine::ACMagazine()
{

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
    //RootComponent = MeshComp;
    SetRootComponent(MeshComp);

    ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("/Game/Weapons/Meshes/AR4/SM_AR4_Mag_Empty"));

    if (meshAsset.Succeeded())
    {
        MeshComp->SetStaticMesh(meshAsset.Object);
    }

    MeshComp->SetSimulatePhysics(false);
}

