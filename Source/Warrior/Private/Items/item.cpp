


#include "Items/item.h"
#include "DrawDebugHelpers.h"
#include "Warrior/DebugMacro.h"


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	
	
		
	
}

// ReSharper disable once CppMemberFunctionMayBeConst
float AItem::TransformSin()
{
	return Amplitude * FMath::Sin(RunningTime* TimeConstant);
}

// ReSharper disable once CppMemberFunctionMayBeConst
float AItem::TransformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}



// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	//float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);

	//AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ)); // period = 2*pi/K

	//Movement rate in units of cm/s
	//float MovementRate = 100.f;
	//float RotationRate = 45.f;

	// MovementRate * DeltaTime (cm/s) * (s/frame)	= (cm/frame)
	//AddActorWorldOffset(FVector(MovementRate * DeltaTime, 0.f, 0.f));
	//AddActorWorldRotation(FRotator(0.f, RotationRate * DeltaTime, 0.f));
	DRAW_SPHERE_SINGLE_FRAME(GetActorLocation());
	DRAW_VECTOR_SINGLE_FRAME(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f);
}

