#include "CPlayer.h"
#include "CAnimInstance.h"
#include "Global.h"
#include "Assiment/Chest/CChestBase_Box.h"
#include "Assiment/Door/CDoor.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Image.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"

ACPlayer::ACPlayer()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 60));
	SpringArmComp->bDoCollisionTest = false;
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UCAnimInstance> AnimInstanceClass(TEXT("/Game/ABP_CPlayer"));
	if (AnimInstanceClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClass.Class);
	}

	AcquiredKeys.Init(false, 3);

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

    if (WidgetClass)
    {
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            CurrentWidget = CreateWidget<UUserWidget>(PlayerController, WidgetClass);
            if (CurrentWidget)
            {
                CurrentWidget->AddToViewport();
            }
        }
    }
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::OffSprint);
	PlayerInputComponent->BindAction("Open", EInputEvent::IE_Released, this, &ACPlayer::OnBoxOpen);
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(ControlRotation).GetForwardVector();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(ControlRotation).GetRightVector();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ACPlayer::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACPlayer::OnBoxOpen()
{
    FVector Start = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();
    FVector End = ((ForwardVector * 200.f) + Start);
    FHitResult HitResult;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

    if (bIsHit)
    {
        if (ACChestBase_Box* HitChest = Cast<ACChestBase_Box>(HitResult.Actor))
        {
            HitChest->OpenChest();
            AcquireKey(HitChest->KeyIndex);  // ≈∞ ¿Œµ¶Ω∫∏¶ ≈Î«ÿ ≈∞ »πµÊ
        }
        else if (ACDoor* HitDoor = Cast<ACDoor>(HitResult.Actor))
        {
            HitDoor->OpenDoor(AcquiredKeys);
        }
    }

    float SearchRadius = 200.0f;
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACChestBase_Box::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        if (Actor)
        {
            float Distance = FVector::Dist(Start, Actor->GetActorLocation());
            if (Distance <= SearchRadius)
            {
                ACChestBase_Box* Chest = Cast<ACChestBase_Box>(Actor);
                if (Chest && !Chest->IsOpen())
                {
                    Chest->OpenChest();
                    AcquireKey(Chest->KeyIndex);  // ≈∞ ¿Œµ¶Ω∫∏¶ ≈Î«ÿ ≈∞ »πµÊ
                    break;
                }
            }
        }
    }
}

void ACPlayer::AcquireKey(int32 KeyIndex)
{
    if (KeyIndex >= 0 && KeyIndex < AcquiredKeys.Num())
    {
        AcquiredKeys[KeyIndex] = true;

        if (CurrentWidget)
        {
            UImage* ImageWidgetRed = Cast<UImage>(CurrentWidget->GetWidgetFromName(TEXT("ImageWidgetRed")));
            UImage* ImageWidgetGreen = Cast<UImage>(CurrentWidget->GetWidgetFromName(TEXT("ImageWidgetGreen")));
            UImage* ImageWidgetBlue = Cast<UImage>(CurrentWidget->GetWidgetFromName(TEXT("ImageWidgetBlue")));

            if (ImageWidgetRed && ImageWidgetGreen && ImageWidgetBlue)
            {
                switch (KeyIndex)
                {
                case 0:
                    ImageWidgetRed->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
                    break;
                case 1:
                    ImageWidgetGreen->SetColorAndOpacity(FLinearColor::Green);
                    break;
                case 2:
                    ImageWidgetBlue->SetColorAndOpacity(FLinearColor::Blue);
                    break;
                default:
                    break;
                }
            }
        }
    }
}