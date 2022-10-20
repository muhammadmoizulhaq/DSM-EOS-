// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Net/UnrealNetwork.h"

#include "SampleMultiplayerCharacter.generated.h"

UCLASS(config=Game)
class ASampleMultiplayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ASampleMultiplayerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to make character sprint.
	 */
	void Sprint();

	/**
	 * Called via input to make character walk.
	 */
	void Walk();

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/** This is a server RPC for running, marked as reliable */
	UFUNCTION(Server, Reliable)
	void OnServerSprint(float InSprintVal);
	void OnServerSprint_Implementation(float InSprintVal);

	/** This is a server RPC for walking, marked as reliable */
	UFUNCTION(Server, Reliable)
	void OnServerWalk(float InWalkVal);
	void OnServerWalk_Implementation(float InWalkVal);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Creating a RepNotify Username Variable. */
	UPROPERTY(ReplicatedUsing = OnRep_Username, BlueprintReadWrite, Category = "DSMS|Replication")
	FString Username;
	/** Callback function when the property is updated over the network. */
	UFUNCTION()
	void OnRep_Username();
	/** the implementing native event to call from blueprint while the repnotify (Username) callback function fired. */
	UFUNCTION(BlueprintNativeEvent, Category = "DSMS|Replication")
	void SetUsername();

};