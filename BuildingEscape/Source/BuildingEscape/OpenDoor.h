// Copyright Tal Hekman 17

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
		float open_angle = 90.0f;
		float close_angle = 0.0f;
	

		UPROPERTY(EditAnywhere)
			ATriggerVolume* PressurePlate;
		UPROPERTY(EditAnywhere)
			float DoorCloseDelay = 1.0f;
		UPROPERTY(EditAnywhere)
			float LastDoorOpenTime = 0;
	AActor* curr_actor; //Remember pawn inherits from actor 
	AActor* Owner;
	float GetTotalMassOfActorsOnPlate();
};
