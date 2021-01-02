#include "Tab/SizeofTypeTab.h"
#include "CoreMinimal.h"
#include "Widgets/SWindow.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Views/STableViewBase.h"
#include "Widgets/Views/SHeaderRow.h"
#include "Widgets/Views/STableRow.h"
#define LOCTEXT_NAMESPACE "SizeofType"
DEFINE_LOG_CATEGORY_STATIC(LogSizeof, Log, All)
namespace TestSizeofType {
	// 多列表
	class STypeSizeRow : public SMultiColumnTableRow<TSharedPtr< FSizeTypeItem>>
	{
		SLATE_BEGIN_ARGS(STypeSizeRow) :
			_ItemShow()
		{}
			SLATE_ARGUMENT(TSharedPtr<FSizeTypeItem>, ItemShow)
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
				return SNew(STextBlock)
					.Text(FText::FromString(ItemShow->TypeName));
			}
			else
			{
				return SNew(STextBlock)
					.Text(FText::FromString(FString::Printf(TEXT("%d"), ItemShow->TypeSize)));
			}
		}
	private:
		TSharedPtr<FSizeTypeItem> ItemShow;
	};


	TSharedPtr<SWidget> TestSizeofType::MakeWidget()
	{
		static FWidgetHelper WidgetHelper;
		static TSharedPtr< SListView<TSharedPtr<FSizeTypeItem>>> ThisListView;
		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SMultiLineEditableTextBox)
				.Text(FText::FromString(TEXT("Hello World!")))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(ThisListView,SListView<TSharedPtr<FSizeTypeItem>>)
				.ItemHeight(50)//Item高度
				.ListItemsSource(&WidgetHelper.ItemData)//要显示的数据
				.OnGenerateRow_Lambda([](TSharedPtr<FSizeTypeItem> InItem, const TSharedRef<STableViewBase>& OwnerTable)->TSharedRef<ITableRow> {
					return SNew(STypeSizeRow, OwnerTable)
						.ItemShow(InItem);
				})//生成数据显示项
				.OnContextMenuOpening_Lambda([]() {//右键菜单项
					return SNew(SVerticalBox)
							+SVerticalBox::Slot()
							.AutoHeight()
							[
								SNew(SBorder)
								.BorderImage(FCoreStyle::Get().GetBrush("Menu.Background"))
								.Padding( FMargin(5) )
								[
									SNew(STextBlock) .Text( LOCTEXT("ListContextMenuLabel", "List Context Menu" ) )
								]
							];
				})
				//.SelectionMode(ESelectionMode::Type::SingleToggle) // 第一次是选择，再点一次取消选择
				//.SelectionMode(ESelectionMode::Type::Single) // 单选
				.SelectionMode(ESelectionMode::Type::Multi)  // 多选
				.OnSelectionChanged_Lambda([](TSharedPtr<FSizeTypeItem> inSelectItem, ESelectInfo::Type SelectType)
				{
					if (!inSelectItem.IsValid())
					{
						return;
					}
					//多选结果获取
					if (ThisListView->Private_GetSelectionMode() == ESelectionMode::Type::Multi)
					{
						TArray<TSharedPtr<FSizeTypeItem>> selectItems = ThisListView->GetSelectedItems();
						for (auto elem:selectItems)
						{
							UE_LOG(LogSizeof, Log, TEXT("Select Item, type = %s, size = %d"), *elem->TypeName, elem->TypeSize)
						}
					}
					else //单选结果
					{
						UE_LOG(LogSizeof,Log,TEXT("Select Item, type = %s, size = %d"),*inSelectItem->TypeName,inSelectItem->TypeSize)
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
					+ SHeaderRow::Column("Size")
					.DefaultLabel(FText::FromString(TEXT("Size")))
				)
			]
		;
	}

FWidgetHelper::FWidgetHelper()
{
#define ADD_LIST_ITEM(Type) ItemData.Add(MakeShareable(new FSizeTypeItem(FString(TEXT(#Type)),sizeof(Type))))
	ADD_LIST_ITEM(int8);
	ADD_LIST_ITEM(int16);
	ADD_LIST_ITEM(int32);
	ADD_LIST_ITEM(int64);
	ADD_LIST_ITEM(float);
	ADD_LIST_ITEM(TArray<int8>);
	ADD_LIST_ITEM(FString);
	ADD_LIST_ITEM(FName);
	ADD_LIST_ITEM(FText);
	ADD_LIST_ITEM(UObject);
#undef ADD_LIST_ITEM
}
}
#undef LOCTEXT_NAMESPACE