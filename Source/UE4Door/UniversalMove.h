// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UniversalMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4DOOR_API UUniversalMove : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUniversalMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//IDE exposed functions
public:
	//UniMove control variables used in UE4 IDE /BP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UniMove)
		FVector    OffsetVector; //Vector Offset when Active(Open)

		//Get for current On State
	UFUNCTION(BlueprintPure, Category = UniMove)
		bool	isOffset(); //Is it offset (open)

		//Get Toggle Open/Closed, can be pure as its a getter
	UFUNCTION(BlueprintCallable, Category = UniMove)
		bool	SetOffset(bool vActive);


	//Private Variables/Functions
private:
	float   CurrentLERP; //Current LERP from 0.0=Closed - 1.0=Open
	bool    isBusy; //Is door busy with last operation?
	bool	isOffsetFlag; //Is it Open or closed?
	FVector    InitialVector;	//Initial Door position
	FVector    FromVector;		//position when started
	FVector    ToVector;		//position when complete

private: //Code declaration
	void    Animate(float DeltaTime); //Animate door on Tick
	void    Begin(); //Set door on startup		
};
