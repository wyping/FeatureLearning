#include "MenuTest.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateStyle.h"
#include "Widgets/Input/SButton.h"
DEFINE_LOG_CATEGORY_STATIC(LogMenuTest, Log, All);
#define LOCTEXT_NAMESPACE "MenuFeature"

#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define BOX_BRUSH(RelativePath, ...) FSlateBoxBrush(RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define BORDER_BRUSH(RelativePath, ...) FSlateBorderBrush(RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define TTF_FONT(RelativePath, ...) FSlateFontInfo(RootToContentDir(RelativePath, TEXT(".ttf")), __VA_ARGS__)
#define OTF_FONT(RelativePath, ...) FSlateFontInfo(RootToContentDir(RelativePath, TEXT(".otf")), __VA_ARGS__)
class FFeatureStyle : public FSlateStyleSet
{
public:
	FFeatureStyle() : FSlateStyleSet("FFeatureStyle")
	{
		const FVector2D Icon64x64(64.0f, 64.0f);
		const FVector2D Icon40x40(40.0f, 40.0f);
		const FVector2D Icon16x16(16.0f, 16.0f);
		Set("FeatureStyle.LuaIcon_64x", new IMAGE_BRUSH("LuaIcon_64x", Icon64x64));
		Set("FeatureStyle.LuaIcon_40x", new IMAGE_BRUSH("LuaIcon_64x", Icon40x40));
		Set("FeatureStyle.LuaIcon_16x", new IMAGE_BRUSH("LuaIcon_64x", Icon16x16));
		FSlateStyleRegistry::RegisterSlateStyle(*this);
	}
	~FFeatureStyle()
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*this);
	}
	static const ISlateStyle& Get()
	{
		if (!Style.IsValid())
		{
			Style = MakeShareable(new FSlateStyleSet("TestStyle"));
			Style->SetContentRoot(FPaths::EngineDir() / TEXT("Source/Programs/FeatureLearning/Resources"));
		}
		return *Style;
	}
private:
	static TSharedPtr< FSlateStyleSet > Style;
};
TSharedPtr< FSlateStyleSet >  FFeatureStyle::Style = nullptr;
#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT


FTest1MenuCommands::FTest1MenuCommands() : TCommands<FTest1MenuCommands>("commands", LOCTEXT("commands", "Multibox Test"), NAME_None, FFeatureStyle::Get().GetStyleSetName())
{

}

void FTest1MenuCommands::RegisterCommands()
{
	UI_COMMAND(Menu1, "Menu1", "Menu1 tip", EUserInterfaceActionType::ToggleButton, FInputChord());
	UI_COMMAND(Menu2, "Menu2", "Menu2 tip", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Alt, EKeys::Q));// 配置快捷键，Alt + Q
	UI_COMMAND(Menu3, "Menu3", "Menu3 tip", EUserInterfaceActionType::ToggleButton, FInputChord());
}

FMenuWidget::FMenuWidget() :
	CommandList(new FUICommandList())
{

}

TSharedPtr<SWidget> FMenuWidget::MakeMenu()
{
	return MakeMenuBar();
}

TSharedPtr<SWidget> FMenuWidget::MakeMenuBar()
{
	FMenuBarBuilder MenuBuilder(CommandList);
	MenuBuilder.AddPullDownMenu(
		LOCTEXT("Menu1", "CustomMenu"),
		LOCTEXT("Menu1 tip", "Menu 1 tips"),
		FNewMenuDelegate::CreateLambda([](FMenuBuilder& MenuBuilder)
	{
		MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Menu2);
		MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Menu1);
		MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Menu3);
		//显示的顺序就是AddMenuEntry的顺序
		MenuBuilder.BeginSection("Section2");
		{
			MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Menu1);
			MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Menu2);
			MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Menu3);
		}
		MenuBuilder.EndSection();

		// 自定义Widget
		MenuBuilder.BeginSection("Section3");
		{
			MenuBuilder.AddSearchWidget();
			MenuBuilder.AddWidget(
				SNew(SButton)
				.OnClicked_Lambda([]()->FReply { UE_LOG(LogMenuTest, Warning, TEXT("Widget clicked!")); return FReply::Handled(); })
				.Text(LOCTEXT("Widget1", "BtnTest"))
				, LOCTEXT("Widget", "Widget Test"));
			MenuBuilder.AddWidget(SNew(STextBlock).Text(LOCTEXT("WidgetText", "Key1")), LOCTEXT("WidgetText", "WidgetText tips"));
		}
		MenuBuilder.EndSection();

		// 子菜单
		MenuBuilder.BeginSection("Section4");
		{
			MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Menu3);
			MenuBuilder.AddEditableText(LOCTEXT("EditableItem", "Editable Item"), LOCTEXT("EditableItem_ToolTip", "You can edit this item's text"), FSlateIcon(), LOCTEXT("DefaultEditableText", "Edit Me!"));
			MenuBuilder.AddSubMenu(LOCTEXT("SubMenu", "TestSub"), LOCTEXT("SubMenuTip", "Submenu tips"), FNewMenuDelegate::CreateStatic(&FMenuWidget::MakeSubMenu), false);//点击之后，不关闭（感觉不起作用？）
			MenuBuilder.AddEditableText(LOCTEXT("EditableItem1", "Editable Item1"), LOCTEXT("EditableItem_ToolTip", "You can edit this item's text"), FSlateIcon(), LOCTEXT("DefaultEditableText1", "Edit Me too!"));
			MenuBuilder.AddSubMenu(LOCTEXT("SubMenu1", "TestSub1"), LOCTEXT("SubMenuTip1", "Submenu tips1"), FNewMenuDelegate::CreateStatic(&FMenuWidget::MakeSubMenu), true); //点击之后关闭
		}
		MenuBuilder.EndSection();
	})
	);
	return MenuBuilder.MakeWidget();
}

TSharedPtr<SWidget> FMenuWidget::MakeToolBar()
{
	return MakeMenuBar();
}

void FMenuWidget::MakeSubMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Menu3);
	MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Menu2);
	MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Menu1);
}

#undef LOCTEXT_NAMESPACE
