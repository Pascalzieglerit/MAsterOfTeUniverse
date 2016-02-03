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

FVector UEarthWalkerBehaviour::getWalkingPosition(bool& positionFindingWorked, FVector PlanetCenterWorldPoisition, FVector CameraPosition, FVector CameraForward)
{
	positionFindingWorked = false;
	FCollisionQueryParams traceParams(FName(TEXT("Walker Trace")), true, this->GetOwner());
	traceParams.bTraceComplex = true;
	//TraceParams.bTraceAsyncScene = true;
	//Re-initialize hit info
	FHitResult firstRayCastResult(ForceInit);

	bool rayCastWorked = this->GetWorld()->LineTraceSingle(firstRayCastResult, CameraPosition, CameraPosition - CameraForward * 9999, ECC_Camera, traceParams);

	if (rayCastWorked)
	{
		FHitResult secondRayCastResult(ForceInit);
		rayCastWorked = this->GetWorld()->LineTraceSingle(secondRayCastResult, firstRayCastResult.ImpactPoint,  PlanetCenterWorldPoisition, ECC_Camera, traceParams);
		if (rayCastWorked  && secondRayCastResult.GetActor()->ActorHasTag(FName(TEXT("Floor"))))
		{
			positionFindingWorked = true;
			return secondRayCastResult.ImpactPoint;
		}
	}

	return FVector(0,0,0);
}