// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "PunchKick01Character.generated.h"

UENUM(BlueprintType)
enum class ELogLevel : uint8
{
	TRACE			UMETA(DisplayName = "Trace"),
	DEBUG			UMETA(DisplayName = "Debug"),
	INFO			UMETA(DisplayName = "Info"),
	WARNING			UMETA(DisplayName = "Warning"),
	ERROR			UMETA(DisplayName = "Error")
};

UENUM(BlueprintType)
enum class ELogOutput : uint8
{
	ALL				UMETA(DisplayName = "All levels"),
	OUTPUT_LOG		UMETA(DisplayName = "Output log"),
	SCREEN			UMETA(DisplayName = "Screen")
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	MELEE_FIST			UMETA(DisplayName = "Melee - Fist")
};

/*
 *
 */
/*UENUM(Blueprintable, meta = (Bitflags))
enum class EAttackSection : uint8
{
	Start_1,
	Start_2,
	//Count UMETA(Hidden)
};
ENUM_CLASS_FLAGS(EAttackSection)*/

UCLASS(config=Game)
class APunchKick01Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = true))
	//TSubclassOf<UAnimMontage> MeleeFistAttack;

	/* Melee fist attack montage */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* MeleeFistAttackMontage;

	/* Melee attack play rate */
	UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true", UIMin = -2.f, UIMax=2.f))
	float AttackPlayRate = 1.f;

	//UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true"))
	//FName AttackSection = "Start_1";

	//UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (Bitmask, BitmaskEnum = "EAttackSection", AllowPrivateAccess = true))
	//uint8 AttackSections;

	UPROPERTY(EditAnywhere, Category = Animation,
		meta = (AllowPrivateAccess = true, ClampMin = 0, UIMin = 0, UIMax = 100))
	int32 NumberOfAttacksSeed = 0;

	/* Number of melee attack sections */
	UPROPERTY(EditAnywhere, Category = Animation, /*DisplayName = "Number Of Attacks",*/
		meta = (AllowPrivateAccess = true, ClampMin = 1, ClampMax = 3, UIMin = 1, UIMax = 3))
	int32 NumberOfAttackSections = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = true))
	UBoxComponent* FistColBoxLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = true))
	UBoxComponent* FistColBoxRight;

public:
	APunchKick01Character();

	/* Called when the game starts or when the player is spawn */
	virtual void BeginPlay() override;

	/*
	* AttackStart - trrigered when the player initiates an attack
	*/
	void AttackStart();

	/*
	* AttackEnd - trrigered when the player stops the attack
	*/
	void AttackEnd();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	/** Resets HMD orientation in VR. */
	void OnResetVR();

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
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	/**
	* Log - prints a message to all the log outputs with a specific color
	* @param LogLevel {@see ELogLevel} affects color of log
	* @param FString the message for display
	*/
	void Log(ELogLevel LogLevel, FString Message);
	/**
	* Log - prints a message to all the log outputs with a specific color
	* @param LogLevel {@see ELogLevel} affects color of log
	* @param FString the message for display
	* @param ELogOutput - All, Output Log or Screen
	*/
	void Log(ELogLevel LogLevel, FString Message, ELogOutput LogOutput);
};
