#include "FeatureLearning.h"
#include "ISourceCodeAccessModule.h"
#include "RequiredProgramMainCPPInclude.h"
#include "Framework/Application/SlateApplication.h"
#include "StandaloneRenderer.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Shader.h"
#include "ISlateReflectorModule.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/SWindow.h"
#include "Tab/CommonWidget.h"
#include "Tab/SplineWidget.h"
#include "MenuTest.h"
void InitApp();
TSharedRef<SDockTab> SpawnSizeofTab(const FSpawnTabArgs& Args);

DEFINE_LOG_CATEGORY_STATIC(LogFeatureLearning, Log, All);

IMPLEMENT_APPLICATION(FeatureLearning, "FeatureLearning");// 注册模块
#define LOCTEXT_NAMESPACE "EngineFeature"

TSharedPtr<FCommonWidget> CommonWidgetPtr;
TSharedPtr<FSplineWidget> SplineWidgetPtr;
TSharedPtr<FMenuWidget> MenuWidgetPtr;
namespace WorkspaceMenu
{
	TSharedRef<FWorkspaceItem> MenuRoot = FWorkspaceItem::NewGroup(LOCTEXT("MenuRoot", "MenuRoot"));
	TSharedRef<FWorkspaceItem> SlateReflector = FWorkspaceItem::NewGroup(LOCTEXT("SlateReflectorTab", "WidgetReflector"));
	TSharedRef<FWorkspaceItem> SizeofType = FWorkspaceItem::NewGroup(LOCTEXT("SizeofTypeTab", "SizeofType"));
	TSharedRef<FWorkspaceItem> SplineWidgetTab = FWorkspaceItem::NewGroup(LOCTEXT("SplineWidgetTab", "SplineWidget"));
}

TSharedRef<SDockTab> SpawnSystemMenu(const FSpawnTabArgs& Args)
{
	FMenuBarBuilder MenuBarBuilder = FMenuBarBuilder(TSharedPtr<FUICommandList>());
	MenuBarBuilder.AddPullDownMenu(
		NSLOCTEXT("Feature", "WindowMenuLabel", "Window"),
		FText::GetEmpty(),
		FNewMenuDelegate::CreateSP(FGlobalTabmanager::Get(), &FTabManager::PopulateTabSpawnerMenu, WorkspaceMenu::MenuRoot)
	);

	return SNew(SDockTab)
		.Label(WorkspaceMenu::MenuRoot->GetDisplayName())
		.ToolTipText(LOCTEXT("System", "sizeof type"))
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				MenuBarBuilder.MakeWidget() //建立菜单项
			]
			+SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SNew(STextBlock).Text(LOCTEXT("TestMenu","Menu Content"))
			]
		];
}

TSharedRef<SDockTab> _StaticSpawnSizeofTab()
{
	return SNew(SDockTab)
		.Label(WorkspaceMenu::SizeofType->GetDisplayName())
		.ToolTipText(LOCTEXT("TypeSizeof", "sizeof type"))
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				MenuWidgetPtr->MakeMenuBar().ToSharedRef()//建立菜单项
			]
			+SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				CommonWidgetPtr->MakeWidget().ToSharedRef()
			]
		];
}
TSharedRef<SDockTab> SpawnSizeofTab(const FSpawnTabArgs& Args)
{
	return _StaticSpawnSizeofTab();
}

TSharedRef<SDockTab> _StaticSpawnSplineTab()
{
	return SNew(SDockTab)
		.Label(WorkspaceMenu::SplineWidgetTab->GetDisplayName())
		.ToolTipText(LOCTEXT("SpawnSplineTab", "SpawnSpline"))
		[
			SplineWidgetPtr->MakeWidget().ToSharedRef()
		];
}
TSharedRef<SDockTab> SpawnSplineTab(const FSpawnTabArgs& Args)
{
	return _StaticSpawnSplineTab();
}



int WINAPI WinMain(_In_ HINSTANCE hInInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR, _In_ int nCmdShow)
{
	// 启动引擎的主循环，解析命令行
	int32 result = GEngineLoop.PreInit(GetCommandLineW());
	if (result != 0)
	{
		UE_LOG(LogFeatureLearning,Error,TEXT("Engine Preinit failed."));
		return -1;
	}

	// 使用StandaloneRenderer渲染器渲染Slate，如果Cmd中没有指定opengl，则使用FSlateD3DRenderer渲染器
	FSlateApplication::InitializeAsStandaloneApplication(GetStandardStandaloneRenderer());

	// Load the source code access module
	ISourceCodeAccessModule& SourceCodeAccessModule = FModuleManager::LoadModuleChecked<ISourceCodeAccessModule>(FName("SourceCodeAccess"));
	// Manually load in the source code access plugins, as standalone programs don't currently support plugins.
#if PLATFORM_MAC
	IModuleInterface& XCodeSourceCodeAccessModule = FModuleManager::LoadModuleChecked<IModuleInterface>(FName("XCodeSourceCodeAccess"));
	SourceCodeAccessModule.SetAccessor(FName("XCodeSourceCodeAccess"));
#elif PLATFORM_WINDOWS
	IModuleInterface& VisualStudioSourceCodeAccessModule = FModuleManager::LoadModuleChecked<IModuleInterface>(FName("VisualStudioSourceCodeAccess"));
	SourceCodeAccessModule.SetAccessor(FName("VisualStudioSourceCodeAccess"));
#endif
	FModuleManager::LoadModuleChecked<ISlateReflectorModule>("SlateReflector").RegisterTabSpawner(WorkspaceMenu::SlateReflector);

	CommonWidgetPtr = MakeShareable(new FCommonWidget());
	SplineWidgetPtr = MakeShareable(new FSplineWidget());
	InitApp();

	// loop while the server does the rest
	while (!IsEngineExitRequested())
	{
		FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
		FStats::AdvanceFrame(false);
		FTicker::GetCoreTicker().Tick(FApp::GetDeltaTime());
		FSlateApplication::Get().PumpMessages();
		FSlateApplication::Get().Tick();
		FPlatformProcess::Sleep(0);
	}

	CommonWidgetPtr.Reset();
	SplineWidgetPtr.Reset();
	FCoreDelegates::OnExit.Broadcast();
	FSlateApplication::Shutdown();
	FModuleManager::Get().UnloadModulesAtShutdown();
	return 0;
}

void InitApp()
{
	//初始化菜单项
	MenuWidgetPtr = MakeShareable(new FMenuWidget);
	FTest1MenuCommands::Register();
	MenuWidgetPtr->CommandList->MapAction(FTest1MenuCommands::Get().Menu1, FExecuteAction::CreateLambda([]() {UE_LOG(LogFeatureLearning, Warning, TEXT("Click Menu1")); }));
	MenuWidgetPtr->CommandList->MapAction(FTest1MenuCommands::Get().Menu2, FExecuteAction::CreateLambda([]() {UE_LOG(LogFeatureLearning, Warning, TEXT("Click Menu2")); }));
	MenuWidgetPtr->CommandList->MapAction(FTest1MenuCommands::Get().Menu3, 
		FExecuteAction::CreateLambda([]() {UE_LOG(LogFeatureLearning, Warning, TEXT("Click Menu3")); MenuWidgetPtr->MenuChecked = !MenuWidgetPtr->MenuChecked; }),//点击菜单项，绑定处理函数
		FCanExecuteAction::CreateLambda([](){return true; }),
		FIsActionChecked::CreateLambda([]() {return MenuWidgetPtr->MenuChecked; })//菜单项上的CheckBox是否勾选
	);

	// 注册TabSpawner
	{
		FGlobalTabmanager::Get()->RegisterTabSpawner(FName(*(WorkspaceMenu::MenuRoot->GetDisplayName().ToString())), FOnSpawnTab::CreateStatic(&SpawnSystemMenu));
		FGlobalTabmanager::Get()->RegisterTabSpawner(FName(*(WorkspaceMenu::SizeofType->GetDisplayName().ToString())), FOnSpawnTab::CreateStatic(&SpawnSizeofTab));
		FGlobalTabmanager::Get()->RegisterTabSpawner(FName(*(WorkspaceMenu::SplineWidgetTab->GetDisplayName().ToString())), FOnSpawnTab::CreateStatic(&SpawnSplineTab));
	}

	// 设置布局文件
	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("EngineFeature")
		->AddArea
		(
			FTabManager::NewArea(1920,1080)
			->Split
			(
				FTabManager::NewStack()
				->SetHideTabWell(true)
				->AddTab(FName(*(WorkspaceMenu::SlateReflector->GetDisplayName().ToString())), ETabState::OpenedTab)
				->AddTab(FName(*(WorkspaceMenu::SizeofType->GetDisplayName().ToString())), ETabState::OpenedTab)
				->AddTab(FName(*(WorkspaceMenu::SplineWidgetTab->GetDisplayName().ToString())), ETabState::OpenedTab)
				->AddTab(FName(*(WorkspaceMenu::MenuRoot->GetDisplayName().ToString())), ETabState::OpenedTab)
			)
		);
	FGlobalTabmanager::Get()->RestoreFrom(Layout, TSharedPtr<SWindow>());
}

#undef LOCTEXT_NAMESPACE