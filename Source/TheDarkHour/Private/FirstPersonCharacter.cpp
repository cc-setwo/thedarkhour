// Created by CC. All rights reserved.

#include "TheDarkHour.h"
#include "FirstPersonCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	 
}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay() 
{
	Super::BeginPlay();		
	Capsule = GetCapsuleComponent();
	CharacterMovement = GetCharacterMovement();

	Camera = FindComponentByClass<UCameraComponent>();
	CameraLocation = Camera->GetRelativeTransform().GetLocation();
	
	UCurveFloat* curve = CurveInitialize();
	FOnTimelineFloat progressFunction{};
	progressFunction.BindUFunction(this, "OnCurveUpdate");

	time = FTimeline();
	time.AddInterpFloat(curve, progressFunction, TEXT("Float Function"));
	
	FOnTimelineEvent TimeLineEventForFinishCurve{};
	TimeLineEventForFinishCurve.BindUFunction(this, "OnCurveFinish");
	time.SetTimelineFinishedFunc(TimeLineEventForFinishCurve);
	UsualSpeed = CharacterMovement->MaxWalkSpeed;
	bIsCrouching = 0;	
}

UCurveFloat* AFirstPersonCharacter::CurveInitialize()
{	
	auto curve = NewObject<UCurveFloat>();
	curve->FloatCurve.AddKey(0.f, 0.f);
	curve->FloatCurve.AddKey(0.5f, 1.f);	
	return curve;
}

//void AFirstPersonCharacter::StartSprint(float val)
//{
//	CharacterMovement->MaxWalkSpeed = val;
//}

void AFirstPersonCharacter::StartCrouch()
{	
	bIsCrouching = 1;		
	time.Play();
}

void AFirstPersonCharacter::StopCrouch()
{	
	bIsCrouching = 0;		
}

void AFirstPersonCharacter::OnCurveUpdate(float val)
{	
	if (val == 0) { return; }
	
	if (bIsBlocking == 1 && bIsCrouching == 0)
	{
		time.Stop();
		//return;
	}

	Capsule->SetCapsuleHalfHeight(FMath::Lerp(96.f, 48.f, val));// TODO Magic numbers 96 48	
	Camera->SetRelativeLocation(FMath::Lerp(CameraLocation, FVector(CameraLocation.X, CameraLocation.Y, CameraLocation.Z - 20), val), true); // TODO Magic number -20
	
	CharacterMovement->MaxWalkSpeed = FMath::Lerp(UsualSpeed, CrouchSpeed, val);	
}

void AFirstPersonCharacter::OnCurveFinish()
{
	if (!bIsCrouching)
	{
		CharacterMovement->MaxWalkSpeed = UsualSpeed;
	}
}

// Called every frame
void AFirstPersonCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );	
	
	


	if(bIsCrouching == 0)
	{
		auto ActorLoc = GetActorLocation();
		FHitResult out;
		TArray<TEnumAsByte<ECollisionChannel> > ToTrace;
		ToTrace.Add(ECollisionChannel::ECC_WorldDynamic);
		ToTrace.Add(ECollisionChannel::ECC_WorldStatic);
		bIsBlocking = UKismetSystemLibrary::SphereTraceSingleByObject_DEPRECATED(this,
			ActorLoc,
			FVector(ActorLoc.X, ActorLoc.Y, ActorLoc.Z + 64), // //////////////////////////WEAKNESS
			35,
			ToTrace,
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::ForDuration,
			out,
			true);
		
		if(bIsBlocking == 0) // for standing up!
		{			
			time.Reverse();
		}		
	}	
	if (time.IsPlaying())
	{
		time.TickTimeline(DeltaTime);
	}
}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}