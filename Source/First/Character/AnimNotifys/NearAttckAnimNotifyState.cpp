// Fill out your copyright notice in the Description page of Project Settings.

#include "NearAttckAnimNotifyState.h"
#include "Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Macro.h"


void UNearAttckAnimNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	if (!MeshComp)
		return;


	if (!(MeshComp->GetOwnerRole() < ROLE_Authority)) {
		OwnerCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());

		OwnerCharacter->GetWorldTimerManager().SetTimer(HitTraceTimer ,this, &UNearAttckAnimNotifyState::GenerateLineTrace, 0.1f, true);
	}


}

void UNearAttckAnimNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	if (!MeshComp)	
		return;

	
	//Run Only Server..
	if (!(MeshComp->GetOwnerRole() < ROLE_Authority))
	{
		if (OwnerCharacter->GetWorldTimerManager().TimerExists(HitTraceTimer))
		{
			DamagedActors.Empty();
			OwnerCharacter->GetWorldTimerManager().ClearTimer(HitTraceTimer);
		}
	}
		

}

void UNearAttckAnimNotifyState::GenerateLineTrace()
{
	SAFE_ACCESS_VOID(OwnerCharacter, L"NOTIFY : OWnerChar is NULL");
	//TODO : Get Melle Attack Distance form OwnerCharacter or Character's Component..
	
	FVector EndPos = OwnerCharacter->GetActorLocation() + OwnerCharacter->GetActorForwardVector() * OwnerCharacter->GetCurrentSkill().Distance;

	TArray<TEnumAsByte<EObjectTypeQuery>> QueryObj;
	QueryObj.Add(EObjectTypeQuery::ObjectTypeQuery3);
	QueryObj.Add(EObjectTypeQuery::ObjectTypeQuery1);
	QueryObj.Add(EObjectTypeQuery::ObjectTypeQuery2);

	TArray<AActor*> IgnoreList;
	//TODO : Add to Ignore Object.. Like Party , Team etc...

	
	TArray<FHitResult> HitReults;

	auto Result = UKismetSystemLibrary::CapsuleTraceMultiForObjects(OwnerCharacter, OwnerCharacter->GetActorLocation(), EndPos, 34,88, QueryObj, true, IgnoreList, EDrawDebugTrace::Persistent, HitReults, true);
	if (Result)
	{
		for (auto HIts : HitReults)
		{
			if (!DamagedActors.Contains(HIts.GetActor()))
			{
				HIts.Actor->TakeDamage(30, FDamageEvent(), OwnerCharacter->GetController(), OwnerCharacter);
				DamagedActors.Add(HIts.GetActor());
				//UGameplayStatics::ApplyDamage()
			}


		}
	}
}
