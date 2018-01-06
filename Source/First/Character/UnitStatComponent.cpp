// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/UnitStatComponent.h"
#include "Character/BaseCharacter.h"

// Sets default values for this component's properties
UUnitStatComponent::UUnitStatComponent(const class FObjectInitializer& ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	// ...
}


FUnitStatInfo UUnitStatComponent::GetStatInfo(EUnitStatType StatType)
{
	return *UnitStatMap.Find(StatType);	
}

void UUnitStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);	

}

void UUnitStatComponent::SetUnitStat(EUnitStatType StatType, float CurrntValue, float MaxValue)
{
	UnitStatMap[StatType].MaxValue = MaxValue;

	//>Clamping Unit's Stat..
	UnitStatMap[StatType].CurrentValue = FMath::Clamp<float>(CurrntValue , 0 , MaxValue);	

	

	if(GetOwner()->Role < ROLE_Authority)
	{
		Server_SetUnitStat(StatType, CurrntValue, MaxValue);
	}

}

void UUnitStatComponent::Server_SetUnitStat_Implementation(EUnitStatType StatType, float CurrntValue, float MaxValue)
{
	SetUnitStat(StatType, CurrntValue, MaxValue);
	
}

bool UUnitStatComponent::Server_SetUnitStat_Validate(EUnitStatType StatType, float CurrntValue, float MaxValue)
{
	return true;
}

void UUnitStatComponent::InitializeStatInfo()
{
	
	for (auto& Elem : UnitStatMap)
	{
		SetUnitStat(Elem.Key, Elem.Value.MaxValue, Elem.Value.MaxValue);
	}

}

void UUnitStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	UE_LOG(LogTemp, Warning, TEXT("UnitStatComponent Ready! "));
	
	InitializeStatInfo();


}

// Called when the game starts
void UUnitStatComponent::BeginPlay()
{
	Super::BeginPlay();
	if(UnitStatMap.Find(EUnitStatType::E_ST_HEALTH))
		UE_LOG(LogTemp, Warning, TEXT("Health : %lf "), UnitStatMap[EUnitStatType::E_ST_HEALTH].CurrentValue);

	// ...
	
}


// Called every frame
void UUnitStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...

}

