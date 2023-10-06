using System;
using UnrealBuildTool;

public class GMPAnalyticsEditor : ModuleRules
{
    public GMPAnalyticsEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateIncludePaths.Add("GMPAnalyticsEditor/Private");

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Analytics",
                "AnalyticsVisualEditing",
                "Engine",
                "Projects",
                "DeveloperSettings"
				// ... add private dependencies that you statically link with here ...	
			}
            );


        PrivateIncludePathModuleNames.AddRange(
            new string[]
            {
                "Settings"
            }
        );
    }
}