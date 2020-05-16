// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LearnToolbarButton : ModuleRules
{
	public LearnToolbarButton(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange( new string[] {
        });
		
		PrivateIncludePaths.AddRange( new string[] {
        });
		
		PublicDependencyModuleNames.AddRange( new string[] {
				"Core",
        });
			
		PrivateDependencyModuleNames.AddRange( new string[] {
				"Projects",
				"InputCore",
				"UnrealEd",
				"ToolMenus",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
        });
		
		DynamicallyLoadedModuleNames.AddRange( new string[] {
        });
	}
}
