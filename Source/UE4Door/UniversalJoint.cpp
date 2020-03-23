// Fill out your copyright notice in the Description page of Project Settings.


#include "UniversalJoint.h"

// Sets default values for this component's properties
UUniversalJoint::UUniversalJoint()
{
	//We need to tick as this allows the smooth change
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UUniversalJoint::BeginPlay()
{
	Super::BeginPlay();
	Begin(); //Call My Init code
}


// Called every frame, used to animate door
void UUniversalJoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Animate(DeltaTime); //Play Door animation if needed
}

//Alow safe get of Active State
bool UUniversalJoint::isOffset()
{
	return isOffsetFlag;
}


//Change the door state if not busy, and its its need changing
//Returns false if busy
bool UUniversalJoint::SetOffset(bool vActive)
{
	if (isBusy)  return  false; //Door is busy, ignore command

	if (vActive == isOffsetFlag)	return true; //Already in the state we want

	CurrentLERP = 0.0f;   //Reset LERP
	if (isOffsetFlag)
	{
		FromAngle = InitialAngle + OffsetAngle;
		ToAngle = InitialAngle; //Go from Active to Inactive
	}
	else
	{
		FromAngle = InitialAngle;
		ToAngle = InitialAngle + OffsetAngle; //Go from Inactive to Active
	}
	isBusy = true;    //Allow tick to animate component
	return  true; //Success
}

bool UUniversalJoint::SetOffsetDeferred(bool vActive)
{
	isOffsetFlagDeferred = vActive; //Set Deferred update flag
	return	!isBusy; //If we were not busy it will  get done on next tick
}

void UUniversalJoint::Animate(float DeltaTime)
{
	if (isBusy)
	{
		FRotator CurrentRotation = FMath::Lerp(FromAngle, ToAngle, CurrentLERP); //Get Current rotation
		SetRelativeRotation(CurrentRotation, false, 0, ETeleportType::None);
		CurrentLERP += DeltaTime;
		if (CurrentLERP >= 1.0)
		{
			SetRelativeRotation(ToAngle, false, 0, ETeleportType::None);
			isOffsetFlag = !isOffsetFlag;	//Flip Flag
			isBusy = false;	//Done with movement
		}
	}
	else //Handle deferred offset
	{
		if (isOffsetFlagDeferred != isOffsetFlag)
		{
			SetOffset(isOffsetFlagDeferred);
		}
	}
}

void UUniversalJoint::Begin()
{
	isBusy = false;		//Defaults setup
	isOffsetFlag = false;		//Door Starts inactive
	CurrentLERP = 0.0;
	FQuat tStartRot = GetRelativeRotationFromWorld(GetComponentQuat());	//Get Relative rotation of component
	InitialAngle = FRotator(tStartRot); //Keep hold of intial rotation, which will be used as an offset
}

