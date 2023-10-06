#include "GMPAnalyticsProvider.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "GMPAnalyticsJsonHelper.h"

DEFINE_LOG_CATEGORY_STATIC(LogUEGAnalytics, Display, All);
#define UE_AP_LOG(Verbosity, Format, ...) UE_LOG(LogTemp, Verbosity, Format, ##__VA_ARGS__)

FGMPAnalyticsProvider::FGMPAnalyticsProvider
(
	const FString& InFirebaseAppId, 
	const FString& InApiSecret,
	const FString& InGroupName
) : bHasSessionStarted(false),
	Age(0),
	ApiSecret(InApiSecret),
	FirebaseAppId(InFirebaseAppId),
	GroupName(InGroupName),
	AppInstanceId("12345678910111213141516171819202"),
	BaseURL("https://www.google-analytics.com/mp/collect")
{
	UserId = FPlatformMisc::GetLoginId();
}

FGMPAnalyticsProvider::~FGMPAnalyticsProvider()
{
	if (bHasSessionStarted)
	{
		EndSession();
	}
}

bool FGMPAnalyticsProvider::StartSession(const TArray<FAnalyticsEventAttribute>& Attributes)
{
	if (bHasSessionStarted)
	{
		EndSession();
	}

	if (!BaseURL.IsEmpty() && !FirebaseAppId.IsEmpty() && !ApiSecret.IsEmpty())
	{
		bHasSessionStarted = true;
	}
	else
	{
		UE_AP_LOG(Error, TEXT("FGMPAnalyticsProvider::StartSession called without setting FirebaseAppId or ApiSecret"));
	}

	return bHasSessionStarted;
}

void FGMPAnalyticsProvider::EndSession()
{
	bHasSessionStarted = false;
}

void FGMPAnalyticsProvider::FlushEvents()
{

}

void FGMPAnalyticsProvider::SetUserID(const FString& InUserID)
{
	if (!bHasSessionStarted)
	{
		UserId = InUserID;
	}
	else
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::SetUserID called while a session is in progress.Ignoring."));
	}
}

bool FGMPAnalyticsProvider::SetSessionID(const FString& InSessionID)
{
	if (!bHasSessionStarted)
	{
		SessionId = InSessionID;
	}
	else
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::SetSessionID called while a session is in progress.Ignoring."));
	}

	return !bHasSessionStarted;
}

void FGMPAnalyticsProvider::RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes)
{
	if (bHasSessionStarted)
	{
		SendToGA(EventName, Attributes);
	}
	else
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordEvent called before StartSession or Editor. Ignoring."));
	}
}

void FGMPAnalyticsProvider::RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity)
{
	if (bHasSessionStarted)
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordItemPurchase not yet implemented. Ignoring."));
	}
	else
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordItemPurchase called before StartSession or Editor. Ignoring."));
	}
}

void FGMPAnalyticsProvider::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider)
{
	if (bHasSessionStarted)
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordCurrencyPurchase not yet implemented. Ignoring."));
	}
	else
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordCurrencyPurchase called before StartSession or Editor. Ignoring."));
	}
}

void FGMPAnalyticsProvider::RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount)
{
	if (bHasSessionStarted)
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordCurrencyGiven not yet implemented. Ignoring."));
	}
	else
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordCurrencyGiven called before StartSession or Editor. Ignoring."));
	}
}

void FGMPAnalyticsProvider::RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& EventAttrs)
{
	if (bHasSessionStarted)
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordItemPurchasey not yet implemented. Ignoring."));
	}
	else
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordItemPurchase called before StartSession or Editor. Ignoring."));
	}
}

void FGMPAnalyticsProvider::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& EventAttrs)
{
	if (bHasSessionStarted)
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordCurrencyPurchase not yet implemented. Ignoring."));
	}
	else
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordCurrencyPurchase called before StartSession or Editor. Ignoring."));
	}
}

void FGMPAnalyticsProvider::RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& EventAttrs)
{
	if (bHasSessionStarted)
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordCurrencyGiven not yet implemented. Ignoring."));
	}
	else
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordCurrencyGiven called before StartSession or Editor. Ignoring."));
	}
}

void FGMPAnalyticsProvider::RecordError(const FString& Error, const TArray<FAnalyticsEventAttribute>& EventAttrs)
{
	if (bHasSessionStarted)
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordError not yet implemented. Ignoring."));
	}
	else
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordError called before StartSession or Editor. Ignoring."));
	}
}

void FGMPAnalyticsProvider::RecordProgress(const FString& ProgressType, const FString& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& EventAttrs)
{
	if (bHasSessionStarted)
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordProgress not yet implemented. Ignoring."));
	}
	else
	{
		UE_AP_LOG(Warning, TEXT("FGMPAnalyticsProvider::RecordProgress called before StartSession or Editor. Ignoring."));
	}
}

FString FGMPAnalyticsProvider::CreateJson(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes)
{
	// JSON POSTÇÃç\íz
	TSharedPtr<FJsonObject> RootObject = MakeShareable(new FJsonObject);
	RootObject->SetStringField("app_instance_id", AppInstanceId);
	RootObject->SetStringField("user_id", UserId);
	RootObject->SetBoolField("non_personalized_ads", true);

	// paramsÇÃç\íz
	TSharedPtr<FJsonObject> Params = MakeShareable(new FJsonObject());
	for (const FAnalyticsEventAttribute Attribute : Attributes)
	{
		FString AttributeValue = Attribute.GetValue();
		EJsonValueType Type = UGMPAnalyticsJsonHelper::DetectTypeFromJson(AttributeValue);
		switch (Type)
		{
		case EJsonValueType::Boolean:
			Params->SetBoolField(Attribute.GetName(), UGMPAnalyticsJsonHelper::ConvertAsBoolFromJson(AttributeValue));
			break;
		case EJsonValueType::Number:
			Params->SetNumberField(Attribute.GetName(), UGMPAnalyticsJsonHelper::ConvertAsDoubleFromJson(AttributeValue));
			break;
		case EJsonValueType::String:
		default:
			Params->SetStringField(Attribute.GetName(), UGMPAnalyticsJsonHelper::ConvertAsStringFromJson(AttributeValue));
		}
	}

	// eventsÇÃç\íz
	TSharedPtr<FJsonObject> EventObject = MakeShareable(new FJsonObject);
	EventObject->SetStringField("name", EventName);
	EventObject->SetObjectField("params", Params);

	TArray<TSharedPtr<FJsonValue>> Events;
	Events.Add(MakeShareable(new FJsonValueObject(EventObject)));
	RootObject->SetArrayField("events", Events);

	// jsonÇï∂éöóÒÇ…
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(RootObject.ToSharedRef(), Writer);

	return JsonString;
}

void FGMPAnalyticsProvider::SendToGA(const FString& EventName, const TArray<FAnalyticsEventAttribute>& InAttributes)
{
	const TArray<FAnalyticsEventAttribute> Attributes = CreateSendAttributes(InAttributes);

	if (!IsEditor)
	{
		FString URL = FString::Format(TEXT("{0}?firebase_app_id={1}&api_secret={2}"),
			{ *BaseURL, *FirebaseAppId, *ApiSecret });
		TMap<FString, FString> Headers;
		Headers.Add("Content-Type", "application/json");
		SendHttpPostRequest(URL, Headers, CreateJson(EventName, Attributes));
	}
	else
	{
		TArray<FString> AttributeStrs;
		for (const auto& Attribute : Attributes)
		{
			AttributeStrs.Add(FString::Format(TEXT("{0}={1}"), { *Attribute.GetName(), *Attribute.GetValue() }));
		}

		UE_AP_LOG(Warning, TEXT("EditorPlay Ignoring. Data tried to send is EventName:%s Params:%s"),
			*EventName, *FString::Join(AttributeStrs, TEXT(", ")));
	}
}

void FGMPAnalyticsProvider::SendHttpPostRequest(const FString& URL, const TMap<FString, FString>& Headers, const FString& Body)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb("POST");
	for (const auto& Header : Headers)
	{
		HttpRequest->AppendToHeader(Header.Key, Header.Value);
	}

	HttpRequest->SetContentAsString(Body);
	HttpRequest->ProcessRequest();

	UE_AP_LOG(Verbose, TEXT("Data to send is Body:%s"), *Body);
}

TArray<FAnalyticsEventAttribute> FGMPAnalyticsProvider::CreateSendAttributes(const TArray<FAnalyticsEventAttribute>& Attributes)
{
	TArray<FAnalyticsEventAttribute> NewAttributes = Attributes;
	// paramsÇ…ÉOÉãÅ[ÉvñºÇÃí«â¡
	if (!GroupName.IsEmpty())
	{
		NewAttributes.Add(FAnalyticsEventAttribute(TEXT("group_name"), GroupName));
	}
	return NewAttributes;
}