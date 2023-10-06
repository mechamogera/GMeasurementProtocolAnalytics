#include "Misc/AutomationTest.h"
#include "GMPAnalyticsJsonHelper.h"

BEGIN_DEFINE_SPEC(GMPAnalyticsHelper, "GMPAnalytics", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
END_DEFINE_SPEC(GMPAnalyticsHelper)

void GMPAnalyticsHelper::Define()
{
	Describe("Json Helper", [this]() {
		It("ConvertToJson", [this]() {
			TestEqual("ConvertTrueToJson", UGMPAnalyticsJsonHelper::ConvertBoolToJson(true), "true");
			TestEqual("ConvertFalseToJson", UGMPAnalyticsJsonHelper::ConvertBoolToJson(false), "false");
			TestEqual("ConvertFloatToJson", UGMPAnalyticsJsonHelper::ConvertFloatToJson(10.5f), "10.5");
			TestEqual("ConvertIntToJson", UGMPAnalyticsJsonHelper::ConvertIntToJson(50), "50");
			TestEqual("ConvertStringToJson", UGMPAnalyticsJsonHelper::ConvertStringToJson("te\"st"), "\"te\\\"st\"");
		});

		It("ConvertFromJson", [this]() {
			TestEqual("ConvertTrueFromJson", UGMPAnalyticsJsonHelper::ConvertAsBoolFromJson("true"), true);
			TestEqual("ConvertFalseFromJson", UGMPAnalyticsJsonHelper::ConvertAsBoolFromJson("false"), false);
			TestEqual("ConvertFloatFromJson", UGMPAnalyticsJsonHelper::ConvertAsFloatFromJson("10.5"), 10.5f);
			TestEqual("ConvertAsDoubleFromJson", UGMPAnalyticsJsonHelper::ConvertAsDoubleFromJson("10.5"), 10.5);
			TestEqual("ConvertStringToJson", UGMPAnalyticsJsonHelper::ConvertAsStringFromJson("\"te\\\"st\""), "te\"st");
			TestEqual("ConvertNormalStringToJson", UGMPAnalyticsJsonHelper::ConvertAsStringFromJson("te\\\"st"), "te\"st");
		});

		It("DetectTypeFromJson", [this]() {
			TestEqual("DetectTrue", UGMPAnalyticsJsonHelper::DetectTypeFromJson("true"), EJsonValueType::Boolean);
			TestEqual("DetectFalse", UGMPAnalyticsJsonHelper::DetectTypeFromJson("false"), EJsonValueType::Boolean);
			TestEqual("DetectFloat", UGMPAnalyticsJsonHelper::DetectTypeFromJson("10.5"), EJsonValueType::Number);
			TestEqual("DetectInt", UGMPAnalyticsJsonHelper::DetectTypeFromJson("10"), EJsonValueType::Number);
			TestEqual("DetectEmptyString", UGMPAnalyticsJsonHelper::DetectTypeFromJson(""), EJsonValueType::String);
			TestEqual("DetectNotEmptyString", UGMPAnalyticsJsonHelper::DetectTypeFromJson("test"), EJsonValueType::String);
			TestEqual("DetectStringWithQuotation", UGMPAnalyticsJsonHelper::DetectTypeFromJson("\"test\""), EJsonValueType::String);
		});
	});
}