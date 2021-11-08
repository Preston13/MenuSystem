// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::Setup()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->GetRootWidget()->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	Teardown(InWorld);
}

void UMenuWidget::Teardown(UWorld* InWorld)
{
	this->RemoveFromViewport();

	APlayerController* PlayerController = InWorld->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->bShowMouseCursor = false;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
}

void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterfaceParam)
{
	this->MenuInterface = MenuInterfaceParam;
}
