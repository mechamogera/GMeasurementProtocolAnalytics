#include "Misc/AutomationTest.h"
#include "GMPAnalyticsProvider.h"

/**
 * 実際には通信しないテスト用のProvider
 */
class TestAnalyticsProvider : public FGMPAnalyticsProvider
{
public:
	FString LastURL;
	TMap<FString, FString> LastHeaders;
	FString LastBody;

	TestAnalyticsProvider(
		const FString& FirebaseAppId,
		const FString& ApiSecret,
		const FString& GroupName) : FGMPAnalyticsProvider(FirebaseAppId,
			ApiSecret,
			GroupName) 
	{
		IsEditor = false;
	}
	virtual ~TestAnalyticsProvider() {}

protected:
	virtual void SendHttpPostRequest(const FString& URL, const TMap<FString, FString>& Headers, const FString& Body) override
	{
		LastURL = URL;
		LastHeaders = Headers;
		LastBody = Body;
	}
};

/**
 * テストの定義
 */
BEGIN_DEFINE_SPEC(GMPAnalytics, "GMPAnalytics", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
	const FString DummyUserId = "1234";
	const FString DummyBaseURL = "https://test";
	const FString DummyFirebaseAppId = "FirebaseAppId";
	const FString DummyApiSecret = "ApiSecret";
	const FString DummyAppInstanceId = "AppInstanceId";
	const FString DummyGroupName = "GroupName";


	void ParseURL(const FString& URL, FString& BaseURL, TMap<FString, FString>& Queries);
	void TestURL(const FString& URL, const FString& BaseURL, const FString& FirebaseAppId, const FString& ApiSecret);
	void TestHeaders(const TMap<FString, FString>& Headers);
	void TestBody(const FString& Body, 
				  const FString& UserId, 
				  const FString& AppInstanceId,
				  const bool& NonPersonalizedAds, 
				  const FString& EventName,
				  TSharedPtr<FJsonObject>& Params);
END_DEFINE_SPEC(GMPAnalytics)

/*
 * URLのパース
 */
void GMPAnalytics::ParseURL(const FString& URL, FString& BaseURL, TMap<FString, FString>& Queries)
{
	FString QueriesStr;
	if (!URL.Split(TEXT("?"), &BaseURL, &QueriesStr))
	{
		BaseURL = URL;
		return;
	}

	while (!QueriesStr.IsEmpty())
	{
		FString QueryStr, RemainStr;
		if (QueriesStr.Split(TEXT("&"), &QueryStr, &RemainStr))
		{
			QueriesStr = RemainStr;
		}
		else
		{
			QueryStr = QueriesStr;
			QueriesStr = "";
		}

		FString Key, Value;
		if (QueryStr.Split(TEXT("="), &Key, &Value))
		{
			Queries.Add(Key, Value);
		}
	}
}

/*
 * URLの確認
 */
void GMPAnalytics::TestURL(
	const FString& URL, 
	const FString& InBaseURL, 
	const FString& FirebaseAppId, 
	const FString& ApiSecret
)
{
	FString BaseURL;
	TMap<FString, FString> Headers;
	ParseURL(URL, BaseURL, Headers);
	TestEqual("RequestURLBase", BaseURL, InBaseURL);
	bool isExistFirebaseAppId = false;
	bool isExistApiSecret = false;
	for (const auto& Entry : Headers)
	{
		if (Entry.Key.Equals("firebase_app_id"))
		{
			isExistFirebaseAppId = true;
			TestEqual("firebase_app_id", Entry.Value, FirebaseAppId);
		}
		else if (Entry.Key.Equals("api_secret"))
		{
			isExistApiSecret = true;
			TestEqual("api_secret", Entry.Value, ApiSecret);
		}
	}
	TestTrue("RequestQueries", isExistFirebaseAppId && isExistApiSecret);
}

/*
 * ヘッダの確認
 */
void GMPAnalytics::TestHeaders(const TMap<FString, FString>& Headers)
{
	bool IsExistHeader = false;
	for (const auto& Header : Headers)
	{
		if (Header.Key.Equals("Content-Type"))
		{
			TestEqual("HeaderContentType", Header.Value, "application/json");
			IsExistHeader = true;
		}
	}
	TestTrue("HeaderContentTypeExist", IsExistHeader);
}

/*
 * ボディの確認
 */
void GMPAnalytics::TestBody(
	const FString& Body,
	const FString& UserId,
	const FString& AppInstanceId,
	const bool& NonPersonalizedAds,
	const FString& EventName,
	TSharedPtr<FJsonObject>& Params
)
{
	TSharedPtr<FJsonObject> JsonRootObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Body);
	if (!FJsonSerializer::Deserialize(JsonReader, JsonRootObject))
	{
		return;
	}

	TestEqual("RequestBodyAppInstanceId", JsonRootObject->GetStringField("app_instance_id"), AppInstanceId);
	TestEqual("RequestBodyUserId", JsonRootObject->GetStringField("user_id"), UserId);
	TestEqual("RequestBodyNonPersonalizedAds", JsonRootObject->GetBoolField("non_personalized_ads"), NonPersonalizedAds);
	
	TArray<TSharedPtr<FJsonValue>> Events = JsonRootObject->GetArrayField("events");
	TestEqual("RequestBodyEventsLength", Events.Num(), 1);
	TSharedPtr<FJsonObject> Event = Events[0]->AsObject();
	TestEqual("RequestBodyEventName", Event->GetStringField("name"), EventName);

	Params = Event->GetObjectField("params");

}

/*
 * テスト 
 */
void GMPAnalytics::Define()
{
	Describe("Send Analytics", [this]() {
		It("Send by RecordEvent correctly", [this]() {
			const FString DummyEventName = "EventName";

			TestAnalyticsProvider Provider(DummyFirebaseAppId, DummyApiSecret, DummyGroupName);

			TArray<FAnalyticsEventAttribute> Attributes;
			Provider.SetBaseURL(DummyBaseURL);
			Provider.SetUserID(DummyUserId);
			Provider.SetAppInstanceId(DummyAppInstanceId);
			TestTrue("StartSession", Provider.StartSession(Attributes));

			TArray<FAnalyticsEventAttribute> RecordAttributes;
			RecordAttributes.Add(FAnalyticsEventAttribute("number_param", 82));
			RecordAttributes.Add(FAnalyticsEventAttribute("string_param", "test"));
			RecordAttributes.Add(FAnalyticsEventAttribute("bool_param", "true"));
			Provider.RecordEvent(DummyEventName, RecordAttributes);

			TestURL(Provider.LastURL, DummyBaseURL, DummyFirebaseAppId, DummyApiSecret);
			TestHeaders(Provider.LastHeaders);
			TSharedPtr<FJsonObject> Params;
			TestBody(Provider.LastBody, DummyUserId, DummyAppInstanceId, true, DummyEventName, Params);
			TestValid("Params", Params);
			if (Params.IsValid())
			{
				TestEqual("ParamNumber", Params->GetNumberField("number_param"), 82.0);
				TestEqual("ParamString", Params->GetStringField("string_param"), "test");
				TestEqual("ParamBool", Params->GetBoolField("bool_param"), true);
				TestEqual("ParamGroupName", Params->GetStringField("group_name"), DummyGroupName);
			}
		});
	});
}