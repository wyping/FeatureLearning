
#pragma once
class FCommonWidget :public TSharedFromThis<FCommonWidget>
{
public:
	FCommonWidget();
	TSharedPtr<SWidget> MakeWidget();

	struct FSizeTypeItem
	{
		FString TypeName;
		uint32 TypeSize;
		FSizeTypeItem(FString inName, uint32 inSize) :TypeName(inName), TypeSize(inSize) {}
		TArray<TSharedPtr<FSizeTypeItem>> Children;
	};
	typedef TSharedPtr<FSizeTypeItem> FListViewItemPtr;

	TArray<FListViewItemPtr> ItemData;
private:
	TSharedRef<class ITableRow> OnGenerateWidgetTree(FListViewItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);
	void OnGetChildrenTree(FListViewItemPtr InItem, TArray<FListViewItemPtr>& OutChildren);
private:
	TSharedPtr< class SListView<FListViewItemPtr>> ThisListView;
	TSharedPtr< class STreeView<FListViewItemPtr>> ThisTreeView;
};

