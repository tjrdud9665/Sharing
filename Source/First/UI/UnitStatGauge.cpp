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
	
	auto PlayerCharacter = Controller->GetFirstPlayer();
	SAFE_ACCESS_VOID(PlayerCharacter, L"UnitStatGauage::Setup : PlayerCharacter is NULL");
				
	auto StatComponent = PlayerCharacter->GetUnitStatComponent();
	SAFE_ACCESS_VOID(StatComponent, L"UnitStatGauage::Setup : PlayerCharacter is NULL");


	TArray<EUnitStatType> PlayerStats;
	StatComponent->GetUnitStatMap().GetKeys(OUT PlayerStats);



	GauageInfo.StatType = StatType;
	GauageInfo.Stat = StatComponent->GetStatInfo(StatType);
	FLinearColor* BarColor = StatColors.Find(StatType);
	if (BarColor)
	{

		GauageInfo.BarColor = *BarColor;
		StatBar->SetFillColorAndOpacity(GauageInfo.BarColor);
	}

	if (GauageInfo.Stat.MaxValue)
	{
		StatBar->SetPercent(GauageInfo.Stat.CurrentValue / GauageInfo.Stat.MaxValue);



		FString StatString = FString::Printf(L"%d / %d", (int32)GauageInfo.Stat.CurrentValue, (int32)GauageInfo.Stat.MaxValue);
		StatText->SetText(FText(FText::FromString(StatString)));
	}

	
	
	
}
		
	

