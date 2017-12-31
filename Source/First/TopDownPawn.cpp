// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownPawn.h"
#include "Camera/CameraComponent.h"
#include "Gameframework/SpringArmComponent.h"
#include "FirstPlayerController.h"



// Sets default values
ATopDownPawn::ATopDownPawn(const class FObjectInitializer& ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FollowCamera =  CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	Scene = CreateDefaultSubobject<USceneComponent>(FName("Scene"));

	RootComponent = Scene;

	CameraBoom->SetupAttachment(Scene);
	FollowCamera->SetupAttachment(CameraBoom);	

}

// Called when the game starts or when spawned
void ATopDownPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<AFirstPlayerController>(GetController());

	if (PlayerController)
	{
		PlayerController->Server_InitPlayer();
	}
}

// Called every frame
void ATopDownPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATopDownPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

const AFirstPlayerController * ATopDownPawn::GetPlayerController()
{
	return PlayerController;
}

void ATopDownPawn::SetPlayerController(AFirstPlayerController* Controller)
{
	PlayerController = Controller;
}

