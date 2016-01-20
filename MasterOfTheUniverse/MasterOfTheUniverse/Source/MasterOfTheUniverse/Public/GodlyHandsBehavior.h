// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <iostream>
#include "Components/ActorComponent.h"
#include "GodlyHandsBehavior.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MASTEROFTHEUNIVERSE_API UGodlyHandsBehavior : public UActorComponent
{
	GENERATED_BODY()



public:	

	AActor* ObjectToTurn;
	bool turnObject;
	UPrimitiveComponent* rotatingHand;




	// Sets default values for this component's properties
	UGodlyHandsBehavior();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//returns true if something was picked up.
	UFUNCTION(BlueprintCallable, Category = "Grabbing")
	bool onGodlyGrab(class UPrimitiveComponent* input);

	//returns true if something was let go. if the hand was full it will be emptied and return true.
	UFUNCTION(BlueprintCallable, Category = "Grabbing")
	bool onGodlyLetGo(class UPrimitiveComponent* input);

	//returns true if something was grabbed to rotate
	UFUNCTION(BlueprintCallable, Category = "Grabbing")
	bool grabToRotate(class UPrimitiveComponent* input);

	//returns true if something was grabbed to rotate and is now released
	UFUNCTION(BlueprintCallable, Category = "Grabbing")
	bool endRotating();

	//returns a normalized vector which points from the userPosition towards the zoomDirection.
	UFUNCTION(BlueprintCallable, Category = "Zoom Gesture")
	FVector initializeZoomGesture(class UPrimitiveComponent* inputLeft, class UPrimitiveComponent* inputRight, FVector userPosition);

	//ends the zooming gesture
	UFUNCTION(BlueprintCallable, Category = "Zoom Gesture")
	void endZoomGesture();

	//returns a vector which points from the userPosition towards the zoomDirection (call initializeZoomGesture first). the length of the vector is the zoom amount.
	UFUNCTION(BlueprintCallable, Category = "Zoom Gesture")
	FVector getZoomAmount();

	//hallo markus




private:
	//vector used for computing the rotation quaternion each frame
	FVector oldGrabbingToTurnVector;
	//the rotation quaternion if god is rotationg something
	FQuat rotationQuaternion;
	//the left hand which is used zooming
	UPrimitiveComponent* leftZoomHand;
	//the right hand which is used zooming
	UPrimitiveComponent* rightZoomHand;
	//the position of the user zooming
	FVector zoomUserPosition;
	//used to fast check during zoomUserPosition
	bool zoomInitalized;
	//the object that is zoomed
	AActor* zoomedObject;
	//float used to compute the rel zoom the zoomed object
	float oldZoomAmount;
	//original scale of object before zooming
	FVector oldZoomScale;

	//update the object to turn
	void tickTurnObject();
	//update the object to zoom
	void tickZoomObject();
	
};
