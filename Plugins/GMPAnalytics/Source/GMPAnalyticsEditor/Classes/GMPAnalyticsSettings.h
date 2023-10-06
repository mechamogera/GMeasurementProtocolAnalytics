#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AnalyticsSettings.h"
#include "GMPAnalyticsSettings.generated.h"

UCLASS()
class UGMPAnalyticsSettings : public UAnalyticsSettingsBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = "GMPAnalytics", meta = (ConfigRestartRequired = true))
	FString ApiSecret;

	UPROPERTY(EditAnywhere, Category = "GMPAnalytics", meta = (ConfigRestartRequired = true))
	FString FirebaseAppId;

	UPROPERTY(EditAnywhere, Category = "GMPAnalytics", meta = (ConfigRestartRequired = true))
	FString GroupName;

protected:
	virtual void ReadConfigSettings() override;

	virtual void WriteConfigSettings() override;

protected:
	virtual FString ReadIniValue( 
		const FString& Key
	);

	virtual void WriteConfigIfNotEmpty(
		const FString& Key,
		const FString& Value
	);

	virtual void WriteIniValue(
		const FString& Section, 
		const FString& Key, 
		const FString& Value
	);

};