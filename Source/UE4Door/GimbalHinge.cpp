// Fill out your copyright notice in the Description page of Project Settings.


#include "GimbalHinge.h"
#include "Engine/GameEngine.h" //Needed for Debug Messages


// Sets default values for this component's properties
UGimbalHinge::UGimbalHinge()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGimbalHinge::BeginPlay()
{
	Super::BeginPlay();
	BeginDoor();	//Do door setup
	
}


// Called every frame
void UGimbalHinge::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AnimateDoor(DeltaTime);	//Animate Door
}



//Gimbal Hinge code
//Set the door to a new state
bool UGimbalHinge::ToggleOpen()
{
	if (isBusy)  return  false; //Door is busy, ignore command

	CurrentLERP = 0.0f;   //Reset LERP
	if (isOpenFlag)
	{
		FromAngle = InitialAngle + OpenAngle;
		ToAngle = InitialAngle; //Go from Open to CLosed
	}
	else
	{
		FromAngle = InitialAngle;
		ToAngle = InitialAngle + OpenAngle; //Go from Closed to Open
	}
	isBusy = true;    //Allow tick to drive door
	return  true; //Success
}


//Getter for Open state
bool UGimbalHinge::IsOpen()
{
	return isOpenFlag;
}

void UGimbalHinge::AnimateDoor(float DeltaTime)
{
	if (!isBusy) return; //Door not animating

	FRotator CurrentRotation = FMath::Lerp(FromAngle, ToAngle, CurrentLERP); //Get Current rotation
	SetRelativeRotation(CurrentRotation,false,0, ETeleportType::None);
	CurrentLERP += DeltaTime;
	if (CurrentLERP >= 1.0)
	{
		SetRelativeRotation(ToAngle, false, 0, ETeleportType::None);
		isOpenFlag = !isOpenFlag;	//Flip Flag
		isBusy = false;	//Done with movement
	}
}

void UGimbalHinge::BeginDoor()
{
	isBusy = false;		//Defaults setup
	isOpenFlag = false;		//Door Starts closed
	CurrentLERP = 0.0;
	FQuat tStartRot = GetRelativeRotationFromWorld(GetComponentQuat());	//Get Relative rotation of component
	InitialAngle = FRotator(tStartRot); //Keep hold of intial rotation, which will be used as an offset
}

