// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"



AFirstGameModeBase::AFirstGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BluePrint/BP_TopDownPawn"));
	//static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBP(TEXT("/Game/BluePrint/BP_PlayerController"));	
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUD(TEXT("/Game/BluePrint/BP_FirstHUD"));
	
	
	DefaultPawnClass = PlayerPawnBPClass.Class;
	//PlayerControllerClass = PlayerControllerBP.Class;
	HUDClass = PlayerHUD.Class;

}