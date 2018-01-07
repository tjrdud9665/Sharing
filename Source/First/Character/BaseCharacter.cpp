// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/BaseCharacter.h"
#include "First.h"
#include "Character/UnitStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TopDown/FirstPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/PlayerFrame.h"
#include "Classes/Animation/AnimMontage.h"
#include "Classes/Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "Macro.h"


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
	DOREPLIFETIME(ABaseCharacter, bMovable);
	

}

float ABaseCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	auto UnitHelthInfo= UnitStatComponent->GetStatInfo(EUnitStatType::E_ST_HEALTH);
	
	


	if (UnitHelthInfo.CurrentValue <= 0.0f)
	{
		return 0.0f;
	}
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.0f)
	{
		UnitHelthInfo.CurrentValue -= ActualDamage;
		UnitStatComponent->SetUnitStat(EUnitStatType::E_ST_HEALTH, UnitHelthInfo.CurrentValue, UnitHelthInfo.MaxValue);

		UE_LOG(LogTemp, Warning, TEXT(" H : %d"), (int32)UnitHelthInfo.CurrentValue);
		
		if (UnitHelthInfo.CurrentValue <= 0)
		{
			// TODO : Die ..
		}
		else
		{

		}
	}

	
	return ActualDamage;

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

void ABaseCharacter::UseSkill(struct FSkillInfo Skill)
{
	CurrentUsingSkill = Skill;
	
	
	
	bMovable = false;	

	Server_PlayAnim(CurrentUsingSkill.Anim);	
	
	if (Role < ROLE_Authority)
	{
		Server_UseSkill(Skill);		
	}
	
	

}

void ABaseCharacter::Server_UseSkill_Implementation(struct FSkillInfo Skill)
{
	UseSkill(Skill);
}

bool ABaseCharacter::Server_UseSkill_Validate(struct FSkillInfo Skill)
{
	return true;
}

void ABaseCharacter::Server_PlayAnim_Implementation(class UAnimMontage* Anim)
{
	MultiCast_PlayAnim(Anim);
}

bool ABaseCharacter::Server_PlayAnim_Validate(class UAnimMontage* Anim)
{
	return true;
}

void ABaseCharacter::MultiCast_PlayAnim_Implementation(class UAnimMontage* Anim)
{
	SAFE_ACCESS_VOID(Anim, L"Anim is NULL");
	auto Mesh = GetMesh();
	SAFE_ACCESS_VOID(Mesh, L"Mesh is NULL");

	auto AnimInst = Mesh->GetAnimInstance();
	

	//TODO : 몽타주가 이전 몽타주/스킬을 캔슬하고 들어가는가? 아닌가?
	if (!AnimInst->Montage_IsPlaying(Anim))
	{	
		PlayAnimMontage(Anim);
		
		
	}
}


void ABaseCharacter::SetMovable(uint32 _NewState)
{
	bMovable = _NewState;
}

void ABaseCharacter::SetFirstPlayerController(class AFirstPlayerController* _Controller)
{
	PlayerController = _Controller;
}



