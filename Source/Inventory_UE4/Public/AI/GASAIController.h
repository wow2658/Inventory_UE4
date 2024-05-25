// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GASAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 *
 */
UCLASS()
class INVENTORY_UE4_API AGASAIController : public AAIController
{
	GENERATED_BODY()

public:
	AGASAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
