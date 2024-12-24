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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float Amplitude = 0.25f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant = 5.f;
	
	UFUNCTION(BlueprintPure)
	float TransformSin();
	
	UFUNCTION(BlueprintPure)
	float TransformedCos( );
	
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta =( AllowPrivateAccess = "true"))
	float RunningTime;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * ItemMesh;

	

	
};
