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
		UE_LOG(LogTemp, Warning, TEXT("input component found "));
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
		UE_LOG(LogTemp, Warning, TEXT("physics handle found"), *GetOwner()->GetName());

	}
}
void UGrabber::GrabObject() {

	UE_LOG(LogTemp, Warning, TEXT("Object %s tried to grab!"), *GetOwner()->GetName());

	//Line trace and see if we can reach any actor with physics body collision channel set
	GetFirstPhysicsBodyInReach();

	auto  HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	if (HitResult.GetActor()) {
		//attach physics handle
		PhysicsHandler->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			HitResult.GetActor()->GetTargetLocation(),
			PlayerViewPointRotator
		);
	}
}
void UGrabber::ReleaseObject() {
	UE_LOG(LogTemp, Warning, TEXT("Object %s tried release!"), *GetOwner()->GetName());

	// release physics handle
	if (PhysicsHandler->GrabbedComponent)
	{
		PhysicsHandler->ReleaseComponent();
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{


	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//get player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotator);
	//UE_LOG(LogTemp, Warning, TEXT("Player view point location is : %s and position: %s "), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotator.ToString());

	///calc the end of view point
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotator.Vector() * Reach;

	//if the physics handler is attached
		// move the object that is being held
	if (PhysicsHandler->GrabbedComponent) {
		PhysicsHandler->SetTargetLocation(LineTraceEnd);
	}


}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//get player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotator);
	//UE_LOG(LogTemp, Warning, TEXT("Player view point location is : %s and position: %s "), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotator.ToString());

	///calc the end of view point
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
	if (Hit.GetActor()) {
		ObjectHit = Hit.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Collision occured with object: %s "), *ObjectHit);
	}
	return Hit;
}

