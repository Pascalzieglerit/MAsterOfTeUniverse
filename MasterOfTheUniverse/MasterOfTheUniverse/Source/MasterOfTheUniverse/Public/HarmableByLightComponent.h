// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "HarmableByLightComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MASTEROFTHEUNIVERSE_API UHarmableByLightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHarmableByLightComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	//this function checks if this component is lightened by this lightsource. returns true if so.
	//distance will be the distance to the light source if the component is lit by it. if not it will be the distance to the shadowing object.
	UFUNCTION(BlueprintCallable, Category = "Light Damage")
	bool hitByLightSource(float& distance, AActor* lightsource);
	
};
