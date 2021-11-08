// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	void NetworkError(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

	virtual void Init() override;

	UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadGameMenu();

	UFUNCTION(Exec)
	virtual void Host() override;

	UFUNCTION(Exec)
	virtual void Join(const FString& Address) override;

	UFUNCTION()
	virtual void LoadMainMenu() override;

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> MainMenu;

	UPROPERTY()
	TSubclassOf<UUserWidget> GameMenu;


};
