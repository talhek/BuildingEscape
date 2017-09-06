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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(VisibleAnywhere)
	float open_angle = 90.0f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressure_plate;

	
	
	AActor* curr_actor; //Remember pawn inherits from actor 
};
