// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "BubblepopHUD.h"
#include "BubblepopCharacter.h"
#include "BubblepopGameMode.h"
#include <string>
#include <iostream>
#include "math.h"


void ABubblepopHUD::DrawHUD()
{
    if (Canvas != NULL && ABubblepopGameMode::HasGameStarted())
    {
        int32 id = ((APlayerController*)GetOwningPlayerController())->GetLocalPlayer()->GetControllerId();
        ABubblepopCharacter* Player;
        if (id == 0)
        {
            Player = Cast<ABubblepopCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
            Canvas->SetDrawColor(FColor::Blue);

        }
        else
        {
            Player = Cast<ABubblepopCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),1));
            Canvas->SetDrawColor(FColor::Red);

        }
        std::string PlayerText("Score: " + std::to_string(Player->GetPlayerScore()));
        //std::string PlayerTwoText("P2 Score: " + std::to_string(PlayerTwoCharacter->GetPlayerScore()));
        //std::string PlayerOneText("P1 Score: " );
        //std::string PlayerTwoText("P2 Score: " );

        float RemainingTime = Cast<ABubblepopGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetRemainingTime();
        int minutes = RemainingTime / 60;
        int seconds = ((int)RemainingTime) % 60;
        std::string extraZero("");
        if (seconds < 10)
        {
            extraZero = "0";
        }
        std::string RemainingTimeText = std::to_string(minutes) + ":" + extraZero + std::to_string(seconds);
        
        FString PlayerScore = FString(PlayerText.c_str());
        FString Timer = FString(RemainingTimeText.c_str());
        //FString PlayerTwoScore = FString(PlayerTwoText.c_str());
        //Canvas->SetDrawColor(FColor::White);
        //Canvas->DrawText(HUDFont,HUDString1, 150.0f,10.0f, 2.0f, 2.0f);
        const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
        Canvas->DrawText(HUDFont, PlayerScore, 5.0f, 5.0f, 2.0f, 2.0f);
        Canvas->SetDrawColor(FColor(255, 223, 0));
        Canvas->DrawText(HUDFont, Timer, ViewportSize.X/2 - 32, 5.0f, 2.0f, 2.0f);
        Canvas->SetDrawColor(FColor::Black);
        Canvas->DrawText(HUDFont, FString("+"), ViewportSize.X/2 - 4, 105.0, 1.0f, 1.0f);
        //Canvas->DrawText(HUDFont, PlayerTwoScore, ViewportSize.X/2 + 200, 5.0f, 2.0f, 2.0f);
        //Canvas->DrawText(HUDFont, HUDString2, ViewportSize.X/2 - 150, 80.0f, 2.0f, 2.0f);
        //Canvas->DrawText(HUDFont, HUDString2, ViewportSize.X/2 - 150, 100.0f, 2.0f, 2.0f);
        //Canvas->DrawText(HUDFont, HUDString2, ViewportSize.X/2 - 150, 160.0f, 2.0f, 2.0f);


		if(Player->GetPlayerBuffedWeaponDamage()) Canvas->SetDrawColor(FColor::Red);
		else Canvas->SetDrawColor(FColor::Silver);
		Canvas->DrawText(HUDFont, FString("A"), 10.0f, 180.0f, 3.0f, 3.0f);

		if (Player->GetPlayerBuffedDamageResistance()) Canvas->SetDrawColor(FColor::Green);
		else Canvas->SetDrawColor(FColor::Silver);
		Canvas->DrawText(HUDFont, FString("D"), 10.0f, 210.0f, 3.0f, 3.0f);

		if (Player->GetPlayerSpeededUp()) Canvas->SetDrawColor(FColor::Blue);
		else Canvas->SetDrawColor(FColor::Silver);
		Canvas->DrawText(HUDFont, FString("S"), 10.0f, 240.0f, 3.0f, 3.0f);

		if (Player->GetPlayerGettingBonusScore()) Canvas->SetDrawColor(FColor::Yellow);
		else Canvas->SetDrawColor(FColor::Silver);
		Canvas->DrawText(HUDFont, FString("B"), 10.0f, 270.0f, 3.0f, 3.0f);

		Canvas->SetDrawColor(FColor::Silver);
		std::string healthString = "Health:" + std::to_string(Player->GetPlayerHealth()) 
			+ "/" + std::to_string(Player->GetPlayerFullHealth());
		Canvas->DrawText(HUDFont, FString(healthString.c_str()), 10.0f, 300.0f, 3.0f, 3.0f);
        
        if (Player->IsReloading())
        {
            Canvas->SetDrawColor(FColor::Red);
            std::string reloadingString = "Reloading...";
            Canvas->DrawText(HUDFont, FString(reloadingString.c_str()), ViewportSize.X - 270.0f, 300.0f, 3.0f, 3.0f);
            Canvas->SetDrawColor(FColor::Silver);
        }
        else
        {
        
            std::string ammoString = "Ammo:" + std::to_string(Player->GetWeaponAmmo())
                + "/" + std::to_string(Player->GetWeaponClip());
            Canvas->DrawText(HUDFont, FString(ammoString.c_str()), ViewportSize.X - 300.0f, 300.0f, 3.0f, 3.0f);
        }
        //Canvas->DrawText(HUDFont,HUDString1, ViewportSize.X,10.0f, 2.0f, 2.0f);
        //Canvas->DrawText(HUDFont, HUDString2, ViewportSize.X, ViewportSize.Y / 2 + 10, 5.0f, 5.0f);
        
        //FString SomeText = FString(TEXT("Something...!"));
        //FLinearColor TheFontColour = FLinearColor(1.0f, 1.0f, 1.0f);
        //Canvas->DrawText(HUDString2, FColor::White, 50, 50, HUDFont);
        //DrawText(HUDString3, FColor::White, 50, 50, HUDFont);
        //FCanvasTextItem NewText(FVector2D(10.0f, 10.0f), SomeText, NULL, TheFontColour);
        
        //Text Scale
        //NewText.Scale.Set(ScaleX, ScaleY);
        
        //Draw
        //Canvas->DrawItem(NewText);
    }
    else if (Canvas != NULL && ABubblepopGameMode::GameHasEnded() )
    {
        int32 id = ((APlayerController*)GetOwningPlayerController())->GetLocalPlayer()->GetControllerId();
        ABubblepopCharacter* Player;
        if (id == 0)
        {
            Player = Cast<ABubblepopCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
            Canvas->SetDrawColor(FColor::Blue);
            
        }
        else
        {
            Player = Cast<ABubblepopCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),1));
            Canvas->SetDrawColor(FColor::Red);
            
        }
        const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

        std::string resultString;
        if (Player->Result == EndGameResult::Win)
        {
            Canvas->SetDrawColor(FColor::Green);
            resultString = "You Win!";
        }
        else if (Player->Result == EndGameResult::Lose)
        {
            Canvas->SetDrawColor(FColor::Red);
            resultString = "You Lose!";
        }
        else{
            Canvas->SetDrawColor(FColor::Yellow);
            resultString = "You Tie!";
        }
        
        Canvas->DrawText(HUDFont, FString(resultString.c_str()), ViewportSize.X/2 - 100, 140.0f, 3.0f, 3.0f);

    }
}




