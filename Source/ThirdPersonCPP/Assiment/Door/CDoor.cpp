#include "CDoor.h"
#include "CPlayer.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACDoor::ACDoor()
{
    PrimaryActorTick.bCanEverTick = true;

    DoorColor = FLinearColor::Red;

    RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
    RootComponent = RootComp;

    DoorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMeshComp"));
    FraneMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FraneMeshComp"));

    FraneMeshComp->SetupAttachment(RootComp);
    DoorMeshComp->SetupAttachment(RootComp);

    ConstructorHelpers::FObjectFinder<UStaticMesh> doorMeshComp(TEXT("/Game/Assiment/Door/Props/SM_Door"));
    ConstructorHelpers::FObjectFinder<UStaticMesh> franeMeshComp(TEXT("/Game/Assiment/Door/Props/SM_DoorFrame"));

    if (doorMeshComp.Succeeded() && franeMeshComp.Succeeded())
    {
        FraneMeshComp->SetStaticMesh(franeMeshComp.Object);
        DoorMeshComp->SetStaticMesh(doorMeshComp.Object);
    }

    // Setup Box Collision
    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    RootComponent = BoxCollision;

    BoxCollision->SetBoxExtent(FVector(50.f, 50.f, 50.f));
    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACDoor::OnBoxBeginOverlap);

    RequiredKeyIndex = 0;
    bIsOpened = false;

    // Set up Text Renderer component
    TextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderer"));
    TextRenderer->SetHorizontalAlignment(EHTA_Center);
    TextRenderer->SetWorldSize(16.f);
    TextRenderer->SetupAttachment(RootComponent);
    TextRenderer->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
    TextRenderer->SetText(FText::FromString(TEXT("Player does not have the required key to open the door.")));

    TextRenderer->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));
    TextRenderer->SetVisibility(false);
}

void ACDoor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    UMaterialInstanceConstant* doorMaterialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Assiment/Door/Materials/MI_Door")));
    UMaterialInstanceConstant* glassMaterialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Assiment/Door/Materials/MI_Glass")));
    UMaterialInstanceConstant* franeMaterialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Assiment/Door/Materials/MI_Frame")));

    if (doorMaterialAsset && glassMaterialAsset)
    {
        DoorDynamicMaterial = UMaterialInstanceDynamic::Create(doorMaterialAsset, nullptr);
        DoorDynamicMaterial->SetVectorParameterValue("Color", DoorColor);

        DoorMeshComp->SetMaterial(0, DoorDynamicMaterial);
        DoorMeshComp->SetMaterial(1, glassMaterialAsset);
    }

    if (franeMaterialAsset)
    {
        FraneDynamicMaterial = UMaterialInstanceDynamic::Create(franeMaterialAsset, nullptr);
        FraneDynamicMaterial->SetVectorParameterValue("Color", DoorColor);

        FraneMeshComp->SetMaterial(0, FraneDynamicMaterial);
    }
}

void ACDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsOpened)
    {
        FRotator TargetRotation = FRotator(0.0f, -90.0f, 0.0f);
        FRotator NewRotation = FMath::RInterpTo(DoorMeshComp->GetRelativeRotation(), TargetRotation, DeltaTime, 3.0f);
        DoorMeshComp->SetRelativeRotation(NewRotation);
    }
}

void ACDoor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ACPlayer* OverlappingPlayer = Cast<ACPlayer>(OtherActor);
    if (OverlappingPlayer)
    {

        if (RequiredKeyIndex >= 0 && RequiredKeyIndex < OverlappingPlayer->AcquiredKeys.Num() &&
            OverlappingPlayer->AcquiredKeys[RequiredKeyIndex])
        {
            OpenDoor(OverlappingPlayer->AcquiredKeys);
        }
        else
        {
            FString Message;
            switch (RequiredKeyIndex)
            {
            case 0:
                Message = TEXT("You don't have a Red key");
                break;
            case 1:
                Message = TEXT("You don't have a Green key");
                break;
            case 2:
                Message = TEXT("You don't have a Blue key");
                break;
            default:
                Message = TEXT("Player does not have the required key to open the door.");
                break;
            }

            ShowMessage(Message); // Show the message to the player
        }
    }
}

void ACDoor::OpenDoor(const TArray<bool>& AcquiredKeys)
{
    if (!bIsOpened)
    {
        if (AcquiredKeys[RequiredKeyIndex])
        {
            bIsOpened = true;
        }
    }
}

void ACDoor::ShowMessage(FString Message)
{
    // Show the message in the TextRenderer
    TextRenderer->SetText(FText::FromString(Message));
    TextRenderer->SetVisibility(true);

    // Set a timer to hide the message after 1 second (Adjust time as needed)
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_MessageTimeout, this, &ACDoor::HideMessage, 2.0f, false);
}

void ACDoor::HideMessage()
{
    TextRenderer->SetVisibility(false);
    TimerHandle_MessageTimeout.Invalidate();
}