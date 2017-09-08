// Copyright Tal Hekman 17

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"

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
	if (GetTotalMassOfActorsOnPlate() > 30.0f) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}
	 
}
float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;
	if(PressurePlate)
	PressurePlate->GetOverlappingActors(OverlappingActors);
	for (const auto* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName())

	}
	UE_LOG(LogTemp, Warning, TEXT("Total mass is: %f "), TotalMass)

		return TotalMass;
}

