#include "CAnimInstance.h"
#include "Global.h"
#include "CWeaponInterface.h"
#include "CWeapon.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OnwerPawn)
	{
		Speed = OnwerPawn->GetVelocity().Size2D();
		Direction = CalculateDirection(OnwerPawn->GetVelocity(), OnwerPawn->GetControlRotation());
		Pitch = OnwerPawn->GetBaseAimRotation().Pitch;

		ICWeaponInterface* ImplemetedPawn = Cast<ICWeaponInterface>(OnwerPawn);
		if (ImplemetedPawn)
		{
			ACWeapon* Weapon = ImplemetedPawn->GetWeapon();
			if (Weapon)
			{
				bEquipped = Weapon->IsEquipped();
				bAimng = Weapon->IsAiming();
			}
		}
	}
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnwerPawn = TryGetPawnOwner();
}
