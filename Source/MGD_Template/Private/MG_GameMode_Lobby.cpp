// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_GameMode_Lobby.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void AMG_GameMode_Lobby::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	// initialise an empty local array of player starts
	TArray<AActor*> playerStartArray;

	// get all of the player starts, add them into the playerStartArray var
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), playerStartArray);

	// if no player starts then stop.
	if (playerStartArray.IsEmpty())
		return;
	
	for (AActor* actorRef : playerStartArray)
	{
		if (APlayerStart* psRef = Cast<APlayerStart>(actorRef))
		{
			int playerStartIndex = 1;

			if (psRef->PlayerStartTag == FName("Player 1"))
			{
				playerStartIndex = 2;
			}

			const int32 nunPlayers = UGameplayStatics::GetNumPlayerStates(GetWorld());

			if (playerStartIndex == nunPlayers)
			{
				RestartPlayerAtPlayerStart(NewPlayer, psRef);
				break;
			}
		}
	}
}
