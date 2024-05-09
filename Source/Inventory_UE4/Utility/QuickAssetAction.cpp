// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickAssetAction.h"
#include "DebugHeader.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"

void UQuickAssetAction::DuplicateAssets(int32 NumofDuplicates)
{
	if (NumofDuplicates <= 0)
	{
		Print(TEXT("Please enter a VALID number"), FColor::Red);
		return;
	}

	TArray<FAssetData> SelectedAssetsData = UEditorUtilityLibrary::GetSelectedAssetData();
	uint32 Counter = 0;

	for (const FAssetData& _SelectedAssetData : SelectedAssetsData)
	{
		for (int32 i = 0; i < NumofDuplicates; i++)
		{
			// ObjectPath는 PackagePath와 AssetName를 합친 것이다.
			const FString SourceAssetObjectPath = _SelectedAssetData.ObjectPath.ToString();

			// 복사된 에셋 새 이름 = 기존이름_숫자
			const FString NewDuplicatedAssetName = _SelectedAssetData.AssetName.ToString() + TEXT("_") + FString::FromInt(i + 1);

			// Combine 함수 덕분에 PackagePath와 AssetName를 잘 합칠 수 있다.
			const FString NewDuplicatedAssetObjectPath = FPaths::Combine(_SelectedAssetData.PackagePath.ToString(), NewDuplicatedAssetName);

			// 실질적으로 복사를 실행해주는 핵심인 DuplicateAsset
			if (UEditorAssetLibrary::DuplicateAsset(SourceAssetObjectPath, NewDuplicatedAssetObjectPath))
			{
				UEditorAssetLibrary::SaveAsset(NewDuplicatedAssetObjectPath, false);
				++Counter;
			}
		}
	}

	if (Counter > 0)
	{
		// 성공 여부로 Counter를 이용하는 요령
		Print(TEXT("Successfully duplicated " + FString::FromInt(Counter) + " files"), FColor::Green);
	}

}
