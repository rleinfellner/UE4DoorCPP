//Code can be found at
//https://gist.github.com/rleinfellner/9775c3286ae5da0bf1020cbc0af4e42a

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h" //Needed for static Mesh Component
#include "HingeComp.generated.h"

//IMPORTANT
//If your project name changes you must
//Change UE4DOOR_API below to match
//Or this will not compile
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4DOOR_API UHingeComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHingeComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    //Door control variables used in UE4 IDE /BP
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=DoorControl)
    FRotator    OpenAngle; //Angle when Open

    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=DoorControl)
        TSubclassOf<USceneComponent> Door;


    UFUNCTION(BlueprintCallable, Category = DoorControl)
    bool SetOpen(bool isOpen=true);
    
private:
    float   CurrentLERP; //Current LERP from 0.0=Closed - 1.0=Open
    bool    isBusy; //Is door busy with last operation?
       
    FRotator    InitialAngle; //Angle when started
    FRotator    FinalAngle; //Angle when complete

    
private:
    void    AnimateDoor(float DeltaTime); //Animate door on Tick

    void    BeginDoor(); //Set door on startup
};
