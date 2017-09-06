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
	curr_actor = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{

	//sets the door rotation
	Owner->SetActorRotation(FRotator(0.0f, open_angle, 0.0f));
}

void UOpenDoor::CloseDoor()
{

	//sets the door rotation
	Owner->SetActorRotation(FRotator(0.0f, close_angle, 0.0f));
}
// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Poll the trigger volume
	if (pressure_plate->IsOverlappingActor(curr_actor)) {
		//If the actorThatOpens is in the volume than-
		OpenDoor();
		last_door_open_time = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - last_door_open_time > door_close_delay) {
		CloseDoor();
	}
	/*
	//no trigger- close the door
	else {
		CloseDoor();
	}
	*/
}

