// Fill out your copyright notice in the Description page of Project Settings.


#include "MHoverComponent.h"
#include "MHoverVehicle.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UMHoverComponent::UMHoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	HoverDistance = 100.0f;
	SpringCoeff = 400.0f;
	DampingCoeff = 80;
	// ...
}


// Called when the game starts
void UMHoverComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<AMHoverVehicle>(GetOwner());
}
// ...


// Called every frame
void UMHoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(Owner)) {
		FHitResult Hit;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(Owner);


		auto TraceStart = this->GetComponentLocation();
		auto TraceEnd = TraceStart - this->GetUpVector() * HoverDistance;

		bool LineTraceHit = GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 0.0f, 0, 1.0f);

		if (LineTraceHit) {
			HoverDelta = HoverDistance - Hit.Distance;
			auto ForceScalar = ((HoverDelta - PreviousHoverDelta) / GetWorld()->GetDeltaSeconds()) * DampingCoeff + HoverDelta * SpringCoeff;
			auto Force = this->GetUpVector() * ForceScalar;
			Cast<UPrimitiveComponent>(Owner->GetRootComponent())->AddForceAtLocation(Force, this->GetComponentLocation());
			PreviousHoverDelta = HoverDelta;
		}
	}
}

