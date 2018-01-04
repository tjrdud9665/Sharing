// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SType.h"
#include "UnitStatGauge.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UUnitStatGauge : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget) , meta = (AllowPrivateAccess = "true"))
	class UProgressBar* StatBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	class UTextBlock* StatText;


private:
	UPROPERTY()
	FStatGaugeInfo GauageInfo;



	
	
	
};
