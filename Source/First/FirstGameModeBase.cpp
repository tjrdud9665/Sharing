// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstGameModeBase.h"
#include "UObject/ConstructorHelpers.h"



AFirstGameModeBase::AFirstGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BluePrint/BP_TopDownPawn"));
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBP(TEXT("/Game/BluePrint/BP_PlayerController"));	
	
	
	DefaultPawnClass = PlayerPawnBPClass.Class;
	PlayerControllerClass = PlayerControllerBP.Class;
}