#pragma once
class FSplineWidget :public TSharedFromThis<FSplineWidget>
{
public:
	TSharedPtr<SWidget> MakeWidget();
	float GetSpineThicknessValue() const;
	void OnSpineThicknesChanged(float inNewValue);
private:
	TSharedPtr<class SSplineWidgetTest> SSpineWidget;
	float Thickness = 5.0f;
};
