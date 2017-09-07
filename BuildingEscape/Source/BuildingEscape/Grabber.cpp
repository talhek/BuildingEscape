// Copyright Tal Hekman 17

#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{

	Super::BeginPlay();
	///Look for physics handler
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandler) {
		UE_LOG(LogTemp, Error, TEXT("%s missing physics component"), *GetOwner()->GetName());
	}
	else {
		//PhysicsHandler is found
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{


	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//get player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotator);
	//UE_LOG(LogTemp, Warning, TEXT("Player view point location is : %s and position: %s "), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotator.ToString());

	///draw a red trace in the world to visualize
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotator.Vector() * Reach;
		DrawDebugLine(GetWorld(),
			PlayerViewPointLocation,
			LineTraceEnd,
			FColor(255, 0, 0),
			false,
			0.f,
			0.f,
			10.f
			);
		//setup query params
		FCollisionQueryParams TraceParematers(FName(TEXT("")), false, GetOwner());

		//Ray-cast out to reach distance
		FHitResult Hit;
		GetWorld()->LineTraceSingleByObjectType
		(
			Hit,
			PlayerViewPointLocation,
			LineTraceEnd,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			TraceParematers
		);
	//see what we hit
		if(Hit.GetActor())
			ObjectHit = Hit.GetActor()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("Collision occured with object: %s "), *ObjectHit);

}

