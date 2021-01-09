#pragma once
// TCommands 指令定义（Command) : 菜单项点击（快捷键触发）
class FTest1MenuCommands : public TCommands<FTest1MenuCommands>
{
public:
	FTest1MenuCommands();
	virtual void RegisterCommands() override;
public:
	TSharedPtr<FUICommandInfo> Menu1;
	TSharedPtr<FUICommandInfo> Menu2;
	TSharedPtr<FUICommandInfo> Menu3;
	TSharedPtr<FUICommandInfo> Extender1;
	TSharedPtr<FUICommandInfo> Extender2;
};

// FUICommandList : 指令与执行（响应函数的之间的建立映射关系）
/*
	FUICommandList::MapAction
*/

/*
	FMenuBarBuilder: 根据映射关系建立菜单可视项
*/

class FMenuWidget : public TSharedFromThis<FMenuWidget>
{
public:
	FMenuWidget();
public:
	TSharedRef<SWidget> MakeMenuBar();
	TSharedRef<SWidget> MakeToolBar();
	//TSharedRef<SWidget> MakeWithExtender();
private:
	static void MakeSubMenu(class FMenuBuilder &MenuBuilder);
	static void FillExtenderMenu(class FMenuBuilder& MenuBuilder);
	static void FillExtenderToobar(class FToolBarBuilder& ToolBarBuilder);
public:
	TSharedRef<FUICommandList> CommandList;
	bool MenuChecked = false;
};