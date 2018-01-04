// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerFrame.h"
#include "COmponents/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "FirstPlayerController.h"
#include "UnitStatComponent.h"
#include "FirstPlayerController.h"



UPlayerFrame::UPlayerFrame(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{


}

bool UPlayerFrame::Initialize()
{
	bool Result = Super::Initialize();


	return Result;
}

void UPlayerFrame::SetupPlayerController(class AFirstPlayerController* _Controller)
{
	Controller = _Controller;

	//TODO : GetStatInfo, And Create ProgressBar (like Health , Mana, etc)..


}

void UPlayerFrame::SetStatBarGauageInfo(EUnitStatType _StatType)
{
	if (Controller)
	{
		auto PlayerCharacter = Controller->GetFirstPlayer();

		if (PlayerCharacter)
		{
			auto StatComponent = PlayerCharacter->GetUnitStatComponent();

			if (StatComponent)
			{
				TArray<EUnitStatType> PlayerStats;
				StatComponent->GetUnitStatMap().GetKeys(OUT PlayerStats);


				for (EUnitStatType StatType : PlayerStats)
				{
					//Make Function Setup GauageInfo..
					GaugeInfo.StatType = _StatType;
					GaugeInfo.Stat = StatComponent->GetStatInfo(StatType);
					FLinearColor* BarColor = StatColors.Find(StatType);
					if (BarColor)
					{
						GaugeInfo.BarColor = *BarColor;
					}					


				}
			}
		}
	}
}

