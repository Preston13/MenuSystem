// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "PuzzlePlatformsGameInstance.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UInGameMenu : public UMenuWidget
{

	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UFUNCTION()
	void ExitMenu();

	UFUNCTION()
	void Quit();
};
