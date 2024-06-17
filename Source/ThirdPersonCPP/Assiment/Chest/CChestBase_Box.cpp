#include "CChestBase_Box.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"

ACChestBase_Box::ACChestBase_Box()
{
    PrimaryActorTick.bCanEverTick = true;

    bIsOpen = false;

    // Set up Text Renderer component
    BoxTextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("BoxTextRenderer"));
    BoxTextRenderer->SetHorizontalAlignment(EHTA_Center);
    BoxTextRenderer->SetWorldSize(16.f);
    BoxTextRenderer->SetupAttachment(TopMeshComp);
    BoxTextRenderer->SetRelativeLocation(FVector(100.0f, 0.0f, 50.0f));
    BoxTextRenderer->SetText(FText::FromString(TEXT("Press F key to open")));
    BoxTextRenderer->SetTextRenderColor(FColor::White);
    BoxTextRenderer->SetVisibility(true);
    BoxTextRenderer->SetRelativeRotation(FRotator(0.f, -360.f, 0.f));
}

void ACChestBase_Box::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsOpen)
    {
        FRotator TargetRotation = FRotator(90.0f, 0.0f, 0.0f);
        FRotator NewRotation = FMath::RInterpTo(TopMeshComp->GetRelativeRotation(), TargetRotation, DeltaTime, 3.0f);
        TopMeshComp->SetRelativeRotation(NewRotation);
    }
}

void ACChestBase_Box::OpenChest_Implementation()
{
    if (!bIsOpen)
    {
        bIsOpen = true;
        BoxTextRenderer->SetVisibility(false);
    }
}