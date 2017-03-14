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
	float UsualSpeed = 0.f;	
	FVector CameraLocation;

	UCameraComponent* Camera;
	UCapsuleComponent* Capsule = nullptr;
	UCharacterMovementComponent* CharacterMovement = nullptr;
	UCurveFloat* CurveInitialize();	
	UPROPERTY()
		struct FTimeline time;

	UFUNCTION()
		void OnCurveUpdate(float val);	

	UFUNCTION()
		void OnCurveFinish();

	//Sprint
	UPROPERTY()
		struct FTimeline timeSprint;

	UFUNCTION()
		void OnCurveUpdateSprint(float val);

	//UFUNCTION()
	//	void OnCurveUpdateFinish();

protected:
	UPROPERTY(BlueprintReadOnly, Category = Movement)
		bool bIsBlocking;
	
	UPROPERTY(BlueprintReadOnly, Category = Movement)
		uint32 bIsCrouching : 1;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		uint32 bRunning : 1;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		uint32 bStandingUp : 1;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float SprintSpeed = 800;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float CrouchSpeed = 200;

	//UFUNCTION(BlueprintCallable, Category = Movement) // TODO make sprint in c++
	//	void StartSprint(float val);

	UFUNCTION(BlueprintCallable, Category = Movement)
		void StartCrouch();

	UFUNCTION(BlueprintCallable, Category = Movement)
		void StopCrouch();
	
	//Sprint
	UFUNCTION(BlueprintCallable, Category = Movement)
		void StartSprint();

	UFUNCTION(BlueprintCallable, Category = Movement)
		void StopSprint();
};
