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
	FindInputComponent();
	FindPhysicsHandler();



}
void UGrabber::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Error, TEXT("input component found "));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
	}
	InputComponent->BindAction("GrabObject", IE_Pressed, this, &UGrabber::GrabObject);
	InputComponent->BindAction("GrabObject", IE_Released, this, &UGrabber::ReleaseObject);
}
void UGrabber::FindPhysicsHandler()
{
	///Look for physics handler
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandler) {
		UE_LOG(LogTemp, Error, TEXT("%s missing physics component"), *GetOwner()->GetName());
	}
	else {
		//PhysicsHandler is found
	}
}
void UGrabber::GrabObject() {

	UE_LOG(LogTemp, Warning, TEXT("Object %s grabbed!"), *GetOwner()->GetName());

	//Line trace and see if we can reach any actor with physics body collision channel set

	//if success on hit than attach a physics handle

	//TODO attach physics handle
}
void UGrabber::ReleaseObject() {
	UE_LOG(LogTemp, Warning, TEXT("Object %s released!"), *GetOwner()->GetName());

	//TODO release physics handle
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{


	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if the physics handler is attached
		// move the object that is being held





	//get player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotator);
	//UE_LOG(LogTemp, Warning, TEXT("Player view point location is : %s and position: %s "), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotator.ToString());

	///draw a red trace in the world to visualize
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotator.Vector() * Reach;
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

