// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	friend class ABlasterCharacter;

	UBuffComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Heal(float AmountToHeal, float TimeToHeal);
	void HealRampUp(float DeltaTime);

	void ReplenishShield(float AmountToShield, float TimeToShield);
	void ShieldRampUp(float DeltaTime);

	void BuffSpeed(float BaseSpeedBuff, float CrouchSpeedBuff, float SpeedBuffTime);
	void InitializeSpeed(float BaseWalkSpeed, float BaseCrouchSpeed);

	void BuffJump(float JumpBuffVelocity, float JumpBuffTime);
	void InitializeJumpVelocity(float BaseJumpVelocity);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class ABlasterCharacter* Character;

	/**
	 * Heal Buff
	 */

	bool bHealing = false;
	float HealAmount;
	float HealRate;

	/**
	 * Shield Buff
	 */

	bool bReplenishing = false;
	float ShieldReplenishAmount;
	float ShieldReplenishRate;

	/**
	 * Speed Buff
	 */

	float InitialBaseSpeed;
	float InitialCrouchSpeed;

	FTimerHandle TimerHandle_ResetSpeed;
	void ResetSpeed();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastBuffSpeed(float BaseSpeed, float CrouchSpeed);

	/**
	 * Jump Buff
	 */

	float InitialJumpVelocity;
	FTimerHandle TimerHandle_ResetJumpVelocity;

	void ResetJumpVelocity();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastBuffJump(float JumpVelocity);
public:	
	

		
};
