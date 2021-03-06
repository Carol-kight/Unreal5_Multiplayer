// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterOverlay.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class BLASTER_API UCharacterOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HealthText;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ShieldBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ShieldText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DefeatsNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponAmmoNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CarriedAmmoNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MatchCountdonwText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GrenadesText;

	UPROPERTY(meta = (BindWidget))
	UImage* HighPingImage;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* HighPingAnimation;
};
