#include "CChestBase.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Global.h"

ACChestBase::ACChestBase()
{
	Emissive = FLinearColor::Red;

	TopMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopMeshComp"));
	BottomMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomMeshComp"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> topMeshAsset(TEXT("/Game/Assiment/Chest/SM_ChestTop"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> bottomMeshAsset(TEXT("/Game/Assiment/Chest/SM_ChestBottom"));

	if (topMeshAsset.Succeeded() & bottomMeshAsset.Succeeded())
	{
		TopMeshComp->SetStaticMesh(topMeshAsset.Object);
		BottomMeshComp->SetStaticMesh(bottomMeshAsset.Object);

		BottomMeshComp->SetupAttachment(TopMeshComp);
	}


}

void ACChestBase::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInstanceConstant* materialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Assiment/Chest/MI_Chest")));
	if (materialAsset)
	{
		TopDynamicMaterial = UMaterialInstanceDynamic::Create(materialAsset, nullptr);
		TopDynamicMaterial->SetVectorParameterValue("Emissive", FLinearColor::Red);
		TopMeshComp->SetMaterial(0, TopDynamicMaterial);
	}
}