#pragma once

#include "CoreMinimal.h"
#include "AnalyticsEventAttribute.h"
#include "GMPAnalyticsJsonHelper.generated.h"

UENUM(BlueprintType)
enum class EJsonValueType : uint8
{
	Boolean,
	Number,
	String,
};

UCLASS()
class GMPANALYTICS_API UGMPAnalyticsJsonHelper : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static FString ConvertIntToJson(int Value);

	UFUNCTION(BlueprintPure)
	static FString ConvertFloatToJson(float Value);

	UFUNCTION(BlueprintPure)
	static FString ConvertBoolToJson(bool Value);

	UFUNCTION(BlueprintPure)
	static FString ConvertStringToJson(FString Value);

	UFUNCTION(BlueprintPure)
	static EJsonValueType DetectTypeFromJson(const FString& Str);

	UFUNCTION(BlueprintPure)
	static int ConvertAsIntFromJson(const FString& Str);

	static double ConvertAsDoubleFromJson(const FString& Str);

	UFUNCTION(BlueprintPure)
	static float ConvertAsFloatFromJson(const FString& Str);

	UFUNCTION(BlueprintPure)
	static bool ConvertAsBoolFromJson(const FString& Str);

	UFUNCTION(BlueprintPure)
	static FString ConvertAsStringFromJson(const FString& Str);
};