// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Inventory_UE4 : ModuleRules
{
    public Inventory_UE4(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","Blutility","EditorScriptingUtilities","UMG","Niagara",
            "Slate"});

        PrivateDependencyModuleNames.AddRange(new string[] {"AIModule" });

        PrivateIncludePaths.Add("Inventory_UE4");

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
