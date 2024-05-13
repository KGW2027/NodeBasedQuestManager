#pragma once
#include "PanelSlot.h"

class SQuestNodeGraphPanel : public SPanel
{
	SLATE_DECLARE_WIDGET_API(SQuestNodeGraphPanel, SPanel, NODEBASEDQUESTMANAGER_API)
	SLATE_BEGIN_ARGS(SQuestNodeGraphPanel){}
		
	SLATE_END_ARGS()
	
	SQuestNodeGraphPanel();
	void Construct(const FArguments& InArgs);
	void ClearChildren();
	
	virtual FChildren* GetChildren() override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;
	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override { return FVector2D(0, 0); }
	virtual bool SupportsKeyboardFocus() const override { return true; }

	virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	
private:
	TPanelChildren<FPanelSlot> Children;
	FVector2D RenderOffset;

	static FSlateFontInfo GetLTFont(float Size);
	
	
};
