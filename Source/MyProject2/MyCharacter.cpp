// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Engine.h"
#include "Math/Color.h"
#include "Kismet/GameplayStatics.h"	


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bDeath = false;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
		Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);



	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &StopJumping);


	PlayerInputComponent->BindAxis("MoveForward", this, &MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &MoveRight);

}


void AMyCharacter::Jump()
{
	ACharacter::Jump();
}


void AMyCharacter::StopJumping()
{
	ACharacter::StopJumping();
}


void AMyCharacter::MoveForward(float Axis)
{
	if (Controller != NULL && Axis != 0.0f && bDeath == true) {
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw ,0);


		FVector Direction = FRotationMatrix(YawRotation).UnixAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}


void AMyCharacter::MoveRight(float Axis)
{
	if (Controller != NULL && Axis != 0.0f && bDeath == true) {
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);


		FVector Direction = FRotationMatrix(YawRotation).UnixAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}