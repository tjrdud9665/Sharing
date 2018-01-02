// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

private:
	//Frame..
	UPROPERTY(meta = (BindWidget))
	class UImage* Icon;

	UPROPERTY(meta = (BindWidget))
	class UImage* BackGround;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;	





	//************************HeatlhBar
	UPROPERTY(BlueprintReadOnly,meta = (BindWidget) , meta = (AllowPrivateAccess = "true"))
	class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget) , meta = (AllowPrivateAccess = "true"))
	class UTextBlock* HealthText;


	//************************ManaBar
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ManaBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ManaText;

	
	
};
