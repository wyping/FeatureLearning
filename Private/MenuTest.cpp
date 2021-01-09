#include "MenuTest.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateStyle.h"
#include "Widgets/Input/SButton.h"
#include "Framework/Commands/UIAction.h"
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
	FFeatureStyle() : FSlateStyleSet("FeatureStyle")
	{
		this->SetContentRoot(FPaths::EngineDir() / TEXT("Source/Programs/FeatureLearning/Resources"));
		const FVector2D Icon64x64(64.0f, 64.0f);
		const FVector2D Icon40x40(40.0f, 40.0f);
		const FVector2D Icon16x16(16.0f, 16.0f);
		
		const FLinearColor NormalColor(FColor(0xffeff3f3));
		const FLinearColor SelectedColor(FColor(0xffdbe4d5));
		const FLinearColor HoverColor(FColor(0xffdbe4e4));
		const FLinearColor DisabledColor(FColor(0xaaaaaa));
		const FLinearColor TextColor(FColor(0xff2c3e50));

		Set("commands.Menu1", new IMAGE_BRUSH("LuaIcon_64x", Icon64x64));
		Set("commands.Menu2", new IMAGE_BRUSH("LuaIcon_64x", Icon40x40));
		Set("commands.Menu3", new IMAGE_BRUSH("LuaIcon_64x", Icon16x16));
		Set("TestIcon.Btn", new IMAGE_BRUSH("UE4Icon", Icon64x64));
		Set("commands.Extender1", new IMAGE_BRUSH("UE4Icon", Icon64x64));
		Set("commands.Extender2", new IMAGE_BRUSH("UE4Icon", Icon64x64));  

		const FButtonStyle Button = FButtonStyle()
			.SetNormal(BOX_BRUSH("UE4Icon", Icon64x64, FMargin(1), NormalColor))
			.SetHovered(BOX_BRUSH("UE4Icon", Icon64x64, FMargin(1), HoverColor))
			.SetPressed(BOX_BRUSH("UE4Icon", Icon64x64, FMargin(1), SelectedColor))
			.SetNormalPadding(FMargin(2, 2, 2, 2))
			.SetPressedPadding(FMargin(2, 3, 2, 1));
		Set("TestIcon.Btn", Button);

		
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
			Style = MakeShareable(new FFeatureStyle());
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
	UI_COMMAND(Extender1, "Extender1", "Extender1", EUserInterfaceActionType::ToggleButton, FInputChord());
	UI_COMMAND(Extender2, "Extender2", "Extender2", EUserInterfaceActionType::ToggleButton, FInputChord());
}

FMenuWidget::FMenuWidget() :
	CommandList(new FUICommandList())
{
}

TSharedRef<SWidget> FMenuWidget::MakeMenuBar()
{
	TSharedRef<FExtender> Extender(MakeShareable(new FExtender));
	//在拓展点 Section3之后插入两个菜单项
	Extender->AddMenuExtension("Section3", EExtensionHook::After, this->CommandList, FMenuExtensionDelegate::CreateStatic(&FMenuWidget::FillExtenderMenu));

	FMenuBarBuilder MenuBuilder(CommandList);
	MenuBuilder.PushExtender(Extender);

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
				.ButtonStyle(FFeatureStyle::Get(),"TestIcon.Btn")
				,LOCTEXT("Widget", "Widget Test"));
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

TSharedRef<SWidget> FMenuWidget::MakeToolBar()
{
	FToolBarBuilder ToolsToolbar(CommandList, FMultiBoxCustomization::None);

	TSharedRef<FExtender> Extender(MakeShareable(new FExtender));
	//在Extension1之前追加两项
	Extender->AddToolBarExtension("Extension1", EExtensionHook::Before, this->CommandList, FToolBarExtensionDelegate::CreateStatic(&FMenuWidget::FillExtenderToobar));
	
	ToolsToolbar.PushExtender(Extender);

	ToolsToolbar.BeginSection("Extension1");
	ToolsToolbar.AddToolBarButton(FTest1MenuCommands::Get().Menu1);
	ToolsToolbar.AddToolBarButton(FTest1MenuCommands::Get().Menu2);
	ToolsToolbar.AddToolBarButton(FTest1MenuCommands::Get().Menu3);
	ToolsToolbar.EndSection();

	ToolsToolbar.BeginSection("Extension2");
	ToolsToolbar.AddToolBarWidget(
		SNew(SButton)
		.OnClicked_Lambda([]()->FReply { UE_LOG(LogMenuTest, Warning, TEXT("Widget clicked!")); return FReply::Handled(); })
		.Text(LOCTEXT("Widget1", "BtnTest"))
		.ButtonStyle(FFeatureStyle::Get(), "TestIcon.Btn")
		,LOCTEXT("EditableItem_Click", "Click Me")
	);
	ToolsToolbar.AddEditableText(LOCTEXT("EditableItem1", "Editable Item1"), LOCTEXT("EditableItem_ToolTip", "You can edit this item's text"), FSlateIcon(), LOCTEXT("DefaultEditableText1", "Edit Me too!"));
	ToolsToolbar.AddToolBarWidget(SNew(SCheckBox), LOCTEXT("EditableItem_CheckBox", "Check Me"));
	
	FUIAction uiAction;
	uiAction.ExecuteAction = FExecuteAction::CreateLambda([](){ UE_LOG(LogMenuTest, Warning, TEXT("Widget clicked!"));});
	ToolsToolbar.AddComboButton(uiAction,FOnGetContent::CreateSP(this,&FMenuWidget::MakeMenuBar), LOCTEXT("EditableItem_ComboButton", "ComboButton"));
	ToolsToolbar.EndSection();

	return ToolsToolbar.MakeWidget();
}

//TSharedRef<SWidget> FMenuWidget::MakeWithExtender()
//{
//
//	return MenuBuilder.MakeWidget();
//}

void FMenuWidget::MakeSubMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Menu3);
	MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Menu2);
	MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Menu1);
}

void FMenuWidget::FillExtenderMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Extender2);
	MenuBuilder.AddMenuEntry(FTest1MenuCommands::Get().Extender1);
}

void FMenuWidget::FillExtenderToobar(class FToolBarBuilder& ToolBarBuilder)
{
	ToolBarBuilder.AddToolBarButton(FTest1MenuCommands::Get().Extender1);
	ToolBarBuilder.AddToolBarButton(FTest1MenuCommands::Get().Extender2);
}

#undef LOCTEXT_NAMESPACE
