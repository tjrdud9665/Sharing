// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerFrame.h"
#include "COmponents/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "FirstPlayerController.h"
#include "UnitStatComponent.h"
#include "UnitStatGauge.h"
#include "FirstPlayerController.h"
#include "Macro.h"
#include "UIFactory.h"
#include "Components/VerticalBox.h"

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

void UPlayerFrame::InitializeStatBars()
{
	SAFE_ACCESS_VOID(UnitGauageBarClass, L"AddStatBar : GauageClass is NULL");
	//TODO : Creat BarWidget and Add PlayerFrame..
	SAFE_ACCESS_VOID(Controller, L"AddStatBar :Controller is NULL");



	ABaseCharacter* Character = Controller->GetFirstPlayer();
	SAFE_ACCESS_VOID(Character, L"AddStatBar : Character is NULL");

	UUnitStatComponent* StatComponent = Character->GetUnitStatComponent();
	SAFE_ACCESS_VOID(StatComponent, L"AddStatBar : StatComponent is NULL");




	auto Stats = StatComponent->GetUnitStatMap();
	TArray<EUnitStatType> HasStats;
	Stats.GetKeys(HasStats);

	AddStatBar(HasStats);
}

void UPlayerFrame::AddStatBar(TArray<EUnitStatType> Stats)
{
	StatGauages.Empty();


	for (auto Stat : Stats)
	{		
		switch (Stat)
		{
		case EUnitStatType::E_ST_ENERGY:
		case EUnitStatType::E_ST_MANA:
		case EUnitStatType::E_ST_HEALTH:
		case EUnitStatType::E_ST_RAGE:
		{
			UUnitStatGauge* Gauage = UIFactory::CreateStatGauage<UUnitStatGauge>(UnitGauageBarClass.Get(), Stat, Controller);
			StatGauages.Add(Gauage);
			StatGauageContain->AddChildToVerticalBox(Gauage);
		}
			break;
		}

	}
}
