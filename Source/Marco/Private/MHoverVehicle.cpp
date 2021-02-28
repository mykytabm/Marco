// Fill out your copyright notice in the Description page of Project Settings.


#include "MHoverVehicle.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMHoverVehicle::AMHoverVehicle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	MeshComp->SetSimulatePhysics(true);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	BaseForwardForce = 50000;
	BaseTurnTorque = 100000;

}

// Called when the game starts or when spawned
void AMHoverVehicle::BeginPlay()
{
	Super::BeginPlay();

}

void AMHoverVehicle::MoveForward(float Value)
{
	ForwardForce = BaseForwardForce * Value;
}

void AMHoverVehicle::MoveRight(float Value)
{
	TurnTorque = BaseTurnTorque * Value;
}

// Called every frame
void AMHoverVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MeshComp->AddForce(GetActorForwardVector() * ForwardForce);
	MeshComp->AddTorqueInDegrees(GetActorUpVector() * TurnTorque);
}

// Called to bind functionality to input
void AMHoverVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMHoverVehicle::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMHoverVehicle::MoveRight);

}

