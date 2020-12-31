#include "Tab/SizeofTypeTab.h"
#include "Widgets/SWindow.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

TSharedPtr<SWidget> TestSizeofType::MakeWidget()
{
	return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SMultiLineEditableTextBox)
				.Text(FText::FromString(TEXT("Hello World!")))
			]
	//	+ SVerticalBox::Slot()
	//	.AutoHeight()
	//	[
	//		SNew(SMultiLineEditableTextBox)
	//		.IsReadOnly(true)
	//	.Text(FText::FromString(FString::Printf(TEXT("Tarray<int32> with 2 elemmentsize%d, TMemoryImageArray<FShaderParameterInfo> size %d"), sizeof(_Tmp), sizeof(TMemoryImageArray<FShaderParameterInfo>))))
	//	]
	//+ SVerticalBox::Slot()
	//	.AutoHeight()
	//	[
	//		SNew(SMultiLineEditableTextBox)
	//		.IsReadOnly(true)
	//	.Text(FText::FromString(FString::Printf(TEXT("FShaderParameterMapInfo size %d"), sizeof(FShaderParameterMapInfo))))
	//	]
	;
}
