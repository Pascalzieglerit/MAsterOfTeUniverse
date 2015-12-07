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
	//when the user stars to rotate a planet (or any object) this position will be set. rel from this position the rotating hand will control the rotation
	FVector relativePositionAtBeginOfRotate;



	// Sets default values for this component's properties
	UGodlyHandsBehavior();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//returns true if something was picked up. if the hand was full allready it will be emptied and nothing will be picked up.
	UFUNCTION(BlueprintCallable, Category = "Grabbing")
	bool onGodlyGrab(class UPrimitiveComponent* input);

	//returns true if something was grabbed to rotate
	UFUNCTION(BlueprintCallable, Category = "Grabbing")
	bool grabToRotate(class UPrimitiveComponent* input);

	//returns true if something was grabbed to rotate and is now released
	UFUNCTION(BlueprintCallable, Category = "Grabbing")
	bool endRotating();

	
};
