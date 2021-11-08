// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"

#include "Components/Button.h"


bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::ExitMenu);
	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::Quit);

	return true;
}

void UInGameMenu::ExitMenu()
{
	Teardown(GetWorld());
}

void UInGameMenu::Quit()
{
	UE_LOG(LogTemp,Warning, TEXT("Quitting"));
	if (MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("MenuInterface exists"));
		Teardown(GetWorld());
		MenuInterface->LoadMainMenu();
	}
}
