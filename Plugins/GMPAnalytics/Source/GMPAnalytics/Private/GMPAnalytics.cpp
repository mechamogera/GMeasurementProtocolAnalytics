// Copyright Epic Games, Inc. All Rights Reserved.

#include "GMPAnalytics.h"
#include "GMPAnalyticsProvider.h"

#define LOCTEXT_NAMESPACE "FGMPAnalyticsModule"

TSharedPtr<IAnalyticsProvider> FGMPAnalyticsModule::GMPAnalytics;

void FGMPAnalyticsModule::StartupModule()
{
	
}

void FGMPAnalyticsModule::ShutdownModule()
{
	if (GMPAnalytics.IsValid())
	{
		GMPAnalytics->EndSession();
	}
}

TSharedPtr<IAnalyticsProvider> FGMPAnalyticsModule::CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const
{
	if (GetConfigValue.IsBound())
	{
		if (!GMPAnalytics.IsValid())
		{
			FString FirebaseAppId = GetConfigValue.Execute(TEXT("FirebaseAppId"), true);

			FString ApiSecret = GetConfigValue.Execute(TEXT("ApiSecret"), true);
			
			FString GroupName = GetConfigValue.Execute(TEXT("GroupName"), false);

			GMPAnalytics = TSharedPtr<IAnalyticsProvider>(
				new FGMPAnalyticsProvider(FirebaseAppId, ApiSecret, GroupName));
		}

		return GMPAnalytics;
	}
	else
	{

	}
	
	return nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGMPAnalyticsModule, GMPAnalytics)