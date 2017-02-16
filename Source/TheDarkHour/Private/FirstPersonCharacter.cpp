// Created by CC. All rights reserved.

#include "TheDarkHour.h"
#include "FirstPersonCharacter.h"
#include "PhysicsEngine/PhysicsSettings.h"


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
	
	
	UsualSpeed = CharacterMovement->MaxWalkSpeed;
	bIsCrouching = 0;
}

UCurveFloat* AFirstPersonCharacter::CurveInitialize()
{	
	auto curve = NewObject<UCurveFloat>();
//	auto key = curve->FloatCurve.AddKey(0.f, 0.f);
	curve->FloatCurve.AddKey(0.f, 0.f);
	curve->FloatCurve.AddKey(0.5f, 1.f);
	//curve->FloatCurve.SetKeyTime(key, 0.5f);
	//curve->FloatCurve.SetKeyInterpMode(key, RCIM_Linear);
	return curve;
}

void AFirstPersonCharacter::StartCrouch()
{
	bIsCrouching = 1;
	//CharacterMovement->MaxWalkSpeed = CrouchSpeed;
	//UsualSpeed = CharacterMovement->MaxWalkSpeed;
	time.PlayFromStart();
}

void AFirstPersonCharacter::StopCrouch()
{
	bIsCrouching = 0;
	//CharacterMovement->MaxWalkSpeed = 600;
	time.Reverse();	
}

void AFirstPersonCharacter::OnCurveUpdate(float val)
{
	if(bIsCrouching == 0)
	{
	
	}
	if (bIsBlocking == 1)
	{
		time.Stop();
		return;
	}
	Capsule->SetCapsuleHalfHeight(FMath::Lerp(96.f, 48.f, val));// TODO Magic numbers 96 48
	
	Camera->SetRelativeLocation(FMath::Lerp(CameraLocation, FVector(CameraLocation.X, CameraLocation.Y, CameraLocation.Z - 20), val), true); // TODO Magic number -20
	//if (bIsCrouching == 0)
	//{
	CharacterMovement->MaxWalkSpeed = FMath::Lerp(UsualSpeed, CrouchSpeed, val);
	//}
	//UE_LOG(LogTemp, Warning, TEXT("%f"), val)
}

//void AFirstPersonCharacter::Assign(UCapsuleComponent* cap, UCharacterMovementComponent* characterMovement)  UE_LOG(LogTemp, Warning, TEXT("Success!"))
//{																											  UE_LOG(LogTemp, Warning, TEXT("%s"),*CameraLocation.ToString())
//	CapsuleComponent = cap;
//	CharacterMovement = characterMovement;
//
//	CapsuleComponent->InitCapsuleSize(40.0f, 85.0f);
//	CapsuleComponent->SetHiddenInGame(false);
//
//	CharacterMovement->NavAgentProps.bCanCrouch = true;
//	CharacterMovement->CrouchedSpeedMultiplier_DEPRECATED = 0.5f;
//	//CharacterMovement->CrouchedSpeedMultiplier = 0.5f;
//
//	bIsCrouching = false;
//
//	DecBEH = BaseEyeHeight;
//	DecCapsHeight = CapsuleComponent->GetUnscaledCapsuleHalfHeight();
//}

// Called every frame
void AFirstPersonCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	if (time.IsPlaying()) 
	{
		time.TickTimeline(DeltaTime);
	}

	if(bIsCrouching == 0)
	{
		auto ActorLoc = GetActorLocation();
		FHitResult out;
		//DrawDebugLine(GetWorld(), ActorLoc, FVector(ActorLoc.X, ActorLoc.Y, ActorLoc.Z + 150), FColor(255, 0, 0), true, -1, 0, 12.333);
		//bool k = VTraceSphere(this, ActorLoc, FVector(150), 150, out);
		TArray<TEnumAsByte<ECollisionChannel> > ToTrace;
		ToTrace.Add(ECollisionChannel::ECC_WorldDynamic);
		ToTrace.Add(ECollisionChannel::ECC_WorldStatic);
		
		bIsBlocking = SphereTraceSingleByObject_DEPRECATED(
			this,
			ActorLoc,
			FVector(ActorLoc.X, ActorLoc.Y, ActorLoc.Z + 150),
			35,
			ToTrace,
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::ForDuration,
			out,
			true);
		
		
		if(bIsBlocking == 0)
		{
			time.Reverse();
		}
		
	}

	/*if (Controller)
	{
		CrouchImpl(DeltaTime);
	}*/
}

FORCEINLINE bool AFirstPersonCharacter::VTraceSphere(
	AActor* ActorToIgnore,
	const FVector& Start,
	const FVector& End,
	const float Radius,
	FHitResult& HitOut
	//ECollisionChannel TraceChannel = ECC_Pawn
) {
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
	TraceParams.bTraceComplex = false;
	//TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;

	//Ignore Actors
	TraceParams.AddIgnoredActor(ActorToIgnore);

	//Re-initialize hit info
	HitOut = FHitResult(ForceInit);

	//Get World Source
	//TObjectIterator< APlayerController > ThePC;
	//if (!ThePC) return false;

	ECollisionChannel TraceChannel = ECC_Pawn;
	
	return this->GetWorld()->SweepSingleByObjectType(
		HitOut,
		Start,
		End,
		FQuat(),
		TraceChannel,
		FCollisionShape::MakeSphere(Radius),
		TraceParams
	);


}

bool AFirstPersonCharacter::SphereTraceSingleByObject_DEPRECATED(UObject* WorldContextObject, const FVector Start, const FVector End, float Radius,
	const TArray<TEnumAsByte<ECollisionChannel> > & ObjectsToTrace, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType, FHitResult& OutHit, bool bIgnoreSelf)
{
	static const FName SphereTraceSingleName(TEXT("SphereTraceSingle"));

	FCollisionQueryParams Params(SphereTraceSingleName, bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.bReturnFaceIndex = !UPhysicsSettings::Get()->bSuppressFaceRemapTable; // Ask for face index, as long as we didn't disable globally
	Params.bTraceAsyncScene = true;
	Params.AddIgnoredActors(ActorsToIgnore);
	if (bIgnoreSelf)
	{

		AActor* IgnoreActor = Cast<AActor>(WorldContextObject);
		if (IgnoreActor)
		{
			Params.AddIgnoredActor(IgnoreActor);
		}
		else
		{
			// find owner
			UObject* CurrentObject = WorldContextObject;
			while (CurrentObject)
			{
				CurrentObject = CurrentObject->GetOuter();
				IgnoreActor = Cast<AActor>(CurrentObject);
				if (IgnoreActor)
				{
					Params.AddIgnoredActor(IgnoreActor);
					break;
				}
			}
		}
	}

	FCollisionObjectQueryParams ObjectParams;
	for (auto Iter = ObjectsToTrace.CreateConstIterator(); Iter; ++Iter)
	{
		const ECollisionChannel & Channel = (*Iter);
		if (FCollisionObjectQueryParams::IsValidObjectQuery(Channel))
		{
			ObjectParams.AddObjectTypesToQuery(Channel);
		}
		else
		{
			UE_LOG(LogBlueprintUserMessages, Warning, TEXT("%d isn't valid object type"), (int32)Channel);
		}
	}

	if (ObjectParams.IsValid() == false)
	{
		UE_LOG(LogBlueprintUserMessages, Warning, TEXT("Invalid object types"));
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	bool const bHit = World->SweepSingleByObjectType(OutHit, Start, End, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(Radius), Params);

	return bHit; 
}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


//void AFirstPersonCharacter::CrouchStart()
//{
//	CharacterMovement->bWantsToCrouch = true;
//	/*if (Controller != NULL)
//	{
//		bIsCrouching = true;
//		bCoolDown = true;
//		FTimerHandle time_handler;
//		///this->GetWorldTimerManager().SetTimer(time_handler, this, &AFirstPersonCharacter::CoolDownDone, 2.f, false);
//	
//	}*/
//}
//
//
//void AFirstPersonCharacter::CrouchEnd()
//{
//	CharacterMovement->bWantsToCrouch = false;
//	/*if (Controller != NULL)
//	{
//		bIsCrouching = false;
//	}*/
//}
//
//void AFirstPersonCharacter::CoolDownDone()
//{	
//	//bCoolDown = false;
//	//bIsCrouching = false;
//	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
//}
//
//void AFirstPersonCharacter::CrouchImpl(float DeltaTime)
//{
//	
//	
//		const float TargetBEH = bIsCrouching ? CrouchedEyeHeight : DecBEH;
//		const float TargetCapsuleSize = bIsCrouching ? CharacterMovement->CrouchedHalfHeight : DecCapsHeight;
//		if (Controller != NULL)
//		{
//			BaseEyeHeight = FMath::FInterpTo(BaseEyeHeight, TargetBEH, DeltaTime, 10.0f);
//			CapsuleComponent->SetCapsuleHalfHeight(FMath::FInterpTo(CapsuleComponent->GetUnscaledCapsuleHalfHeight(), TargetCapsuleSize, DeltaTime, 10.0f), true);
//			// Dist and DeltaMovCaps are used for the interpolation value added to RelativeLocation.Z
//			const float Dist = TargetCapsuleSize - CapsuleComponent->GetUnscaledCapsuleHalfHeight();
//			const float DeltaMovCaps = Dist*FMath::Clamp<float>(DeltaTime*10.0f, 0.f, 1.f);
//			CapsuleComponent->SetRelativeLocation(FVector(CapsuleComponent->RelativeLocation.X, CapsuleComponent->RelativeLocation.Y, (CapsuleComponent->RelativeLocation.Z + DeltaMovCaps)), true);
//		}
//	
////	FTimerHandle InOutHandle;
//	//GetWorldTimerManager().SetTimer(InOutHandle, &AFirstPersonCharacter::CoolDownDone, 1.f, false);
//
//	
//}
