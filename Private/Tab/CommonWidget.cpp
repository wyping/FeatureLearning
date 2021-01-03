#include "Tab/CommonWidget.h"
#include "CoreMinimal.h"
#include "Widgets/SWindow.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Views/STableViewBase.h"
#include "Widgets/Views/SHeaderRow.h"
#include "Widgets/Views/STableRow.h"
#define LOCTEXT_NAMESPACE "SizeofType"
DEFINE_LOG_CATEGORY_STATIC(LogSizeof, Log, All)
// 多列表
class STypeSizeRow : public SMultiColumnTableRow<FCommonWidget::FListViewItemPtr>
{
	SLATE_BEGIN_ARGS(STypeSizeRow) :
		_ItemShow()
	{}
	SLATE_ARGUMENT(FCommonWidget::FListViewItemPtr, ItemShow)
		SLATE_END_ARGS()
public:
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)
	{
		ItemShow = InArgs._ItemShow;

		FSuperRowType::Construct(FSuperRowType::FArguments()
			.Padding(0)
			, InOwnerTableView);
	}
public: // override SMultiColumnTableRow
	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override
	{
		if (ColumnName == TEXT("Type"))//判断列名为Type，次名称在创建View时，通过SHeaderRow::Column指定
		{
			TSharedRef<SWidget> typeWidget = SNew(STextBlock)
				.Text(FText::FromString(ItemShow->TypeName));
			// 判斷下是否是有Children且當前表單項為Tree
			if (ItemShow->Children.Num() > 0 && OwnerTablePtr.Pin()->GetTableViewMode() == ETableViewMode::Tree)
			{
				return SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SExpanderArrow, SharedThis(this)) //加入一個展開按鈕
					]
				+ SHorizontalBox::Slot()
					.VAlign(VAlign_Center)
					.AutoWidth()
					[
						typeWidget
					];
			}
			return typeWidget;
		}
		else
		{
			return SNew(STextBlock)
				.Text(FText::FromString(FString::Printf(TEXT("%d"), ItemShow->TypeSize)));
		}
	}
private:
	FCommonWidget::FListViewItemPtr ItemShow;
};


TSharedPtr<SWidget> FCommonWidget::MakeWidget()
{
	return 
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SMultiLineEditableTextBox)
			.Text(FText::FromString(TEXT("Hello World!")))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(ThisListView, SListView<FCommonWidget::FListViewItemPtr>)
			.ItemHeight(50)//Item高度
			.ListItemsSource(&this->ItemData)//要显示的数据
			.OnGenerateRow_Lambda([](FCommonWidget::FListViewItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable)->TSharedRef<ITableRow> {
				return SNew(STypeSizeRow, OwnerTable)
					.ItemShow(InItem);
			})//生成数据显示项
			.OnContextMenuOpening_Lambda([]() {//右键菜单项
				return SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(SBorder)
						.BorderImage(FCoreStyle::Get().GetBrush("Menu.Background"))
						.Padding(FMargin(5))
						[
							SNew(STextBlock).Text(LOCTEXT("ListContextMenuLabel", "List Context Menu"))
						]
					];
			})
			//.SelectionMode(ESelectionMode::Type::SingleToggle) // 第一次是选择，再点一次取消选择
			//.SelectionMode(ESelectionMode::Type::Single) // 单选
			.SelectionMode(ESelectionMode::Type::Multi)  // 多选
			.OnSelectionChanged_Lambda([this](FCommonWidget::FListViewItemPtr inSelectItem, ESelectInfo::Type SelectType)
		{
			if (!inSelectItem.IsValid())
			{
				return;
			}
			//多选结果获取
			if (this->ThisListView->Private_GetSelectionMode() == ESelectionMode::Type::Multi)
			{
				TArray<FCommonWidget::FListViewItemPtr> selectItems = ThisListView->GetSelectedItems();
				for (auto elem : selectItems)
				{
					UE_LOG(LogSizeof, Log, TEXT("Select Item, type = %s, size = %d"), *elem->TypeName, elem->TypeSize)
				}
			}
			else //单选结果
			{
				UE_LOG(LogSizeof, Log, TEXT("Select Item, type = %s, size = %d"), *inSelectItem->TypeName, inSelectItem->TypeSize)
			}

		})
			.HeaderRow //添加一个表头
			(
				SNew(SHeaderRow)
				+ SHeaderRow::Column("Type")
				[
					SNew(SBorder)
					.Padding(5)
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("Type")))
					]
				]
				+ SHeaderRow::Column("Size").DefaultLabel(FText::FromString(TEXT("Size")))
			)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(ThisTreeView, STreeView<FCommonWidget::FListViewItemPtr>)
			.ItemHeight(40)
			.TreeItemsSource(&this->ItemData)
			.OnGenerateRow(this, &FCommonWidget::OnGenerateWidgetTree)
			.OnGetChildren(this, &FCommonWidget::OnGetChildrenTree)
			.HeaderRow
			(
				SNew(SHeaderRow)
				+ SHeaderRow::Column("Type").DefaultLabel(FText::FromString(TEXT("Type")))
				+ SHeaderRow::Column("Size").DefaultLabel(FText::FromString(TEXT("Size")))
			)
		]
	;
}

FCommonWidget::FCommonWidget()
{
#define ADD_LIST_ITEM(Type) ItemData.Add(MakeShareable(new FSizeTypeItem(FString(TEXT(#Type)),sizeof(Type))))
#define ADD_CHILDREN_LIST_ITEM(Type,Parent) ItemData[Parent]->Children.Add(MakeShareable(new FSizeTypeItem(FString(TEXT(#Type)),sizeof(Type))))
	uint32 index = ADD_LIST_ITEM(int8);
	ADD_CHILDREN_LIST_ITEM(int64, index);
	ADD_CHILDREN_LIST_ITEM(char, index);
	ADD_LIST_ITEM(int16);
	index = ADD_LIST_ITEM(int32);
	ADD_CHILDREN_LIST_ITEM(int64, index);
	ADD_CHILDREN_LIST_ITEM(char, index);

	ADD_LIST_ITEM(int64);
	ADD_LIST_ITEM(float);

	index = ADD_LIST_ITEM(TArray<int8>);
	ADD_CHILDREN_LIST_ITEM(int64, index);
	ADD_CHILDREN_LIST_ITEM(char, index);

	ADD_LIST_ITEM(FString);
	ADD_LIST_ITEM(FName);
	ADD_LIST_ITEM(FText);
	ADD_LIST_ITEM(UObject);
#undef ADD_CHILDREN_LIST_ITEM
#undef ADD_LIST_ITEM
}

TSharedRef<class ITableRow> FCommonWidget::OnGenerateWidgetTree(FListViewItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STypeSizeRow, OwnerTable)
		.ItemShow(InItem);
}

void FCommonWidget::OnGetChildrenTree(FListViewItemPtr InItem, TArray<FListViewItemPtr>& OutChildren)
{
	if (InItem.IsValid())
	{
		OutChildren = InItem->Children;
	}
}

#undef LOCTEXT_NAMESPACE