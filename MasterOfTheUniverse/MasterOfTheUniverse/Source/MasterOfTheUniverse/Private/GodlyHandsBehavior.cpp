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
	turnObject = false;
	this->zoomInitalized = false;
	// ...
}


// Called when the game starts
void UGodlyHandsBehavior::BeginPlay()
{
	Super::BeginPlay();

	this->rotationQuaternion = FQuat(0, 0, 0, 0);

	// ...
	
}


// Called every frame
void UGodlyHandsBehavior::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	//UE_LOG(LogTemp, Warning, TEXT("TICK"));
	
	//update the object to turn
	if (this->turnObject)
	{
		// OLD DEMO CODE
		//float pitch = this->rotatingHand->GetComponentLocation().Z - this->relativePositionAtBeginOfRotate.Z;
		//float roll = 0;
		//float yaw = this->rotatingHand->GetComponentLocation().Y - this->relativePositionAtBeginOfRotate.Y;
		//FRotator rotation = FRotator(pitch * DeltaTime, roll * DeltaTime, yaw * DeltaTime);
		//this->ObjectToTurn->AddActorLocalRotation(rotation);


		//this->ObjectToTurn->AddActorWorldRotation();
		

		FVector newGrabbingToTurnVector = (this->rotatingHand->GetComponentLocation() - this->ObjectToTurn->GetActorLocation());
		newGrabbingToTurnVector.Normalize();

		FVector rotationAxis = FVector::CrossProduct(oldGrabbingToTurnVector, newGrabbingToTurnVector);
		rotationAxis.Normalize();

		//true because I normalized first
		float CosOfRotationAngle = FVector::DotProduct(oldGrabbingToTurnVector, newGrabbingToTurnVector);

		this->rotationQuaternion = FQuat(rotationAxis, acos(CosOfRotationAngle) * 5);


		this->ObjectToTurn->AddActorWorldRotation(rotationQuaternion);


		this->oldGrabbingToTurnVector = newGrabbingToTurnVector;

	}
	else
	{
		//if the user lets go the rotation will be applied continuesly
		if (this->ObjectToTurn != NULL)
		{
			this->ObjectToTurn->AddActorWorldRotation(this->rotationQuaternion);
		}
	}
	

	// ...
}


bool UGodlyHandsBehavior::onGodlyGrab(class UPrimitiveComponent* input)
{

	UE_LOG(LogTemp, Warning, TEXT("GRAB"));
	
	//hand not empty => empty it
	if (input->GetNumChildrenComponents() > 0)
	{
		TArray< USceneComponent * > children;
		input->GetChildrenComponents(false, children);
		for (int i = 0; i < children.Num(); i++)
		{
			children[i]->DetachFromParent(true);
		}
		return false;
	}

	TArray< AActor * > overlappingActors = TArray< AActor * >();
	input->GetOverlappingActors(overlappingActors);

	//search for an object that is pickupable
	for (int i = 0; i < overlappingActors.Num(); i++)
	{
		if (overlappingActors[i]->ActorHasTag(FName(TEXT("PickUpByGod"))))
		{
			AActor* pickedUpObject = overlappingActors[i];
			const FTransform moep = pickedUpObject->GetTransform();
			pickedUpObject->AttachRootComponentTo(input);
			pickedUpObject->SetActorTransform(moep);
			pickedUpObject->SetActorLocation(input->GetComponentLocation());
			//ONLY PICK UP ONE OBJECT! remove thie return if you want to pick up all ovelrapping objects
			return true;
		}

	}

	return false;
}


bool UGodlyHandsBehavior::grabToRotate(class UPrimitiveComponent* input)
{
	//check wether there is another hand turning an object
	if (this->turnObject)
	{
		return false;
	}

	TArray< AActor * > overlappingActors = TArray< AActor * >();
	input->GetOverlappingActors(overlappingActors);

	//search for an object that is protatable
	for (int i = 0; i < overlappingActors.Num(); i++)
	{
		if (overlappingActors[i]->ActorHasTag(FName(TEXT("RotatableByGod"))))
		{
			this->ObjectToTurn = overlappingActors[i];
			this->turnObject = true;
			this->rotatingHand = input;
			this->relativePositionAtBeginOfRotate = input->GetComponentLocation();
			return true;
		}
	}

	return false;
}

bool UGodlyHandsBehavior::endRotating()
{
	bool ret = this->turnObject;
	this->turnObject = false;
	return ret;
}

FVector  UGodlyHandsBehavior::initializeZoomGesture(class UPrimitiveComponent* inputLeft, class UPrimitiveComponent* inputRight, FVector userPosition)
{
	//TODO
	this->leftZoomHand = inputLeft;
	this->rightZoomHand = inputRight;
	this->zoomUserPosition = userPosition;
	FVector middlePoint = 0.5 * (inputRight->GetComponentLocation() + inputLeft->GetComponentLocation());
	FVector ret = (middlePoint - userPosition);
	ret.Normalize();
	this->zoomInitalized = true;
	return ret;
}

FVector  UGodlyHandsBehavior::getZoomAmount()
{
	if (this->zoomInitalized == false)
	{
		return FVector(0, 0, 0);
	}
	
	FVector middlePoint = 0.5 * (this->leftZoomHand->GetComponentLocation() + this->rightZoomHand->GetComponentLocation());
	FVector ret = (middlePoint - this->zoomUserPosition);
	ret.Normalize();
	ret = ret * (this->leftZoomHand->GetComponentLocation() - this->rightZoomHand->GetComponentLocation()).Size();
	return ret;
}