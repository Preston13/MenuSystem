// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostGame);
	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	if (!ensure(JoinGameButton != nullptr)) return false;
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinGame);
	if (!ensure(QuitGameButton_1 != nullptr)) return false;
	QuitGameButton_1->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);
	if (!ensure(BackJoinMenuButton != nullptr)) return false;
	BackJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	return true;
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::HostGame()
{	
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::JoinGame()
{
	if (!ensure(IPAddressField != nullptr)) return;
	if (MenuInterface != nullptr)
	{
		MenuInterface->Join(IPAddressField->GetText().ToString());
	}
}

void UMainMenu::QuitGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}
