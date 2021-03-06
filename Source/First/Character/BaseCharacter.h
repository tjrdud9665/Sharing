// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SType.h"
#include "BaseCharacter.generated.h"

#define WALK_SPEED 240
#define DASH_SPEED 360







UCLASS()
class FIRST_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter(const class FObjectInitializer& ObjectInitializer);


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	UFUNCTION()
	void UpdateCharacterState();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterState", meta = (AllowPrivateAccess = "true"))
	FCharStateInfo CharacterState;

	UPROPERTY(Replicated)
	uint32 bMovable : 1;

	//TODO : 상속해서 APlayerCharacter에서 처리할것..
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , meta = (AllowPrivateAccess = "true"))
	TArray<struct FSkillInfo> Skills;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	struct FSkillInfo DefaultAttack;

	UPROPERTY()
	struct FSkillInfo CurrentUsingSkill;

	UPROPERTY()
	class AFirstPlayerController* PlayerController;




private:
	//>Components
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , meta = (AllowPrivateAccess = "true"))
	class UUnitStatComponent* UnitStatComponent;


public:
	UFUNCTION()
	void UseSkill(struct FSkillInfo Skill);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UseSkill(struct FSkillInfo Skill);

	void Server_UseSkill_Implementation(struct FSkillInfo Skill);
	bool Server_UseSkill_Validate(struct FSkillInfo Skill);


	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PlayAnim(class UAnimMontage* Anim);
	void Server_PlayAnim_Implementation(class UAnimMontage* Anim);
	bool Server_PlayAnim_Validate(class UAnimMontage* Anim);

	UFUNCTION(NetMulticast, Reliable)
	void MultiCast_PlayAnim(class UAnimMontage* Anim);
	void MultiCast_PlayAnim_Implementation(class UAnimMontage* Anim);





	UFUNCTION()
	void SetMovable(uint32 _NewState);	

	UFUNCTION()
	void SetFirstPlayerController(class AFirstPlayerController* _Controller);





public:
	FORCEINLINE UUnitStatComponent* GetUnitStatComponent()
	{
		return UnitStatComponent;
	}		

	FORCEINLINE const TArray<struct FSkillInfo> GetSkills()
	{
		return Skills;
	}

	FORCEINLINE const FSkillInfo GetDefaultAttack()
	{
		return DefaultAttack;
	}

	FORCEINLINE const FSkillInfo GetCurrentSkill()
	{
		return CurrentUsingSkill;
	}
	
	FORCEINLINE uint32 IsMovable()
	{
		return bMovable;
	}

	FORCEINLINE AFirstPlayerController* GetFirstPlayerController()
	{
		return PlayerController;
	}

};
