#pragma once

#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"

static void Print(const FString& Message, const FColor& Color)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.f, Color, Message);
	}
}

static void PrintLog(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
}

EAppReturnType::Type ShowMsgDialog(EAppMsgType::Type MsgType, const FString& Msg, bool bShowMsgAsWarning = true)
{
	if (bShowMsgAsWarning)
	{
		FText MsgTitle = FText::FromString(TEXT("Warning"));
		return FMessageDialog::Open(MsgType, FText::FromString(Msg), &MsgTitle);
	}
	else
	{
		return FMessageDialog::Open(MsgType, FText::FromString(Msg));
	}
}

void ShowNotifyInfo(const FString& Msg)
{
	FNotificationInfo NotifyInfo(FText::FromString(Msg));
	NotifyInfo.bUseLargeFont = true;
	NotifyInfo.FadeOutDuration = 7.f;

	FSlateNotificationManager::Get().AddNotification(NotifyInfo);
}
