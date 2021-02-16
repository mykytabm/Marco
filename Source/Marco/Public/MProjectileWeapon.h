// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MWeapon.h"
#include "MProjectileWeapon.generated.h"

/**
 *
 */
UCLASS()
class MARCO_API AMProjectileWeapon : public AMWeapon
{
GENERATED_BODY()

protected:

	virtual void BeginPlay() override;


	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "ProjectileWeapon")
	TSubclassOf<AActor> ProjectileClass;

};
