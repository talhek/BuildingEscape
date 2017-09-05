// Copyright Tal Hekman 17

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}

void UOpenDoor::OpenDoor()
{
	//get owing actor
	AActor* Owner = GetOwner();
	//creates a rotator
	FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);
	//sets the door rotation
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Poll the trigger volume
	if (pressure_plate->IsOverlappingActor(ActorThatOpens))
	//If the actorThatOpens is in the volume than-
	OpenDoor();
}

