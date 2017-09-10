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
	CurrentActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMassOfActorsOnPlate() > 30.f) {
		OnOpen.Broadcast();
	}
	else { OnClose.Broadcast(); }
}
float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;

	if(PressurePlate)
	PressurePlate->GetOverlappingActors(OverlappingActors);
	for ( auto* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
		return TotalMass;
}

