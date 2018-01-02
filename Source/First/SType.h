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

UENUM()
enum class ESkillType : uint8
{
	E_ST_Active,

	E_ST_Passive,

	MAX
};


USTRUCT(BlueprintType)
struct FSkillInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString SkillName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 SkillLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ESkillType SkillType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* Anim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture* SkillIcon;



};


USTRUCT()
struct FTakeHitInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		float ActualDamage;

	UPROPERTY()
		UClass* DamageTypeClass;

//	UPROPERTY()
//		TWeakObjectPtr<class ABaseCharacter> PawnInstigator;
//
//	UPROPERTY()
//		TWeakObjectPtr<class AActor> DamageCauser;
//
//	UPROPERTY()
//		uint8 DamageEventClassID;
//
//	UPROPERTY()
//		bool bKilled;
//
//private:
//	UPROPERTY()
//		FDamageEvent GeneralDamageEvent;
//
//	UPROPERTY()
//		FPointDamageEvent PointDamageEvent;
//
//	UPROPERTY()
//		FRadialDamageEvent RadialDamageEvent;
//
//
//
//public:
//	FTakeHitInfo()
//		: ActualDamage(0),
//		DamageTypeClass(nullptr),
//		PawnInstigator(nullptr),
//		DamageCauser(nullptr),
//		DamageEventClassID(0),
//		bKilled(false)
//
//	{}
//
//	FDamageEvent& GetDamageEvent()
//	{
//		switch (DamageEventClassID)
//		{
//		case FPointDamageEvent::ClassID:
//			if (PointDamageEvent.DamageTypeClass == nullptr)
//			{
//				PointDamageEvent.DamageTypeClass = DamageTypeClass ? DamageTypeClass : UDamageType::StaticClass();
//			}
//			return PointDamageEvent;
//
//		case FRadialDamageEvent::ClassID:
//			if (RadialDamageEvent.DamageTypeClass == nullptr)
//			{
//				RadialDamageEvent.DamageTypeClass = DamageTypeClass ? DamageTypeClass : UDamageType::StaticClass();
//			}
//			return RadialDamageEvent;
//
//		default:
//			if (GeneralDamageEvent.DamageTypeClass == nullptr)
//			{
//				GeneralDamageEvent.DamageTypeClass = DamageTypeClass ? DamageTypeClass : UDamageType::StaticClass();
//			}
//			return GeneralDamageEvent;
//		}
//	}
//
//
//	void SetDamageEvent(const FDamageEvent& DamageEvent)
//	{
//		DamageEventClassID = DamageEvent.GetTypeID();
//		switch (DamageEventClassID)
//		{
//		case FPointDamageEvent::ClassID:
//			PointDamageEvent = *((FPointDamageEvent const*)(&DamageEvent));
//			break;
//		case FRadialDamageEvent::ClassID:
//			RadialDamageEvent = *((FRadialDamageEvent const*)(&DamageEvent));
//			break;
//		default:
//			GeneralDamageEvent = DamageEvent;
//		}
//	}
//
//

};