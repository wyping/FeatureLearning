
#pragma once

namespace TestSizeofType
{
	TSharedPtr<SWidget> MakeWidget();
}

//TArray<int32> _Tmp;
//_Tmp.Add(1);
//_Tmp.Add(2);
//// 建立窗口
//TSharedPtr<SWindow> MainWindow = SNew(SWindow).ClientSize(FVector2D(1280, 720))
//[
//	SNew(SVerticalBox)
//	+ SVerticalBox::Slot()
//	.AutoHeight()
//	[
//		SNew(SMultiLineEditableTextBox)
//		.Text(FText::FromString(FString::Printf(TEXT("Tarray<int32> with 2 elemmentsize%d, TMemoryImageArray<FShaderParameterInfo> size %d"), sizeof(_Tmp), sizeof(TMemoryImageArray<FShaderParameterInfo>))))
//	]
//+ SVerticalBox::Slot()
//.AutoHeight()
//[
//	SNew(SMultiLineEditableTextBox)
//	.Text(FText::FromString(FString::Printf(TEXT("FShaderParameterMapInfo size %d"), sizeof(FShaderParameterMapInfo))))
//]
//];
//FSlateApplication::Get().AddWindow(MainWindow.ToSharedRef());