// Created by CC. All rights reserved.

#include "TheDarkHour.h"
#include "GetWidgetRef.h"


// Sets default values for this component's properties
UGetWidgetRef::UGetWidgetRef()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGetWidgetRef::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGetWidgetRef::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

