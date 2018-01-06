// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SType.h"
#include "UnitStatComponent.generated.h"


//This Component Managing Unit Stat Info  (like Taking a Damage ..)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRST_API UUnitStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUnitStatComponent(const class FObjectInitializer& ObjectInitializer);


protected:
	UPROPERTY( EditDefaultsOnly, Category = "UnitUseStat" , meta = (AllowPrivateAccess = "true"))
	TMap<EUnitStatType, FUnitStatInfo> UnitStatMap;


public:
	UFUNCTION(BlueprintCallable,BlueprintPure )
	FUnitStatInfo GetStatInfo(EUnitStatType StatType);



	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UFUNCTION(BlueprintCallable)
	void SetUnitStat(EUnitStatType StatType, float CurrntValue, float MaxValue);


	UFUNCTION(Server, Reliable , WithValidation)
	void Server_SetUnitStat(EUnitStatType StatType, float CurrntValue, float MaxValue);

	void Server_SetUnitStat_Implementation(EUnitStatType StatType, float CurrntValue, float MaxValue);

	bool Server_SetUnitStat_Validate(EUnitStatType StatType, float CurrntValue, float MaxValue);




	UFUNCTION()
	void InitializeStatInfo();		


	virtual void InitializeComponent() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		

	FORCEINLINE const TMap<EUnitStatType, FUnitStatInfo> GetUnitStatMap()
	{
		return UnitStatMap;

	}
	
};
