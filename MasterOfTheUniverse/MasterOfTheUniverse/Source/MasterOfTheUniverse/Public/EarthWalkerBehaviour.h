// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "EarthWalkerBehaviour.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MASTEROFTHEUNIVERSE_API UEarthWalkerBehaviour : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEarthWalkerBehaviour();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	//returns the position where the earth walker can be teleported/moved/jumped/whater to. if not possible positionFindingWorked will be false.
	//it depends on the camera orientation
	//ths function shoots a camera ray. the hitpoint will be taken and tranformed towards the center of the planet until it reaches an blocking object with tag "Floor".
	UFUNCTION(BlueprintCallable, Category = "Earth Walking")
	FVector getWalkingPosition(bool& positionFindingWorked, FVector PlanetCenterWorldPoisition, FVector CameraPosition, FVector CameraForward);
};
