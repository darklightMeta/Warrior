// Copyright 2024 darklightMeta


#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include  "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"


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


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	
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



void ABird::Move(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();

	if  (Controller && (DirectionValue != 0.f))
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, DirectionValue);
	}
}

void ABird::Look(const FInputActionValue& Value)
{
  const FVector2D LookAxisValue = Value.Get<FVector2D>();
  if (GetController())
  {
	  AddControllerYawInput(LookAxisValue.X);
	  AddControllerPitchInput(LookAxisValue.Y);
  	  
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
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABird::Look);
	}

	


}

