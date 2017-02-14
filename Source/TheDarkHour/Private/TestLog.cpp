// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDarkHour.h"
#include "TestLog.h"


// Sets default values for this component's properties
UTestLog::UTestLog()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTestLog::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("hello!"));
	// ...
	
}


// Called every frame
void UTestLog::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

