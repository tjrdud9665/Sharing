// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDLayOut.h"
#include "Components/UniformGridPanel.h"
#include "PlayerFrame.h"
#include "kismet/GameplayStatics.h"
#include "Components/UniformGridSlot.h"
#include "GameFramework/GameStateBase.h"

bool UHUDLayOut::Initialize()
{
	Super::Initialize();


	return true;

}

void UHUDLayOut::AddPlayerFramePanel(UPlayerFrame* FrameForSlot,int32 Col ,int32 Row)
{

	auto Slot = PlayerFramePanel->AddChildToUniformGrid(FrameForSlot);

	Slot->SetColumn(Col);
	Slot->SetRow(Row);	

}

void UHUDLayOut::ClearPlayerFramePanel()
{
	PlayerFramePanel->ClearChildren();
}
