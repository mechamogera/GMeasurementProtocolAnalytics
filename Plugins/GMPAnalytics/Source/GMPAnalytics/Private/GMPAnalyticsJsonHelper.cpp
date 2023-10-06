#include "GMPAnalyticsJsonHelper.h"

FString UGMPAnalyticsJsonHelper::ConvertIntToJson(int Value)
{
	return FString::FromInt(Value);
}

FString UGMPAnalyticsJsonHelper::ConvertFloatToJson(float Value)
{
	return FString::SanitizeFloat(Value);
}

FString UGMPAnalyticsJsonHelper::ConvertBoolToJson(bool Value)
{
	return Value ? TEXT("true") : TEXT("false");
}

FString UGMPAnalyticsJsonHelper::ConvertStringToJson(FString Value)
{
	return FString::Format(TEXT("\"{0}\""), { *Value.Replace(TEXT("\""), TEXT("\\\"")) });
}

EJsonValueType UGMPAnalyticsJsonHelper::DetectTypeFromJson(const FString& Str)
{
	if (Str.IsNumeric())
	{
		return EJsonValueType::Number;
	}
	else if (Str.Equals("true") || Str.Equals("false"))
	{
		return EJsonValueType::Boolean;
	}
	return EJsonValueType::String;
}

int UGMPAnalyticsJsonHelper::ConvertAsIntFromJson(const FString& Str)
{
	return FCString::Atoi(*Str);
}

double UGMPAnalyticsJsonHelper::ConvertAsDoubleFromJson(const FString& Str)
{
	return FCString::Atod(*Str);
}

float UGMPAnalyticsJsonHelper::ConvertAsFloatFromJson(const FString& Str)
{
	return FCString::Atof(*Str);
}

bool UGMPAnalyticsJsonHelper::ConvertAsBoolFromJson(const FString& Str)
{
	return Str.ToBool();
}

FString UGMPAnalyticsJsonHelper::ConvertAsStringFromJson(const FString& Str)
{
	FString ReturnStr = Str;
	if (Str.StartsWith("\""))
	{
		ReturnStr = ReturnStr.LeftChop(1);
	}

	if (Str.EndsWith("\""))
	{
		ReturnStr = ReturnStr.RightChop(1);
	}

	return ReturnStr.Replace(TEXT("\\\""), TEXT("\""));
}