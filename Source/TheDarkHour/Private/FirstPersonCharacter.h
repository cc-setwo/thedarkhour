// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FirstPersonCharacter.generated.h"

UCLASS()
class AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector CameraLocation;
	UCameraComponent* Camera;

	UCapsuleComponent* Capsule = nullptr;
	UCharacterMovementComponent* CharacterMovement = nullptr;

	UCurveFloat* CurveInitialize();

	float UsualSpeed = 0.f;
	
	FORCEINLINE bool VTraceSphere(
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		const float Radius,
		FHitResult& HitOut
		//ECollisionChannel TraceChannel = ECC_Pawn
	);

	UPROPERTY()
	struct FTimeline time;
	UFUNCTION()
	void OnCurveUpdate(float val);

	bool SphereTraceSingleByObject_DEPRECATED(UObject* WorldContextObject, const FVector Start, const FVector End, float Radius,
		const TArray<TEnumAsByte<ECollisionChannel> > & ObjectsToTrace, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType, FHitResult& OutHit, bool bIgnoreSelf);
protected:
	/*UPROPERTY()
		UTimelineComponent* ScoreTimeline;

	UPROPERTY()
		UCurveFloat* fCurve;

	FOnTimelineFloat InterpFunction{};

	UFUNCTION()
		void TimelineFloatReturn(float val);*/
		
		

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		uint32 bIsCrouching : 1;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		bool bIsBlocking;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float CrouchSpeed = 200;

	UFUNCTION(BlueprintCallable, Category = Movement)
		void StartCrouch();
	UFUNCTION(BlueprintCallable, Category = Movement)
		void StopCrouch();
	
};
