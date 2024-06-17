#include "CChestBase.h"
#include "Global.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACChestBase::ACChestBase()
{
	Emissive = FLinearColor::Red;

	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	TopMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopMeshComp"));
	BottomMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomMeshComp"));

	TopMeshComp->SetupAttachment(RootComp);
	BottomMeshComp->SetupAttachment(RootComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> topMeshAsset(TEXT("/Game/Assiment/Chest/SM_ChestTop"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> bottomMeshAsset(TEXT("/Game/Assiment/Chest/SM_ChestBottom"));

	if (topMeshAsset.Succeeded() & bottomMeshAsset.Succeeded())
	{
		TopMeshComp->SetStaticMesh(topMeshAsset.Object);
		BottomMeshComp->SetStaticMesh(bottomMeshAsset.Object);
	}
}

void ACChestBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UMaterialInstanceConstant* materialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Assiment/Chest/MI_Chest")));
	if (materialAsset)
	{
		TopDynamicMaterial = UMaterialInstanceDynamic::Create(materialAsset, nullptr);
		TopDynamicMaterial->SetVectorParameterValue("Emissive", Emissive);
		TopMeshComp->SetMaterial(0, TopDynamicMaterial);
	}
}
