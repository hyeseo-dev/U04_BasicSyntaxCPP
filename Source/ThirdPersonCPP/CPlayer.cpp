#include "CPlayer.h"

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAxis("MoveForward", this, //�Լ��� �ּ� );
}

