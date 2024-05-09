// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickAssetAction.h"
#include "DebugHeader.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"

void UQuickAssetAction::DuplicateAssets(int32 NumofDuplicates)
{
	if (NumofDuplicates <= 0)
	{
		//Print(TEXT("Please enter a VALID number"), FColor::Red);

		ShowMsgDialog(EAppMsgType::Ok, TEXT("Please enter a VALID number"));
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
		// 성공 여부로 Counter를 이용하는 첫번째 요령
		ShowNotifyInfo(TEXT("Successfully duplicated " + FString::FromInt(Counter) + " files"));

		//Print(TEXT("Successfully duplicated " + FString::FromInt(Counter) + " files"), FColor::Green);
	}

}

void UQuickAssetAction::AddPrefixes()
{
	TArray<UObject*>SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();
	uint32 Counter = 0;

	for (UObject* _SelectedObject : SelectedObjects)
	{
		if (!_SelectedObject) continue;

		// map.find(key:오브젝트) -> value:매칭되는 컨벤션 반환
		FString* PrefixFound = PrefixMap.Find(_SelectedObject->GetClass());
		if (!PrefixFound || PrefixFound->IsEmpty())
		{
			Print(TEXT("Failed to find prefix for class ") + _SelectedObject->GetClass()->GetName(), FColor::Red);
			continue;
		}

		FString OldName = _SelectedObject->GetName();
		if (OldName.StartsWith(*PrefixFound))
		{
			Print(OldName + TEXT(" already has prefix added"), FColor::Red);
			continue;
		}

		/* bad
		if (*PrefixFound == TEXT("MI_"))
		{
			OldName.RemoveFromStart(TEXT("M_"));
		}

		FString suffixFound = TEXT("_Inst");
		if (OldName.EndsWith(*suffixFound))
		{
			OldName.RemoveFromEnd(*suffixFound);
		}
		*/
		if (_SelectedObject->IsA<UMaterialInstanceConstant>())
		{
			OldName.RemoveFromStart(TEXT("M_"));
			OldName.RemoveFromEnd(TEXT("_Inst"));
		}
	

		const FString NewNameWithPrefix = *PrefixFound + OldName;
		UEditorUtilityLibrary::RenameAsset(_SelectedObject, NewNameWithPrefix);
		++Counter;
	}

	if (Counter > 0)
	{
		// 모든 함정을 피한 Counter로 성공을 판단하는 두번째 요령
		ShowNotifyInfo(TEXT("Successfully renamed " + FString::FromInt(Counter) + " assets"));
	}
}
