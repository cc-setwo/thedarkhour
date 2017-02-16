// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDarkHour.h"
#include "FirstPersonCharacter.h"


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
	
}

//void AFirstPersonCharacter::Assign(UCapsuleComponent* cap, UCharacterMovementComponent* characterMovement)
//{
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
	/*if (Controller)
	{
		CrouchImpl(DeltaTime);
	}*/
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
