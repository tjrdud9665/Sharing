// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SType.h"

/**
 * 
 */

class FIRST_API UIFactory
{
public:	
	template<typename T>
	static T* CreateStatGauage(UClass* Class, EUnitStatType StatType, class AFirstPlayerController* Controller);

	template<typename T>
	static T* CreatePlayerFrame(UClass* Class, class AFirstPlayerController* Controller);

	
};

template<typename T>
T* UIFactory::CreateStatGauage(UClass* Class , EUnitStatType StatType , class AFirstPlayerController* Controller)
{
	T* Gauage = CreateWidget<T>(Controller, Class);
	
	Gauage->Setup(StatType, Controller);	
	return Gauage;

}

template<typename T>
T* UIFactory::CreatePlayerFrame(UClass* Class, class AFirstPlayerController* Controller)
{
	T* Frame = CreateWidget<T>(Controller, Class);

	Frame->SetupPlayerController(Controller);
	Frame->InitializeStatBars();


	return Frame;
}

