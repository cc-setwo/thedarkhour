// Created by CC. All rights reserved.

#pragma once

#include "Components/Widget.h"
#include "WidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class UWidgetBase : public UWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	UWidget* STATICWIDGET;
	
	
};
