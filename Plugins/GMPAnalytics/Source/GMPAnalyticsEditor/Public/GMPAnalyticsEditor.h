#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FGMPAnalyticsEditorModule : public IModuleInterface
{
private:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};