// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterOfTheUniverse.h"
#include "EarthWalkerBehaviour.h"


// Sets default values for this component's properties
UEarthWalkerBehaviour::UEarthWalkerBehaviour()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEarthWalkerBehaviour::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEarthWalkerBehaviour::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

FVector UEarthWalkerBehaviour::getWalkingPosition(bool& positionFindingWorked, FVector PlanetCenterWorldPoisition, FVector CameraPosition, FVector CameraForward, float maximalWalkingDistance)
{
	positionFindingWorked = false;
	FCollisionQueryParams traceParams(FName(TEXT("Walker Trace")), true, this->GetOwner());
	traceParams.bTraceComplex = true;
	//TraceParams.bTraceAsyncScene = true;
	//Re-initialize hit info
	FHitResult firstRayCastResult(ForceInit);

	bool rayCastWorked = this->GetWorld()->LineTraceSingle(firstRayCastResult, CameraPosition, CameraPosition + CameraForward * maximalWalkingDistance, ECC_Camera, traceParams);
	
	//if that did not succed we need to trace another ray towards the centre of the planet to find the floor.
	FVector secondaryRayStartPoint = FVector(0, 0, 0);

	if (rayCastWorked)
	{
		if (firstRayCastResult.GetActor()->ActorHasTag(FName(TEXT("Floor"))))
		{
			positionFindingWorked = true;
			return firstRayCastResult.ImpactPoint;
		}
		else
		{
			//hit something not floor, but blocking.  now we need to compute a new point.
			//go a little bit back to not hit the same object again and to spawn a bit in front of it.
			secondaryRayStartPoint = firstRayCastResult.ImpactPoint - CameraForward * 50.0;
		}
	}

	else
	{
		//hitpoint too far away. now we need to compute another point
		secondaryRayStartPoint = CameraPosition + CameraForward * maximalWalkingDistance;
	}

	
	FHitResult secondRayCastResult(ForceInit);
	rayCastWorked = this->GetWorld()->LineTraceSingle(secondRayCastResult, secondaryRayStartPoint, PlanetCenterWorldPoisition, ECC_Camera, traceParams);
	if (rayCastWorked  && secondRayCastResult.GetActor()->ActorHasTag(FName(TEXT("Floor"))))
	{
		positionFindingWorked = true;
		return secondRayCastResult.ImpactPoint;
	}
	
	

	return FVector(0,0,0);
}