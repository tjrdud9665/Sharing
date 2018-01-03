// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"
#include "FirstPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


AFirstGameModeBase::AFirstGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BluePrint/BP_TopDownPawn"));
	//static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBP(TEXT("/Game/BluePrint/BP_PlayerController"));	
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUD(TEXT("/Game/BluePrint/BP_FirstHUD"));

	static ConstructorHelpers::FClassFinder<AFirstPlayerController> ControllerClass_BP(TEXT("/Game/BluePrint/BP_PlayerController"));

	
	
	
	DefaultPawnClass = PlayerPawnBPClass.Class;
	//PlayerControllerClass = PlayerControllerBP.Class;
	HUDClass = PlayerHUD.Class;

	ControllerClass = ControllerClass_BP.Class;

}

void AFirstGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);	
	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFirstGameModeBase::OnPlayerLogin, 2.f, false);

	//OnPlayerLogin();		


}

//void AFirstGameModeBase::OnPlayerLogin()
//{
//	//TODO : Find All Controller
//	//		Call UpdatePlayerFrame For UI
//	TSubclassOf<AFirstPlayerController> ControllerClass;
//	TArray<AActor*> Controllers;
//
//
//
//	UGameplayStatics::GetAllActorsOfClass(this, ControllerClass, Controllers);
//	UE_LOG(LogTemp, Warning, TEXT("Controller : %d"), Controllers.Num());
//
//
//	
//	for (AActor* Controller : Controllers)
//	{
//
//		auto Con = Cast<AFirstPlayerController>(Controller);
//		if (Con)
//		{
//			Con->Client_UpdatePlayerFrame();
//		}
//
//	}
//}

void AFirstGameModeBase::OnPlayerLogin_Implementation()
{
	//TODO : Find All Controller
	//		Call UpdatePlayerFrame For UI	
	TArray<AActor*> Controllers;



	UGameplayStatics::GetAllActorsOfClass(this, ControllerClass, Controllers);
	UE_LOG(LogTemp, Warning, TEXT("Controller : %d"), Controllers.Num());



	for (AActor* Controller : Controllers)
	{

		auto Con = Cast<AFirstPlayerController>(Controller);
		if (Con)
		{
			Con->Client_UpdatePlayerFrame();
		}

	}
}

//bool AFirstGameModeBase::OnPlayerLogin_Validate()
//{
//	return true;
//}
