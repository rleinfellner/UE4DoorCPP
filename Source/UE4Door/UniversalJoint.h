// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UniversalJoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4DOOR_API UUniversalJoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUniversalJoint();

protected:
	// Called when the game startsD
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//IDE exposed functions
public:
	//UniJoint control variables used in UE4 IDE /BP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UniJoint)
	FRotator    OffsetAngle; //Angle Offset when Active(Open)

	//Get for current On State
	UFUNCTION(BlueprintPure, Category = UniJoint)
	bool	isOffset(); //Is it offset (open)

	//Get Toggle Open/Closed, can be pure as its a getter
	UFUNCTION(BlueprintCallable, Category = UniJoint)
	bool	SetOffset(bool vActive);

	//Get Toggle Open/Closed, can be pure as its a getter
	UFUNCTION(BlueprintCallable, Category = UniJoint)
	bool	SetOffsetDeferred(bool vActive);


	//Private Variables/Functions
private:
	float   CurrentLERP; //Current LERP from 0.0=Closed - 1.0=Open
	bool    isBusy; //Is door busy with last operation?
	bool	isOffsetFlag; //Is it Open or closed?
	FRotator    InitialAngle;	//Initial Door angle
	FRotator    FromAngle;		//Angle when started
	FRotator    ToAngle;		//Angle when complete

	bool    isOffsetFlagDeferred; //Do we have a De?

private: //Code declaration
	void    Animate(float DeltaTime); //Animate door on Tick
	void    Begin(); //Set door on startup		
};
