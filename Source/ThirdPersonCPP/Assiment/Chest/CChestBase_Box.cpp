#include "CChestBase_Box.h"
#include "Global.h"

ACChestBase_Box::ACChestBase_Box()
{
    bIsOpen = false;
}

void ACChestBase_Box::OpenChest()
{
    if (!bIsOpen)
    {
        bIsOpen = true;

        FRotator NewRotation = FRotator(90.0f, 0.0f, 0.0f);
        TopMeshComp->AddLocalRotation(NewRotation);

        OnChestOpened.Broadcast();
    }
}