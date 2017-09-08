// Copyright Tal Hekman 17

#pragma once
#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//finds (assumed) initial needed components
	void FindInputComponent();
	void FindPhysicsHandler();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	FHitResult Hit;
	FVector LineTraceEnd;
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;
	float Reach = 100.f;
	FString ObjectHit;

	UPhysicsHandleComponent* PhysicsHandler = nullptr;
	UInputComponent* InputComponent = nullptr;
	void GrabObject();
	void ReleaseObject();
	const FHitResult GetFirstPhysicsBodyInReach();

	void LocationUpdate();

};
