// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIV2023_First_Lesson.h"
#include "Modules/ModuleManager.h"
#include "Editor.h"

class FAIVGameModule : public FDefaultGameModuleImpl, public FSelfRegisteringExec
{
public:
	virtual bool Exec(UWorld* world, const TCHAR* Cmd, FOutputDevice& Ar) override
	{
		if (FParse::Command(&Cmd, TEXT("CheckCommand")))
		{
			int32 number = 0;
			FParse::Value(Cmd, TEXT("n ="), number);
			UE_LOG(LogTemp, Warning, TEXT("ALL GOOD"));
			TArray<FAssetData> AssetData;
			GEditor->GetContentBrowserSelections(AssetData);
			for (const FAssetData &selected:AssetData)
			{
				UBlueprint* BP = Cast<UBlueprint>(selected.GetAsset());
				if (BP == nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("BP NULL"));
					continue;
				}
				AActor* BP_Actor = Cast<AActor>(BP->GeneratedClass.GetDefaultObject());
				if (BP_Actor == nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("ACTOR NULL"));
					continue;
				}
				if (number == 0)
				{
					world->SpawnActor(BP_Actor->StaticClass(), NULL, NULL);
					continue;
				}
				for (int32 i = 0; i < number; ++i)
				{
					world->SpawnActor(BP_Actor->StaticClass(), NULL, NULL);
				}
			}
			return true;
		}
		return false;
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FAIVGameModule, AIV2023_First_Lesson, "AIV2023_First_Lesson" );
