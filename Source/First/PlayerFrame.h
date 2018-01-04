// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SType.h"
#include "PlayerFrame.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UPlayerFrame : public UUserWidget
{
	GENERATED_BODY()

public:
	UPlayerFrame(const FObjectInitializer& ObjectInitializer);



	virtual bool Initialize() override;

	UFUNCTION()
	void SetupPlayerController(class AFirstPlayerController* _Controller);


private:
	//Frame..
	UPROPERTY(meta = (BindWidget))
	class UImage* Icon;

	UPROPERTY(meta = (BindWidget))
	class UImage* BackGround;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;	
	
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* StatGauageContain;

	UPROPERTY(EditDefaultsOnly, Category = "BarColor", meta = (AllowPrivateAccess = "true"))
	TMap<EUnitStatType, FLinearColor> StatColors;


private:
	UPROPERTY()
	class AFirstPlayerController* Controller;

	UPROPERTY()
	FStatGaugeInfo GaugeInfo;


	UFUNCTION()
	void SetStatBarGauageInfo(EUnitStatType _StatType);

	
};
