// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/UnitStatGauge.h"
#include "Character/UnitStatComponent.h"
#include "TopDown/FirstPlayerController.h"
#include "Macro.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


UUnitStatGauge::UUnitStatGauge(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UUnitStatGauge::Setup(EUnitStatType StatType, AFirstPlayerController* PlayerController)
{
	Controller = PlayerController;
	SAFE_ACCESS_VOID(Controller,L"UnitStatGauage::Setup : Controller is NULL");
	
	PlayerCharacter = Controller->GetFirstPlayer();
	SAFE_ACCESS_VOID(PlayerCharacter, L"UnitStatGauage::Setup : PlayerCharacter is NULL");
				
	auto StatComponent = PlayerCharacter->GetUnitStatComponent();
	SAFE_ACCESS_VOID(StatComponent, L"UnitStatGauage::Setup : PlayerCharacter is NULL");


	TArray<EUnitStatType> PlayerStats;
	StatComponent->GetUnitStatMap().GetKeys(OUT PlayerStats);

	BarStatType = StatType;

	
	auto UnitStat = StatComponent->GetStatInfo(StatType);
	FLinearColor* BarColor = StatColors.Find(StatType);
	if (BarColor)
	{

		
		StatBar->SetFillColorAndOpacity(*BarColor);
	}

	if (UnitStat.MaxValue)
	{
		StatBar->SetPercent(UnitStat.CurrentValue / UnitStat.MaxValue);



		FString StatString = FString::Printf(L"%d / %d", (int32)UnitStat.CurrentValue, (int32)UnitStat.MaxValue);
		StatText->SetText(FText(FText::FromString(StatString)));
	}
	
	
	
	
}
		
	
void UUnitStatGauge::UpdateStatBar()
{
	SAFE_ACCESS_VOID(Controller, L"UnitStatGauage::Setup : Controller is NULL");	
	SAFE_ACCESS_VOID(PlayerCharacter, L"UnitStatGauage::Setup : PlayerCharacter is NULL");	
	SAFE_ACCESS_VOID(StatComponent, L"UnitStatGauage::Setup : StatComponent is NULL");	
	
	auto NewStatInfo = StatComponent->GetStatInfo(BarStatType);

	

	//Guard Zero Div..
	if (NewStatInfo.MaxValue)
	{
		StatBar->SetPercent(NewStatInfo.CurrentValue / NewStatInfo.MaxValue);

		FString StatString = FString::Printf(L"%d / %d", (int32)NewStatInfo.CurrentValue, (int32)NewStatInfo.MaxValue);
		StatText->SetText(FText(FText::FromString(StatString)));
	}
	




	
}

