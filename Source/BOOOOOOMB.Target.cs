// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BOOOOOOMBTarget : TargetRules
{
	public BOOOOOOMBTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("BOOOOOOMB");

        bUsesSteam = true;
	}
}
