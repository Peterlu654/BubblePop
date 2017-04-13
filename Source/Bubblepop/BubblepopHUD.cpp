// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "BubblepopHUD.h"


void ABubblepopHUD::DrawHUD()
{
    if (Canvas != NULL)
    {
        FString HUDString1 = FString(TEXT("Testing1!"));
        FString HUDString2 = FString(TEXT("Testing2!"));
        FString HUDString3 = FString(TEXT("Testing3!"));
        Canvas->SetDrawColor(FColor::White);
        Canvas->DrawText(HUDFont,HUDString1, 150.0f,10.0f, 2.0f, 2.0f);
        
        //const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
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



