// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MountainsTarget : TargetRules
{
	public MountainsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		bUseUnityBuild = true;

		ExtraModuleNames.AddRange( new string[] { "Mountains" } );
	}
}
