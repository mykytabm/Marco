// Copyright Epic Games, Inc. All Rights Reserved.

#include "MarcoGameMode.h"
#include "MarcoHUD.h"
#include "MarcoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMarcoGameMode::AMarcoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMarcoHUD::StaticClass();
}
