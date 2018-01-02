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

void UHUDLayOut::AddPlayerFramePanel(UPlayerFrame* FrameForSlot)
{
	PlayerFramePanel->ClearChildren();		

	auto Slot = PlayerFramePanel->AddChildToUniformGrid(FrameForSlot);

	TArray<APlayerState*> PlayerArr = UGameplayStatics::GetGameState(this)->PlayerArray;

	int32 i = 0;
	//for(int32 i = 0 ; i <PlayerArr.Num(); i++)
	//{
	//	Slot->SetRow(i++);
	//}



}
