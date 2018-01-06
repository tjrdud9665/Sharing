// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */


#define SAFE_ACCESS_VOID(P , Message)  if(!P){UE_LOG(LogTemp ,Error, TEXT("%s"),Message) return;}
#define SAFE_ACCESS(P, Message) if(!P){UE_LOG(LogTemp ,Error, TEXT("%s"),Message) return 0;}
#define SAFE_ACCESS_NOLOG(P)  if(!P){return;}
