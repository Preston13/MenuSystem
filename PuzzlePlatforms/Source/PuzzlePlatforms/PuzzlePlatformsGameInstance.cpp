// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"

#include "PlatformTrigger.h"
#include "MainMenu.h"
#include "MenuWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MainMenuBPClass.Class != nullptr)) return;

	MainMenu = MainMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> GameMenuBPClass(TEXT("/Game/MenuSystem/WBP_GameMenu"));
	if (!ensure(GameMenuBPClass.Class != nullptr)) return;

	GameMenu = GameMenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MainMenu != nullptr)) return;
	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MainMenu);

	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();

	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadGameMenu()
{
	if (!ensure(GameMenu != nullptr)) return;
	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, GameMenu);

	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();
	UE_LOG(LogTemp, Warning, TEXT("Setup"));
	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);

}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Leaving")));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MainMenu->GetName());

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->OnNetworkFailure().AddUObject(this, &UPuzzlePlatformsGameInstance::NetworkError);
}

void UPuzzlePlatformsGameInstance::NetworkError(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	LoadMainMenu();
}