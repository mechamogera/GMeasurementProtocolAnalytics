#pragma once

#include "CoreMinimal.h"
#include "AnalyticsEventAttribute.h"
#include "Interfaces/IAnalyticsProvider.h"
#

class FGMPAnalyticsProvider : public IAnalyticsProvider
{
	/** Tracks whether we need to start the session or restart it */
	bool bHasSessionStarted;
	/** Id representing the user the analytics are recording for */
	FString UserId;
	/** Unique Id representing the session the analytics are recording for */
	FString SessionId;
	/** Holds the Age if set */
	int32 Age;
	/** Holds the Location of the user if set */
	FString Location;
	/** Holds the Gender of the user if set */
	FString Gender;
	/** Holds the build info if set */
	FString BuildInfo;

	/* For Google Analytics */
	FString ApiSecret;
	FString FirebaseAppId;
	FString GroupName;
	FString AppInstanceId;
	FString BaseURL;

protected:
#if WITH_EDITOR
	bool IsEditor = true;
#else
	bool IsEditor = false;
#endif

public:
	FGMPAnalyticsProvider(
		const FString& FirebaseAppId, 
		const FString& ApiSecret,
		const FString& GroupName
	);
	virtual ~FGMPAnalyticsProvider();

	virtual void SetBaseURL(const FString& InBaseURL) { BaseURL = InBaseURL; }
	virtual void SetAppInstanceId(const FString& InAppInstanceId) { AppInstanceId = InAppInstanceId; }
	virtual void SetFirebaseAppId(const FString& InFirebaseAppId) { FirebaseAppId = InFirebaseAppId; }
	virtual void SetApiSecret(const FString& InApiSecret) { ApiSecret = InApiSecret; }

	virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes) override;
	virtual void EndSession() override;
	virtual void FlushEvents() override;

	virtual void SetUserID(const FString& InUserID) override;
	virtual FString GetUserID() const override { return UserId;  };

	virtual FString GetSessionID() const override { return SessionId; };
	virtual bool SetSessionID(const FString& InSessionID) override;

	virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override;

	virtual void RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity) override;

	virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider) override;

	virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount) override;

	virtual void SetBuildInfo(const FString& InBuildInfo) override { BuildInfo = InBuildInfo; };
	virtual void SetGender(const FString& InGender) override { Gender = InGender; };
	virtual void SetLocation(const FString& InLocation) override { Location = InLocation; };
	virtual void SetAge(const int32 InAge) override { Age = InAge; };

	virtual void RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;
	virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;
	virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;
	virtual void RecordError(const FString& Error, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;
	virtual void RecordProgress(const FString& ProgressType, const FString& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;

protected:
	virtual FString CreateJson(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes);
	virtual void SendToGA(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes);
	virtual void SendHttpPostRequest(const FString& URL, const TMap<FString, FString>& Headers, const FString& Body);
	virtual TArray<FAnalyticsEventAttribute> CreateSendAttributes(const TArray<FAnalyticsEventAttribute>& Attributes);
};