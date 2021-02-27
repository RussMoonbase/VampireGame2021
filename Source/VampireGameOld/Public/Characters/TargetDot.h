// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetDot.generated.h"

class UImage;

UCLASS( Abstract )
class VAMPIREGAMEOLD_API UTargetDot : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* Dot;
	
};
