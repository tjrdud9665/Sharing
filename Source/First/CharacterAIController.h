// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CharacterAIController.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API ACharacterAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class ABaseCharacter* PlayerCharacter;
	
	
	
public:
	virtual FPathFollowingRequestResult MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath = nullptr) override;


	virtual void Possess(APawn* InPawn) override;

};
