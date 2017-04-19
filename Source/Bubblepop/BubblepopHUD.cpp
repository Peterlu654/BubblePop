// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "BubblepopHUD.h"
#include "BubblepopCharacter.h"
#include "BubblepopGameMode.h"
#include <string>
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
        Canvas->DrawText(HUDFont, FString("+"), ViewportSize.X/2 - 16, 50.0, 1.0f, 1.0f);
        //Canvas->DrawText(HUDFont, PlayerTwoScore, ViewportSize.X/2 + 200, 5.0f, 2.0f, 2.0f);
        //Canvas->DrawText(HUDFont, HUDString2, ViewportSize.X/2 - 150, 80.0f, 2.0f, 2.0f);
        //Canvas->DrawText(HUDFont, HUDString2, ViewportSize.X/2 - 150, 100.0f, 2.0f, 2.0f);
        //Canvas->DrawText(HUDFont, HUDString2, ViewportSize.X/2 - 150, 160.0f, 2.0f, 2.0f);




        
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
}




