// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GimbalHinge.generated.h"

//IMPORTANT
//If your project name changes you must
//Change XXXXXXX_API below to match
//Or this will not compile
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4DOOR_API UGimbalHinge : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGimbalHinge();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//IDE exposed variables/functions
public:
	//Door control variables used in UE4 IDE /BP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DoorControl)
	FRotator    OpenAngle; //Angle when Open

	//Get for current Open State
	UFUNCTION(BlueprintCallable, Category = DoorControl)
	bool	IsOpen();

	//Get Toggle Open/Closed
	UFUNCTION(BlueprintCallable, Category = DoorControl)
	bool	ToggleOpen();

	//Private Variables/Functions
private:
	float   CurrentLERP; //Current LERP from 0.0=Closed - 1.0=Open
	bool    isBusy; //Is door busy with last operation?
	bool	isOpenFlag; //Is it Open or closed?
	FRotator    InitialAngle;	//Initial Door angle
	FRotator    FromAngle;		//Angle when started
	FRotator    ToAngle;		//Angle when complete

private: //Code declaration
	void    AnimateDoor(float DeltaTime); //Animate door on Tick
	void    BeginDoor(); //Set door on startup
};
