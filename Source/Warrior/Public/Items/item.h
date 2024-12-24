// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "item.generated.h"

UCLASS()
class WARRIOR_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AItem();
    virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
};
