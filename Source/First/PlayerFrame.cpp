// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerFrame.h"
#include "COmponents/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "FirstPlayerController.h"
#include "UnitStatComponent.h"



UPlayerFrame::UPlayerFrame(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{


}

bool UPlayerFrame::Initialize()
{
	bool Result = Super::Initialize();
	
		
	return Result;
}

