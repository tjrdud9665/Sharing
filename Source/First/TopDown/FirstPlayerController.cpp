// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDown/FirstPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Character/BaseCharacter.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "CharacterAIController.h"
#include "TopDown/TopDownPawn.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Gameframework/PlayerStart.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/GameStateBase.h"
#include "UI/HUDLayOut.h"
#include "Net/UnrealNetwork.h"
#include "UI/PlayerFrame.h"
#include "Kismet/KismetArrayLibrary.h"
#include "UI/UIFactory.h"
#include "Macro.h"



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
	SAFE_ACCESS_NOLOG(PlayerCharacter);
	if (!PlayerCharacter->IsMovable() )
	{
		Hit = MoveTraceHit;
	}


	if (bMoveToMouseCursor)
	{		//Movement..
		MoveToDestination(Hit);
	}
	else if (bAttackClicked)
	{
		//Attack
		MouseAttack(AttackTraceHit);
		//Server_MouseAttack(AttackTraceHit);
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


	InputComponent->BindAction("Attack", IE_Pressed, this, &AFirstPlayerController::OnAttackPressed);
	
	UE_LOG(LogTemp, Warning, TEXT("Bind Key Input!!"));
}



void AFirstPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	
	
	Client_UpdatePlayerFrame();	
	

}



void AFirstPlayerController::UpdateProgressBar()
{
	if (HUD)
	{
		for (auto Frame : PlayerFrames)
		{
			Frame->UpdateStatBars();
		}
	}
}

void AFirstPlayerController::Client_UpdateProgressBar_Implementation()
{
	UpdateProgressBar();
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
	SAFE_ACCESS_NOLOG(HUD);
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
	
	PlayerFrames.Empty();	
	
	for (int32 i = 0; i < PlayerArr.Num(); i++)
	{		
		auto Frame = UIFactory::CreatePlayerFrame<UPlayerFrame>(PlayerFrameClass.Get(), this);

		PlayerFrames.Add(Frame);	

		HUD->AddPlayerFramePanel(Frame, 0, i);
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

		PlayerCharacter->SetMovable(true);
		PlayerCharacter->SetFirstPlayerController(this);

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
	GetHitResultUnderCursor(ECC_Visibility, true, hit);

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

void AFirstPlayerController::MouseAttack(const FHitResult& Hit)
{
	//TODO : Change Casting Type AttackSubject ABaseCharacter - > AttackableObject...
	auto ClickedActor = Hit.GetActor();

	auto AttackSubject = Cast<ABaseCharacter>(ClickedActor);
		
	
	if (!AttackSubject)
	{
		bAttackClicked = false;
		return;
	}

	LastAttackSubject = AttackSubject;

	SAFE_ACCESS_NOLOG(PlayerCharacter);

	if (AttackSubject == PlayerCharacter)
		return;
		

	//Get Dist Character and AttackSubject..
	FVector Diff = (PlayerCharacter->GetActorLocation() - AttackSubject->GetActorLocation());
	float Distance = Diff.Size();
	FVector Direction = Diff.GetSafeNormal();

	//So Far
	if (PlayerCharacter->GetDefaultAttack().Distance < Distance)
	{
		//Go to Actor  
		MoveToActor(Hit);				
	}
	else
	{
		//TODO : Change Direction to AttackSubject with Lerp..
		float Deltatime = UGameplayStatics::GetWorldDeltaSeconds(this);
				
		//PlayerChFaracter->GetActorRotation()

		auto LookRot = UKismetMathLibrary::FindLookAtRotation(PlayerCharacter->GetActorLocation(), AttackSubject->GetActorLocation());
		
		auto CurrentRot = PlayerCharacter->GetActorRotation();

		auto TargetRot = CurrentRot;

		TargetRot.Yaw = LookRot.Yaw;

		//auto LerpedRotation= UKismetMathLibrary::RInterpTo(CurrentRot, TargetRot ,Deltatime, 12.0f);		
		
		PlayerCharacter->SetActorRotation(TargetRot);

		PlayerCharacter->UseSkill(PlayerCharacter->GetDefaultAttack());		
		bAttackClicked = false;


	}
	
	

	if (Role < ROLE_Authority)
	{
		Server_MouseAttack(Hit);

	}
}

void AFirstPlayerController::Server_MouseAttack_Implementation(FHitResult& Hit)
{
	MouseAttack(Hit);
}

bool AFirstPlayerController::Server_MouseAttack_Validate(FHitResult& Hit)
{
	return true;
}

void AFirstPlayerController::MoveToActor(const FHitResult& Hit)
{
	SAFE_ACCESS_NOLOG(PlayerCharacter);

	if (Hit.bBlockingHit)
	{

		if (AiController)
		{
			SAFE_ACCESS_NOLOG(Hit.GetActor());
			float Dist = (-1.0f);
			if (LastAttackSubject)
			{
				Dist = (PlayerCharacter->GetActorLocation() - LastAttackSubject->GetActorLocation()).Size()/2;
			}

			AiController->MoveToActor(Hit.GetActor(),PlayerCharacter->GetCurrentSkill().Distance/2);
		}
	}

	if (Role < ROLE_Authority)
	{
		Server_MoveToActor(Hit);

	}

}

void AFirstPlayerController::Server_MoveToActor_Implementation(FHitResult& Hit)
{
	MoveToActor(Hit);
}

bool AFirstPlayerController::Server_MoveToActor_Validate(FHitResult& Hit)
{
	return true;
}

void AFirstPlayerController::OnMovetoCursorPressed()
{
	bMoveToMouseCursor = true;	
	bAttackClicked = false;

	
	GetHitResult(MoveTraceHit);


	//if it is  client
	if (Role < ROLE_Authority)
	{
		//Request the Server whit RPC..
		Server_OnMovetoCursorPressed();

	}

}

void AFirstPlayerController::OnAttackPressed()
{
	bAttackClicked = true;	
	
	GetHitResult(AttackTraceHit);
	
	
	if (Role < ROLE_Authority)
	{
		//Request the Server whit RPC..
		Server_OnAttackPressed();

	}

}



void AFirstPlayerController::Server_OnAttackPressed_Implementation()
{
	bAttackClicked = true;
	
	OnAttackPressed();
}

bool AFirstPlayerController::Server_OnAttackPressed_Validate()
{
	return true;
}

void AFirstPlayerController::Server_OnMovetoCursorPressed_Implementation()
{
	bMoveToMouseCursor = true;
	bAttackClicked = false;
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
