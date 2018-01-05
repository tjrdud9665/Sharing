// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDLayOut.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UHUDLayOut : public UUserWidget
{
	GENERATED_BODY()
	

private:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* PlayerFramePanel;

		
public:
	virtual bool Initialize() override;

public:
	UFUNCTION()
	void AddPlayerFramePanel(class UPlayerFrame* FrameForSlot, int32 Col, int32 Row);
	UFUNCTION()
	void ClearPlayerFramePanel();


};
