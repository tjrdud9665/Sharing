// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseCharacter.h"
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



public:
	FORCEINLINE ABaseCharacter* GetFirstPlayer()
	{
		return PlayerCharacter;
	}


//>Client Update

private:
	UFUNCTION()
	void UpdateFollowCamera(float DeltaTime);
	
	

	UFUNCTION(Reliable, Client)
	void Client_UpdatePlayerFrame();





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




};
