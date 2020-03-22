// Fill out your copyright notice in the Description page of Project Settings.


#include "UniversalMove.h"


// Sets default values for this component's properties
UUniversalMove::UUniversalMove()
{
	//We need to tick as this allows the smooth change
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UUniversalMove::BeginPlay()
{
	Super::BeginPlay();
	Begin(); //Call My Init code
}


// Called every frame, used to animate door
void UUniversalMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Animate(DeltaTime); //Play Door animation if needed
}

//Alow safe get of Active State
bool UUniversalMove::isOffset()
{
	return isOffsetFlag;
}


//Change the door state if not busy, and its its need changing
//Returns false if busy
bool UUniversalMove::SetOffset(bool vActive)
{
	if (isBusy)  return  false; //Door is busy, ignore command

	if (vActive == isOffsetFlag)	return true; //Already in the state we want

	CurrentLERP = 0.0f;   //Reset LERP
	if (isOffsetFlag)
	{
		FromVector = InitialVector + OffsetVector;
		ToVector = InitialVector; //Go from Active to Inactive
	}
	else
	{
		FromVector = InitialVector;
		ToVector = InitialVector + OffsetVector; //Go from Inactive to Active
	}
	isBusy = true;    //Allow tick to animate component
	return  true; //Success
}

void UUniversalMove::Animate(float DeltaTime)
{
	if (!isBusy) return; //Door not animating

	FVector CurrentLocation = FMath::Lerp(FromVector, ToVector, CurrentLERP); //Get Current position
	SetRelativeLocation(CurrentLocation, false, 0, ETeleportType::None);
	CurrentLERP += DeltaTime;
	if (CurrentLERP >= 1.0)
	{
		SetRelativeLocation(ToVector, false, 0, ETeleportType::None);
		isOffsetFlag = !isOffsetFlag;	//Flip Flag
		isBusy = false;	//Done with movement
	}
}

void UUniversalMove::Begin()
{
	isBusy = false;		//Defaults setup
	isOffsetFlag = false;		//Door Starts inactive
	CurrentLERP = 0.0;
	InitialVector = GetRelativeTransform().GetLocation(); //Keep hold of intial position, which will be used as an offset
}

