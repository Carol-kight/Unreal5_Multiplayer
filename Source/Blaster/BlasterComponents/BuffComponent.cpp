// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


UBuffComponent::UBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HealRampUp(DeltaTime);
	ShieldRampUp(DeltaTime);
}

void UBuffComponent::Heal(float AmountToHeal, float TimeToHeal)
{
	bHealing = true;
	HealRate = AmountToHeal / TimeToHeal;
	HealAmount += AmountToHeal;
}

void UBuffComponent::HealRampUp(float DeltaTime)
{
	if (!bHealing || Character == nullptr || Character->IsElimmed()) return;
	// the amount to heal this frame
	float HealThisFrame = HealRate * DeltaTime;
	Character->SetHealth(FMath::Clamp(Character->GetHealth() + HealThisFrame, 0, Character->GetMaxHealth()));
	// update health UI
	Character->UpdateHUDHealth();
	
	HealAmount -= HealThisFrame;
	if (HealAmount <= 0.f || Character->GetHealth() >= Character->GetMaxHealth())
	{
		bHealing = false;
		HealAmount = 0.f;
	}
}

void UBuffComponent::ReplenishShield(float AmountToShield, float TimeToShield)
{
	bReplenishing = true;
	ShieldReplenishRate = AmountToShield / TimeToShield;
	ShieldReplenishAmount += AmountToShield;
}

void UBuffComponent::ShieldRampUp(float DeltaTime)
{
	if (!bReplenishing || Character == nullptr || Character->IsElimmed()) return;
	// the amount to replenish this frame
	float ShieldThisFrame = ShieldReplenishRate * DeltaTime;
	Character->SetShield(FMath::Clamp(Character->GetShield() + ShieldThisFrame, 0, Character->GetMaxShield()));
	// update shield UI
	Character->UpdateHUDShield();

	ShieldReplenishAmount -= ShieldThisFrame;
	if (ShieldReplenishAmount <= 0.f || Character->GetShield() >= Character->GetMaxShield())
	{
		bReplenishing = false;
		ShieldReplenishAmount = 0.f;
	}
}

void UBuffComponent::InitializeSpeed(float BaseWalkSpeed, float BaseCrouchSpeed)
{
	InitialBaseSpeed = BaseWalkSpeed;
	InitialCrouchSpeed = BaseCrouchSpeed;
}

void UBuffComponent::BuffSpeed(float BaseSpeedBuff, float CrouchSpeedBuff, float SpeedBuffTime)
{
	if (Character == nullptr || Character->GetCharacterMovement() == nullptr) return;

	Character->GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_ResetSpeed,
		this,
		&UBuffComponent::ResetSpeed,
		SpeedBuffTime
	);

	Character->GetCharacterMovement()->MaxWalkSpeed = BaseSpeedBuff;
	Character->GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeedBuff;

	MulticastBuffSpeed(BaseSpeedBuff, CrouchSpeedBuff);
}

void UBuffComponent::ResetSpeed()
{
	if (Character == nullptr || Character->GetCharacterMovement() == nullptr) return;
	Character->GetCharacterMovement()->MaxWalkSpeed = InitialBaseSpeed;
	Character->GetCharacterMovement()->MaxWalkSpeedCrouched = InitialCrouchSpeed;
	MulticastBuffSpeed(InitialBaseSpeed, InitialCrouchSpeed);
}

void UBuffComponent::MulticastBuffSpeed_Implementation(float BaseSpeed, float CrouchSpeed)
{
	if (Character == nullptr || Character->GetCharacterMovement() == nullptr) return;
	Character->GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
	Character->GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
}

void UBuffComponent::InitializeJumpVelocity(float BaseJumpVelocity)
{
	InitialJumpVelocity = BaseJumpVelocity;
}

void UBuffComponent::BuffJump(float JumpBuffVelocity, float JumpBuffTime)
{
	if (Character == nullptr || Character->GetCharacterMovement() == nullptr) return;

	Character->GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_ResetJumpVelocity,
		this,
		&UBuffComponent::ResetJumpVelocity,
		JumpBuffTime
	);
	
	Character->GetCharacterMovement()->JumpZVelocity = JumpBuffVelocity;
	MulticastBuffJump(JumpBuffVelocity);
}

void UBuffComponent::ResetJumpVelocity()
{
	if (Character == nullptr || Character->GetCharacterMovement() == nullptr) return;
	Character->GetCharacterMovement()->JumpZVelocity = InitialJumpVelocity;
	MulticastBuffJump(InitialJumpVelocity);
}

void UBuffComponent::MulticastBuffJump_Implementation(float JumpVelocity)
{
	if (Character == nullptr || Character->GetCharacterMovement() == nullptr) return;
	Character->GetCharacterMovement()->JumpZVelocity = JumpVelocity;
}









