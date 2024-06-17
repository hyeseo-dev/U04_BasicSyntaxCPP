#include "CChestBase_Box.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"

ACChestBase_Box::ACChestBase_Box()
{
    bIsOpen = false;

    // Set up Text Renderer component
    BoxTextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("BoxTextRenderer"));
    BoxTextRenderer->SetHorizontalAlignment(EHTA_Center);
    BoxTextRenderer->SetWorldSize(16.f);
    BoxTextRenderer->SetupAttachment(TopMeshComp);
    BoxTextRenderer->SetRelativeLocation(FVector(100.0f, 0.0f, 50.0f));
    BoxTextRenderer->SetText(FText::FromString(TEXT("Press F key to open")));
    BoxTextRenderer->SetTextRenderColor(FColor::White);

    BoxTextRenderer->SetRelativeRotation(FRotator(0.f, -360.f, 0.f));
    BoxTextRenderer->SetVisibility(true);
}

void ACChestBase_Box::OpenChest_Implementation()
{
    if (!bIsOpen)
    {
        bIsOpen = true;
        TopMeshComp->AddLocalRotation(FRotator(90.0f, 0.0f, 0.0f));
        BoxTextRenderer->SetVisibility(false);
    }
}