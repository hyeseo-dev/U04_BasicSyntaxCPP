#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ACChestBase_Box;

UCLASS()
class THIRDPERSONCPP_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 0: Red, 1: Green, 2: Blue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keys")
	TArray<bool> AcquiredKeys;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void OnBoxOpen();
	void AcquireKey(int32 KeyIndex);

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, Category = "Chest")
	TSubclassOf<ACChestBase_Box> ChestBoxClasses;
	
private:
	ACChestBase_Box* ChestBox;
};
