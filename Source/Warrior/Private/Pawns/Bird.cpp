// Copywrite 2024 darklightMeta


#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h" 
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"


ABird::ABird()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Capsule->SetCapsuleHalfHeight(20.f);
	Capsule->SetCapsuleRadius(15.f);
	//Capsule->SetCollisionProfileName("Pawn");
	//Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	//Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	//Capsule->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);

	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(GetRootComponent());
	//BirdMesh->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
	//BirdMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	//BirdMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	//BirdMesh->SetCollisionProfileName("Pawn");
	//BirdMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//BirdMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}


void ABird::BeginPlay()
{
	Super::BeginPlay();

	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(BirdMappingContext, 0);
		}
	}
	
}

void ABird::MoveForward(float Value)
{
	//AddActorWorldOffset(FVector(0.f, 0.f, Value * 100.f));
	UE_LOG(LogTemp, Warning, TEXT("MoveForward: %f"), Value);
}

void ABird::Move(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();

	if  (Controller && (DirectionValue != 0.f))
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, DirectionValue);
	}
}


void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
	}

	


}

