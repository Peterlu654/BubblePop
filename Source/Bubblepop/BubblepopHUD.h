// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "BubblepopHUD.generated.h"

/**
 *
 */
UCLASS()
class BUBBLEPOP_API ABubblepopHUD : public AHUD
{
    GENERATED_BODY()
    
    //DrawText
    FORCEINLINE void DrawText(
                                 UFont*	TheFont,
                                 const FString& TheStr,
                                 const float& X, const float& Y,
                                 const FLinearColor& TheColor,
                                 const float& TheScale,
                                 bool DrawOutline=false,
                                 const FLinearColor OutlineColor=FLinearColor(0,0,0,1)
                                 ) {
        if(!Canvas) return;
        //
        
        //Text and Font
        FCanvasTextItem NewText(
                                FVector2D(X,Y),
                                FText::FromString(TheStr),
                                TheFont,
                                TheColor
                                );
        
        //Text Scale
        NewText.Scale.Set(TheScale,TheScale);
        
        //Outline gets its alpha from the main color
        NewText.bOutlined = true;
        NewText.OutlineColor = OutlineColor;
        NewText.OutlineColor.A = TheColor.A * 2;
        
        //Draw
        Canvas->DrawItem(NewText);
    }
    
public:
    FORCEINLINE void DrawMyText()
    {
        if (Canvas != NULL)
        {
            FString HUDString = FString(TEXT("Testing!"));
            Canvas->DrawText(NULL,HUDString, 10.0f,10.0f);
        }
    }
    
    virtual void DrawHUD() override;
    
protected:
    UPROPERTY(EditAnywhere)
    UFont* HUDFont;

    
};
