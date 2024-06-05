#include "CLogActor.h"
#include "Global.h"

ACLogActor::ACLogActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACLogActor::BeginPlay()
{
	Super::BeginPlay();

	CLog::Print(1);
	CLog::Print(2, 1);
	CLog::Print(3, 2, 20.f);
	CLog::Print(4, 2, 20.f, FColor::Orange);
	CLog::Print("Hello C++ World");
	CLog::Print(GetActorLocation());
	CLog::Print(GetActorRotation());

}

void ACLogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

