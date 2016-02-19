// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterOfTheUniverse.h"
#include "HarmableByLightComponent.h"


// Sets default values for this component's properties
UHarmableByLightComponent::UHarmableByLightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHarmableByLightComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHarmableByLightComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

bool UHarmableByLightComponent::hitByLightSource(float& distance, AActor* lightsource)
{
	//TODO

	FCollisionQueryParams traceParams(FName(TEXT("Finding Light Source Trace")), true, this->GetOwner());
	traceParams.bTraceComplex = true;
	//TraceParams.bTraceAsyncScene = true;
	//Re-initialize hit info
	FHitResult firstRayCastResult(ForceInit);

	bool rayCastWorked = this->GetWorld()->LineTraceSingle(firstRayCastResult, this->GetOwner()->GetActorLocation(), lightsource->GetActorLocation(), ECC_Visibility, traceParams);

	float distanceToLightSource = (this->GetOwner()->GetActorLocation() - lightsource->GetActorLocation()).Size();

	if (rayCastWorked)
	{
		distance = firstRayCastResult.Distance;
		//if nothing was hit but the lightsource thats a hit still.
		return (distanceToLightSource >= distance);
	}
	//nothing was hit. not even the light source.
	distance = distanceToLightSource;
	return false;
}