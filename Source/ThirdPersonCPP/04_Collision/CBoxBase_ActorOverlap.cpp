#include "CBoxBase_ActorOverlap.h"
#include "Global.h"

void ACBoxBase_ActorOverlap::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_ActorOverlap::BeginOverlap);
}

void ACBoxBase_ActorOverlap::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	CLog::Print("OtherActor :" + OtherActor->GetActorLabel());
}
