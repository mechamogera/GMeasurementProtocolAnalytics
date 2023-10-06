#include "GMPAnalyticsEditor.h"

#include "Modules/ModuleManager.h"
#include "GMPAnalyticsSettings.h"
#include "Analytics.h"

IMPLEMENT_MODULE(FGMPAnalyticsEditorModule, UGMPAnalyticsEditor);

#define LOCTEXT_NAMESPACE "FGMPAnalyticsEditorModule"

void FGMPAnalyticsEditorModule::StartupModule()
{
}

void FGMPAnalyticsEditorModule::ShutdownModule()
{
}

UGMPAnalyticsSettings::UGMPAnalyticsSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SettingsDisplayName = LOCTEXT("SettingsDisplayName", "GMPAnalytics");
	SettingsTooltip = LOCTEXT("SettingsTooltip", "GoogleAnalytics configuration settings");
}

void UGMPAnalyticsSettings::ReadConfigSettings()
{
	ApiSecret = ReadIniValue(TEXT("ApiSecret"));
	FirebaseAppId = ReadIniValue(TEXT("FirebaseAppId"));
	GroupName = ReadIniValue(TEXT("GroupName"));
}

void UGMPAnalyticsSettings::WriteConfigSettings()
{
	WriteConfigIfNotEmpty(TEXT("ApiSecret"), ApiSecret);
	WriteConfigIfNotEmpty(TEXT("FirebaseAppId"), FirebaseAppId);
	WriteConfigIfNotEmpty(TEXT("GroupName"), GroupName);
}

FString UGMPAnalyticsSettings::ReadIniValue(const FString& Key)
{
	FString ReadValue = FAnalytics::Get().GetConfigValueFromIni(GetIniName(), GetReleaseIniSection(), Key, true);
	return ReadValue;
}

void UGMPAnalyticsSettings::WriteConfigIfNotEmpty(
	const FString& Key,
	const FString& Value)
{
	if (Value.IsEmpty())
	{
		return;
	}

	WriteIniValue(GetReleaseIniSection(), Key, Value);
	WriteIniValue(GetTestIniSection(), Key, Value);
	WriteIniValue(GetDebugIniSection(), Key, Value);
	WriteIniValue(GetDevelopmentIniSection(), Key, Value);
}

void UGMPAnalyticsSettings::WriteIniValue(
	const FString& Section,
	const FString& Key, 
	const FString& Value)
{
	FAnalytics::Get().WriteConfigValueToIni(GetIniName(), Section, Key, Value);
}

#undef LOCTEXT_NAMESPACE