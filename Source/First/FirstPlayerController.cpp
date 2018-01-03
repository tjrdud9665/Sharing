// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "BaseCharacter.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "CharacterAIController.h"
#include "TopDownPawn.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Gameframework/PlayerStart.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/GameStateBase.h"
#include "HUDLayOut.h"
#include "Net/UnrealNetwork.h"
#include "PlayerFrame.h"




AFirstPlayerController::AFirstPlayerController(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bReplicates = true;
	bShowMouseCursor = true;
}

void AFirstPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateFollowCamera(DeltaTime);

	//> getHitResult..
	FHitResult Hit;
	GetHitResult(Hit);

	if (bMoveToMouseCursor)
	{
		//Movement..
		MoveToDestination(Hit);

	}

}

void AFirstPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFirstPlayerController, TopDownPawn);
	DOREPLIFETIME(AFirstPlayerController, PlayerCharacter);


}

void AFirstPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MovetoCursor", IE_Pressed, this, &AFirstPlayerController::OnMovetoCursorPressed);
	InputComponent->BindAction("MovetoCursor", IE_Released, this, &AFirstPlayerController::OnMovetoCursorReleased);

	UE_LOG(LogTemp, Warning, TEXT("Bind Key Input!!"));
}



void AFirstPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	
	
	Client_UpdatePlayerFrame();	
	

}

void AFirstPlayerController::UpdateFollowCamera(float DeltaTime)
{
	if (!TopDownPawn)
		return;
	if (!PlayerCharacter)
		return;

	auto PlayerLocation = PlayerCharacter->GetActorLocation();
	auto TopDownPawnLoaction = TopDownPawn->GetActorLocation();
	
	//Lerp..
	auto LerpedLocation = UKismetMathLibrary::VInterpTo(TopDownPawnLoaction, PlayerLocation, DeltaTime, CamearaSpeed);


	TopDownPawn->SetActorLocation(LerpedLocation);

	//UKismetMathLibrary::VInterpTo()

}

void AFirstPlayerController::UpdatePlayerFrame()
{
	if (!HUD)
	{
		HUD = CreateWidget<UHUDLayOut>(this, HUDLayOut.Get());
	}

	if (!HUD->IsInViewport())
	{
		HUD->AddToViewport();
	}

	auto GameState = UGameplayStatics::GetGameState(this);
	TArray<APlayerState*> PlayerArr;
	if (GameState)
	{
		PlayerArr = GameState->PlayerArray;
	}	

	HUD->ClearPlayerFramePanel();
	UE_LOG(LogTemp, Warning, TEXT("%d "), PlayerArr.Num());
	for (int32 i = 0; i < PlayerArr.Num(); i++)
	{		
		UPlayerFrame* Slot = CreateWidget<UPlayerFrame>(this, PlayerFrameClass.Get());
		HUD->AddPlayerFramePanel(Slot, 0, i);
	}

}

void AFirstPlayerController::Client_UpdatePlayerFrame_Implementation()
{

	UpdatePlayerFrame();
	
}

void AFirstPlayerController::Server_InitPlayer_Implementation()
{
	APawn* ControlledPawn = GetPawn();

	if (!ensure(ControlledPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("Respawn Falied.. : Miss ControlledPawn"));

	}

	TopDownPawn = Cast<ATopDownPawn>(ControlledPawn);

	if (!ensure(TopDownPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("Respawn Falied.. : Casting FAild"));
		return;
	}

	//>Call Server REspawn..
	Server_Respawn();

}

bool AFirstPlayerController::Server_InitPlayer_Validate()
{
	return true;
}

void AFirstPlayerController::Respawn()
{


	TArray<AActor*> StartArray;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), StartArray);
	int32 idx  = UKismetMathLibrary::RandomIntegerInRange(0, StartArray.Num()-1);
	if (!StartArray.IsValidIndex(idx))
	{			
		return;
	}
	
	

	
	FVector RespawnLocation = StartArray[idx]->GetActorLocation();

	if (!ensure(TopDownPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("Respawn Falied.."));
		return;
	}
	//
	TopDownPawn->SetActorLocation(RespawnLocation);

	if (RespawnCharacterClass)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		PlayerCharacter = GetWorld()->SpawnActor<ABaseCharacter>(RespawnCharacterClass, TopDownPawn->GetActorTransform(), SpawnInfo);

		AiController = GetWorld()->SpawnActor<ACharacterAIController>(ACharacterAIController::StaticClass(), TopDownPawn->GetActorTransform());

		AiController->Possess(PlayerCharacter);
		Possess(TopDownPawn);
	}


}

void AFirstPlayerController::Server_Respawn_Implementation()
{
	Respawn();
}

bool AFirstPlayerController::Server_Respawn_Validate()
{
	return true;
}

void AFirstPlayerController::GetHitResult(FHitResult& hit)
{
	GetHitResultUnderCursor(ECC_Visibility, false, hit);

	if (Role < ROLE_Authority)
	{
		Server_GetHitResult(hit);
	}
}



void AFirstPlayerController::Server_GetHitResult_Implementation(FHitResult& hit)
{
	GetHitResult(hit);
}



bool AFirstPlayerController::Server_GetHitResult_Validate(FHitResult& hit)
{
	return true;
}

void AFirstPlayerController::MoveToDestination(const FHitResult& Hit)
{
	if (Hit.bBlockingHit)
	{

		if (AiController)
		{
			AiController->MoveToLocation(Hit.ImpactPoint);
		}
	}

	if (Role < ROLE_Authority)
	{
		Server_MoveToDestination(Hit);

	}
}





void AFirstPlayerController::Server_MoveToDestination_Implementation(FHitResult& Hit)
{
	MoveToDestination(Hit);
}

bool AFirstPlayerController::Server_MoveToDestination_Validate(FHitResult& Hit)
{
	return true;
}

void AFirstPlayerController::OnMovetoCursorPressed()
{
	bMoveToMouseCursor = true;	

	//if it is  client
	if (Role < ROLE_Authority)
	{
		//Request the Server whit RPC..
		Server_OnMovetoCursorPressed();

	}

}

void AFirstPlayerController::Server_OnMovetoCursorPressed_Implementation()
{
	bMoveToMouseCursor = true;
	OnMovetoCursorPressed();
}

bool AFirstPlayerController::Server_OnMovetoCursorPressed_Validate()
{
	return true;
}

void AFirstPlayerController::OnMovetoCursorReleased()
{
	bMoveToMouseCursor = false;

	

	if (Role < ROLE_Authority)
	{
		Server_OnMovetoCursorReleased();
	}
}

void AFirstPlayerController::Server_OnMovetoCursorReleased_Implementation()
{
	OnMovetoCursorReleased();
}

bool AFirstPlayerController::Server_OnMovetoCursorReleased_Validate()
{
	return true;
}
