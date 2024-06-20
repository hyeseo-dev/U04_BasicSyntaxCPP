#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

class USkeletalMeshComponent;
class UACharacter;
class UAnimMontage;
class ACBullet;
class UParticleSystem;
class USoundCue;
class UMaterialInstanceConstant;
class ACMagazine;

UCLASS()
class THIRDPERSONCPP_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsEquipping() { return bEquipping; }
	FORCEINLINE bool IsAiming() { return bAiming; }
	FORCEINLINE USkeletalMeshComponent* GetMesh() { return MeshComp; }

	FORCEINLINE bool IsFiring() { return bFiring; }
	FORCEINLINE bool IsAutoFire() { return bAutoFire; }

	void ToggleAutoFire();

	void Begin_Aiming();
	void End_Aiming();

	void Begin_Fire();
	void End_Fire();

	UFUNCTION()
	void Firing();

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

	void Reload();
	void Begin_Reload();
	void End_Reload();

	void HideMagazine();
	void UnHideMagazine();

	void Begin_SwapMagazine();
	void End_SwapMagazine();

public:
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentBullet;

private:
	UPROPERTY(EditDefaultsOnly, Category = "BulletClass")
	TSubclassOf<ACBullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "AutoFire")
	float FireInterval;

	UPROPERTY(EditDefaultsOnly, Category = "AutoFire")
	float PitchSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HolsterSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HandSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName MagSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* UnequipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "CameraShake")
	TSubclassOf<UCameraShake> CameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* MuzzleParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* EjectParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundCue* SwapMagazineSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UMaterialInstanceConstant* DecalMaterial;

private:
	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "MagazineClass")
	TSubclassOf<ACMagazine> MagazineClass;

private:
	ACharacter* OwnerCharacter;
	ACMagazine* Magazine;

	FTimerHandle AutoTimerHandle;

	FName MagBoneName;

	bool bEquipped;
	bool bEquipping;
	bool bAiming;
	bool bFiring;
	bool bAutoFire;
	bool bReloading;
	bool bSwapMagazine;

	float CurrentPitch;
	
};
