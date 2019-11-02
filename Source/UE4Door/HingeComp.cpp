// Fill out your copyright notice in the Description page of Project Settings.


#include "HingeComp.h"
#include "Engine/GameEngine.h" //Needed for Debug Messages


// Sets default values for this component's properties
UHingeComp::UHingeComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHingeComp::BeginPlay()
{
	Super::BeginPlay();
    BeginDoor();
    if (GEngine) //Only in Debug build
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("INFO:Hello"))); //Show on screen
    }

}

// Called every frame
void UHingeComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    AnimateDoor(DeltaTime);
}

void    UHingeComp::AnimateDoor(float DeltaTime)
{
    if(!isBusy) return; //Door not animating
    
    AActor* tActor = GetOwner(); //Get door this Hinge is owned by
    if(IsValid(tActor)) //Ensure owner exists
    {
        FRotator CurrentRotation = FMath::Lerp(InitialAngle, FinalAngle, CurrentLERP); //Get Current rotation
        tActor->SetActorRotation(CurrentRotation, ETeleportType::None);
        CurrentLERP+=DeltaTime;
        if(CurrentLERP>=1.0)
        {
            tActor->SetActorRotation(FinalAngle, ETeleportType::None);
            isBusy=false;
        }
    }
}


//Set up door to initial state
void    UHingeComp::BeginDoor()
{
    isBusy=false;   //Defaults setup
    CurrentLERP=0.0;
    AActor* tActor = GetOwner(); //Get door this Hinge is owned by
    
    if(!IsValid(tActor)) //Make sure we have an Actor parent
    {
        if (GEngine) //Only in Debug build
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("ERROR:No Owning Actor"))); //Show on screen
        }
        return;
    }
    
    TArray<UActorComponent*> Children;
    tActor->GetComponents(Children);
    for(int i=0; i < Children.Num();i++)
    {
        for(int j=0; j < Children[i]->ComponentTags.Num() ; j++)
        {
            auto tTag = *Children[i]->ComponentTags[j].ToString();
            if (GEngine) //Only in Debug build
            {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Info:Child %s"),tTag)); //Show on screen
            }
        }
    }
    
    InitialAngle=tActor->GetActorRotation(); //Keep hold of intial rotation, which will be used as an offset
}





//Open or Close door
bool  UHingeComp::SetOpen(bool isOpen)
{
    if(isBusy)  return  false; //Door is busy, ignore command
    
    CurrentLERP=0.0f;   //Reset LERP
    FinalAngle = InitialAngle + OpenAngle; //Make up final angle
    isBusy=true;    //Allow tick to drive door
    return  true; //Success
}

