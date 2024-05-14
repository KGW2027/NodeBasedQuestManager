#pragma once

class UQuestInfo;

class SQuestNode : public SLeafWidget
{
	SLATE_DECLARE_WIDGET_API(SQuestNode, SLeafWidget, NODEBASEDQUESTMANAGER_API)
	SLATE_BEGIN_ARGS(SQuestNode){}
		SLATE_ATTRIBUTE(UQuestInfo*, Quest)
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);
	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	
private:
	UQuestInfo* QuestInfo;
	bool bIsExpand;
	mutable TPair<FString, FString> CachedWrapTitle;
};
