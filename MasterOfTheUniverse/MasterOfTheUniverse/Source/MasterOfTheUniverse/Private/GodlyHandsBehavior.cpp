// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterOfTheUniverse.h"
#include "GodlyHandsBehavior.h"


// Sets default values for this component's properties
UGodlyHandsBehavior::UGodlyHandsBehavior()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGodlyHandsBehavior::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGodlyHandsBehavior::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	//UE_LOG(LogTemp, Warning, TEXT("TICK"));
	

	// ...
}

void UGodlyHandsBehavior::onGodlyGrab(class UActorComponent* parent, bool grabbingButtonPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("GRAB"));
	if (!grabbingButtonPressed)
	{
		return;
	}

	
	

	//TODO:
	//check out all overlapping objects of parent
	//take the first one and change its parent to parent
}