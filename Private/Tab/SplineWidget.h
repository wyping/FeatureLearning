#pragma once
class FSplineWidget :public TSharedFromThis<FSplineWidget>
{
public:
	FSplineWidget();
	TSharedPtr<SWidget> MakeWidget();
	float GetSpineThicknessValue() const;
	void OnSpineThicknesChanged(float inNewValue);
private:
	FText OnGetSplineModeText() const;
	void OnSelectSplineMode(TSharedPtr<FString>  NewSelection, ESelectInfo::Type SelectInfo);
private:
	TSharedPtr<class SSplineWidgetTest> SSpineWidget;
	float Thickness = 5.0f;

	TArray<TSharedPtr<FString>> SplineMode;

	// 0: Hermite Spline, 1:Bezier Spline
	int32 SelectSplineModeIndex = 0;
};
