// Fill out your copyright notice in the Description page of Project Settings.
#pragma once


#include "SType.generated.h"


//UENUM()
//enum class ENumSample : uint8
//{
//	
//	Sample_One,
//	
//	Sample_Two,
//		
//	Sample_Three,
//};
//
//USTRUCT()
//struct FStructSample
//{
//	GENERATED_USTRUCT_BODY()
//		

//	UPROPERTY()
//		float SampleFloat;
//};


UENUM()
enum class EUnitStatType : uint8
{
	E_ST_NULL,

	E_ST_HEALTH,

	E_ST_MANA,

	E_ST_MOVESPEED,			//> Use Multiply with Movement Speed with Percentage..
	

	MAX
};

USTRUCT(BlueprintType)
struct FUnitStatInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxValue;

	UPROPERTY(BlueprintReadOnly)
	float CurrentValue;
};

USTRUCT(BlueprintType)
struct FCharStateInfo
{
	GENERATED_USTRUCT_BODY()	
	


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bAttackMode = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDashMode =false;

};


