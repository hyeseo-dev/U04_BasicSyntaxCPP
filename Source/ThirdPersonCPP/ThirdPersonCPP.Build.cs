using UnrealBuildTool;

public class ThirdPersonCPP : ModuleRules
{
	public ThirdPersonCPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		//PrivateDependencyModuleNames.AddRange(new string[] {  });
		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
