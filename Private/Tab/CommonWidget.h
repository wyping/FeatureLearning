
#pragma once

class FCommonWidget :public TSharedFromThis<FCommonWidget>
{
public:
	TSharedPtr<SWidget> MakeWidget();

	struct FSizeTypeItem
	{
		FString TypeName;
		uint32 TypeSize;
		FSizeTypeItem(FString inName, uint32 inSize) :TypeName(inName), TypeSize(inSize) {}
	};

	FCommonWidget();
	TArray<TSharedPtr<FSizeTypeItem>> ItemData;

private:
	TSharedPtr< class SListView<TSharedPtr<FSizeTypeItem>>> ThisListView;
};

typedef TSharedPtr<FCommonWidget::FSizeTypeItem> FListViewItemPtr;