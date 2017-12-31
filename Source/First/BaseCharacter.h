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


private:
	//>Components
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , meta = (AllowPrivateAccess = "true"))
	class UUnitStatComponent* UnitStatComponent;



public:
	FORCEINLINE UUnitStatComponent* GetUnitStatComponent()
	{
		return UnitStatComponent;
	}	
	

public:
};
