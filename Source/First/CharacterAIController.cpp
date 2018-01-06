// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAIController.h"
#include "Character/BaseCharacter.h"



FPathFollowingRequestResult ACharacterAIController::MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath /*= nullptr*/)
{
	FPathFollowingRequestResult Result;

	if (PlayerCharacter->IsMovable())
	{
		Result = Super::MoveTo(MoveRequest, OutPath);
	}
	

	return Result;
	
}

void ACharacterAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	PlayerCharacter = Cast<ABaseCharacter>(InPawn);


}
