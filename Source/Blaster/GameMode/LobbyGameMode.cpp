// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"

// PostLogin() is the first place that's safe to access PlayerController after that player
// has joined a game.
void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	// GameMode has a GameState variable with an array of players that have joined the game (PlayerStates).
	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	UE_LOG(LogTemp, Warning, TEXT("Number of players: %d"), NumberOfPlayers);
	if (NumberOfPlayers == 2)
	{
		UWorld* World = GetWorld();
		
		if (World)
		{
			bUseSeamlessTravel = true;
			World->ServerTravel(FString("/Game/Maps/BlasterMap?listen"));
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to get world!"));
			}
		}
	}
}
