// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "PuzzlePlatformsGameInstance.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()



protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinGameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitGameButton_1;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* IPAddressField;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void HostGame();

	UFUNCTION()
	void JoinGame();

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void OpenMainMenu();

};
