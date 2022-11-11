// Fill out your copyright notice in the Description page of Project Settings.

#include "EpicOnlineServicesSettings.h"

inline bool IsAnsi(const FString& Source)
{
	for (const TCHAR& IterChar : Source)
	{
		if (!FChar::IsPrint(IterChar))
		{
			return false;
		}
	}
	return true;
}

inline bool IsHex(const FString& Source)
{
	for (const TCHAR& IterChar : Source)
	{
		if (!FChar::IsHexDigit(IterChar))
		{
			return false;
		}
	}
	return true;
}

inline bool ContainsWhitespace(const FString& Source)
{
	for (const TCHAR& IterChar : Source)
	{
		if (FChar::IsWhitespace(IterChar))
		{
			return true;
		}
	}
	return false;
}

inline FString StripQuotes(const FString& InSource)
{
	if (InSource.StartsWith(TEXT("\"")))
	{
		return InSource.Mid(1, InSource.Len() - 2);
	}
	return InSource;
}

FEpicOnlineServiceArtifactSettings FConfigData::ToNative() const 
{
	FEpicOnlineServiceArtifactSettings Native;
	Native.ArtifactName = ArtifactName;
	Native.ClientId = ClientId;
	Native.ClientSecret = ClientSecret;
	Native.DeploymentId = DeploymentId;
	Native.EncryptionKey = EncryptionKey;
	Native.ProductId = ProductId;
	Native.SandboxId = SandboxId;
	return Native;
}

void FEpicOnlineServiceArtifactSettings::ParseRawArrayEntry(const FString& InRawLine)
{
	const TCHAR* Delims[4] = { TEXT("("),TEXT(")"),TEXT("="),TEXT(",") };
	TArray<FString> Values;
	InRawLine.ParseIntoArray(Values, Delims, 4, false);
	for (int32 ValueIndex = 0; ValueIndex < Values.Num(); ValueIndex++)
	{
		if (Values[ValueIndex].IsEmpty())
		{
			continue;
		}

		// Parse which struct field
		if (Values[ValueIndex] == TEXT("ArtifactName"))
		{
			ArtifactName = StripQuotes(Values[ValueIndex + 1]);
		}
		else if (Values[ValueIndex] == TEXT("ClientId"))
		{
			ClientId = StripQuotes(Values[ValueIndex + 1]);
		}
		else if (Values[ValueIndex] == TEXT("ClientSecret"))
		{
			ClientSecret = StripQuotes(Values[ValueIndex + 1]);
		}
		else if (Values[ValueIndex] == TEXT("ProductId"))
		{
			ProductId = StripQuotes(Values[ValueIndex + 1]);
		}
		else if (Values[ValueIndex] == TEXT("SandboxId"))
		{
			SandboxId = StripQuotes(Values[ValueIndex + 1]);
		}
		else if (Values[ValueIndex] == TEXT("DeploymentId"))
		{
			DeploymentId = StripQuotes(Values[ValueIndex + 1]);
		}
		else if (Values[ValueIndex] == TEXT("EncryptionKey"))
		{
			EncryptionKey = StripQuotes(Values[ValueIndex + 1]);
		}
		ValueIndex++;
	}
}