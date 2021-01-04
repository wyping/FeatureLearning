#include "Tab/SplineWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SSpinBox.h"
DEFINE_LOG_CATEGORY_STATIC(LogSpline, Log, All)
#define LOCTEXT_NAMESPACE "SplineWidgetTest"
class SSplineWidgetTest : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSplineWidgetTest)
	: _P1(FVector2D(0,32))
	, _P2(FVector2D(200,32))
	, _P3(FVector2D(0,200))
	, _P4(FVector2D(200,200))
	, _SpineThickness(1.0f)
	{}
		SLATE_ARGUMENT(FVector2D,P1)
		SLATE_ARGUMENT(FVector2D,P2)
		SLATE_ARGUMENT(FVector2D,P3)
		SLATE_ARGUMENT(FVector2D,P4)
		SLATE_ATTRIBUTE(float,SpineThickness)
	SLATE_END_ARGS()
public:
	void Construct(const FArguments &InArgs)
	{
		SetPoint(InArgs._P1, InArgs._P2, InArgs._P3, InArgs._P4);
		ThicknessValue = InArgs._SpineThickness;
	}

	void SetPoint(const FVector2D &p1,const FVector2D&p2,const FVector2D&p3,const FVector2D&p4 )
	{
		BezierPoints[0] = p1;
		BezierPoints[1] = p2;
		BezierPoints[2] = p3;
		BezierPoints[3] = p4;
	}

private:
	virtual int32 OnPaint(const FPaintArgs& Args, 
		const FGeometry& AllottedGeometry, 
		const FSlateRect& MyCullingRect, 
		FSlateWindowElementList& OutDrawElements, 
		int32 LayerId, 
		const FWidgetStyle& InWidgetStyle, 
		bool bParentEnabled) const override
	{
		// 画四个控制点
		for (int index = 0; index < 4; ++ index)
		{
			FSlateDrawElement::MakeBox(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(BezierPointRadius,FSlateLayoutTransform(1.0f, BezierPoints[index])),
				&WhiteBox,
				bParentEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect,
				FLinearColor::Green
			);
		}
		// 画Spine
		++LayerId;
		FSlateDrawElement::MakeCubicBezierSpline(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			BezierPoints[0], BezierPoints[1], BezierPoints[2], BezierPoints[3],
			ThicknessValue.Get() * AllottedGeometry.Scale,
			bParentEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect,
			FColor::White
		);
		return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	}

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) 
	{
		if (MouseEvent.GetEffectingButton() != EKeys::LeftMouseButton)
		{
			return FReply::Unhandled();
		}

		//鼠标左键按下，且实在控制点区域内的按下，捕获鼠标，并handle鼠标消息
		FVector2D localPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
		DragIndex = GetMouseClickHandleIndex(localPos);
		if (DragIndex != INDEX_NONE)
		{
			return FReply::Handled().CaptureMouse(SharedThis(this));
		}
		return FReply::Unhandled();
	}

	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
	{
		//是否捕获的鼠标
		if (DragIndex != INDEX_NONE && MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			DragIndex = INDEX_NONE;
			return FReply::Handled().ReleaseMouseCapture();
		}
		return FReply::Unhandled().ReleaseMouseCapture();
	}

	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
	{
		if (DragIndex != INDEX_NONE && MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			const FVector2D  curLocalMousLoc = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
			BezierPoints[DragIndex] = curLocalMousLoc;
			return FReply::Handled();
		}
		return FReply::Unhandled();
	}
	
	// 判断鼠标落点是不是控制点范围，如果是返回控制点索引
	int32 GetMouseClickHandleIndex(FVector2D inMouseLoc)
	{
		for (int32 index = 0 ; index < 4; ++ index)
		{
			if ((BezierPoints[index] - inMouseLoc).SizeSquared() < BezierPointRadius.SizeSquared())
			{
				return index;
			}
		}
		return INDEX_NONE;
	}

private:
	FVector2D BezierPoints[4];
	TAttribute<float> ThicknessValue;
	FSlateColorBrush WhiteBox = FSlateColorBrush(FColor::White);
	int32 DragIndex = INDEX_NONE;
	const FVector2D BezierPointRadius = FVector2D(8, 8); // 控制点大小 X:长，Y：宽
};


TSharedPtr<SWidget> FSplineWidget::MakeWidget()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.FillWidth(1)
			[
				SNew(SSpinBox<float>)
				.MinValue(0.1f)
				.MaxValue(10.0f)
				.Value(this,&FSplineWidget::GetSpineThicknessValue)
				.OnValueChanged(this,&FSplineWidget::OnSpineThicknesChanged)
			]
			+ SHorizontalBox::Slot()
			[
				SNew(SButton)
				.Text(LOCTEXT("HorizontalHermite", "Horizontal"))
				.OnClicked_Lambda([this]()
				{
					SSpineWidget->SetPoint(FVector2D(0, 64), FVector2D(66, 64), FVector2D(133, 64), FVector2D(200, 64));
					return FReply::Handled();
				})
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(SSpineWidget,SSplineWidgetTest)
		]
	;
}

float FSplineWidget::GetSpineThicknessValue() const
{
	return Thickness;
}

void FSplineWidget::OnSpineThicknesChanged(float inNewValue)
{
	Thickness = inNewValue;
}


#undef LOCTEXT_NAMESPACE