// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Character/BaseCharacter.h"
#include "FirstPlayerController.generated.h"



/**
 * 
 */
UCLASS()
class FIRST_API AFirstPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFirstPlayerController(const class FObjectInitializer& ObjectInitializer);
	

	virtual void PlayerTick(float DeltaTime) override;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

protected:
	virtual void SetupInputComponent() override;


	virtual void BeginPlay() override;

private:


	UPROPERTY()
	uint32 bMoveToMouseCursor : 1;

	UPROPERTY()
	uint32 bAttackClicked : 1;

	UPROPERTY()
	class AActor* LastAttackSubject;

	UPROPERTY()
	FHitResult AttackTraceHit;

	UPROPERTY()
	FHitResult MoveTraceHit;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CamFollowSpeed" , meta = (AllowPrivateAccess = "true"))
	float CamearaSpeed = 12.0f;

	//Notify Other Client the Valiable..
	//>UPROPERTY(Transient, Replicated)

	UPROPERTY()
	class ACharacterAIController* AiController;

	UPROPERTY(Replicated)
	class ATopDownPawn* TopDownPawn;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseCharacter> RespawnCharacterClass;

	UPROPERTY(BlueprintReadOnly,Replicated , Category = "Character" , meta = (AllowPrivateAccess = "true"))
	class ABaseCharacter* PlayerCharacter;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UHUDLayOut> HUDLayOut;

	UPROPERTY(EditDefaultsOnly, Category = "Frame", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPlayerFrame> PlayerFrameClass;



	UPROPERTY()
	class UHUDLayOut* HUD;

	UPROPERTY()
	TArray<UPlayerFrame*> PlayerFrames;



public:
	FORCEINLINE ABaseCharacter* GetFirstPlayer()
	{
		return PlayerCharacter;
	}

	FORCEINLINE TArray<UPlayerFrame*> GetPlayerFrames()
	{
		return PlayerFrames;
	}


//>Client Update
public:
	UFUNCTION(Reliable, Client)
	void Client_UpdatePlayerFrame();

	UFUNCTION()
	void UpdateProgressBar();

	UFUNCTION(Reliable, Client)
	void Client_UpdateProgressBar();	
	void Client_UpdateProgressBar_Implementation();
	




private:
	UFUNCTION()
	void UpdateFollowCamera(float DeltaTime);
	UFUNCTION()
	void UpdatePlayerFrame();
	
	






//> Server Update..
public:

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_InitPlayer();

	void Server_InitPlayer_Implementation();

	bool Server_InitPlayer_Validate();

private:
	UFUNCTION()
	void Respawn();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Respawn();

	void Server_Respawn_Implementation();

	bool Server_Respawn_Validate();




	//> For Movement
	UFUNCTION()
	void GetHitResult( FHitResult& hit);


	UFUNCTION(Server, Reliable, WithValidation)
	void Server_GetHitResult(const FHitResult& hit);
	
	void Server_GetHitResult_Implementation( FHitResult& hit);

	bool Server_GetHitResult_Validate( FHitResult& hit);

	
	UFUNCTION()
	void MoveToDestination(const FHitResult& Hit);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveToDestination(const FHitResult& Hit);

	void Server_MoveToDestination_Implementation(FHitResult& Hit);

	bool Server_MoveToDestination_Validate(FHitResult& Hit);

	UFUNCTION()
	void MouseAttack(const FHitResult& Hit);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MouseAttack(const FHitResult& Hit);

	void Server_MouseAttack_Implementation(FHitResult& Hit);

	bool Server_MouseAttack_Validate(FHitResult& Hit);

	


	UFUNCTION()
	void MoveToActor(const FHitResult& Hit);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveToActor(const FHitResult& Hit);

	void Server_MoveToActor_Implementation(FHitResult& Hit);
	
	bool Server_MoveToActor_Validate(FHitResult& Hit);




	UFUNCTION()
	void OnMovetoCursorPressed();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_OnMovetoCursorPressed();

	void Server_OnMovetoCursorPressed_Implementation();

	bool Server_OnMovetoCursorPressed_Validate();



	UFUNCTION()
	void OnMovetoCursorReleased();


	UFUNCTION(Server, Reliable, WithValidation)
	void Server_OnMovetoCursorReleased();

	void Server_OnMovetoCursorReleased_Implementation();

	bool Server_OnMovetoCursorReleased_Validate();


	UFUNCTION()
	void OnAttackPressed();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_OnAttackPressed();

	void Server_OnAttackPressed_Implementation();

	bool Server_OnAttackPressed_Validate();

	






};
