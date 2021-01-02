
#pragma once

namespace TestSizeofType
{
	TSharedPtr<SWidget> MakeWidget();

	struct FSizeTypeItem
	{
		FString TypeName;
		uint32 TypeSize;
		FSizeTypeItem(FString inName, uint32 inSize):TypeName(inName),TypeSize(inSize){}
	};

	class FWidgetHelper:public TSharedFromThis<FWidgetHelper> {
	public:
		FWidgetHelper();
		TArray<TSharedPtr<FSizeTypeItem>> ItemData;
	};
}