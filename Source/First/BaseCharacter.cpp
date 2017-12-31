// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "First.h"
#include "UnitStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FirstPlayerController.h"



// Sets default values
ABaseCharacter::ABaseCharacter(const class FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UnitStatComponent = CreateDefaultSubobject<UUnitStatComponent>(FName("UnitStat"));	
	


	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
			

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	

	

}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);	
	

}

void ABaseCharacter::UpdateCharacterState()
{
	if (!ensure(UnitStatComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("UnitComponent Error"));
		return;
	}

	float SpeedPerCentBuff = UnitStatComponent->GetStatInfo(EUnitStatType::E_ST_MOVESPEED).CurrentValue;



	if (CharacterState.bDashMode)
	{				
		GetCharacterMovement()->MaxWalkSpeed = DASH_SPEED + (DASH_SPEED* SpeedPerCentBuff);
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED + (DASH_SPEED* SpeedPerCentBuff);
	}
}


// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();		
		
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (HasAuthority())
	{
		UpdateCharacterState();
	}		

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


