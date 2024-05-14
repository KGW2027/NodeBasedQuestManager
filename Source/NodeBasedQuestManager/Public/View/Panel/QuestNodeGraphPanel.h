#pragma once
#include "PanelSlot.h"

class UQuestInfo;

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
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	
private:
	TPanelChildren<FPanelSlot> Children;
	FVector2D RenderOffset;

	void OnNewQuest(UQuestInfo* NewQuest);

	static FSlateFontInfo GetLTFont(float Size);
	
	
};
