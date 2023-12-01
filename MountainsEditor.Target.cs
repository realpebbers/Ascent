// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MountainsEditorTarget : TargetRules
{
	public MountainsEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		bUseUnityBuild = true;

		ExtraModuleNames.AddRange( new string[] { "Mountains" } );
	}
}
