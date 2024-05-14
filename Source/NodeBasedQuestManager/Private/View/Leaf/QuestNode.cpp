#include "View/Leaf/QuestNode.h"

#include "Fonts/FontMeasure.h"
#include "Model/QuestInfo.h"

#define BOX_BRUSH(Brush, CornerRadi) \
	Brush.DrawAs = ESlateBrushDrawType::Type::RoundedBox; \
	Brush.OutlineSettings.Width = 1.0; \
	Brush.OutlineSettings.Color = FColor(0x70, 0x70, 0x70); \
	Brush.OutlineSettings.CornerRadii = CornerRadi; \
	Brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;

void SQuestNode::PrivateRegisterAttributes(FSlateAttributeInitializer&)
{
	
}

void SQuestNode::Construct(const FArguments& InArgs)
{
	check(InArgs._Quest.IsSet())
	QuestInfo = InArgs._Quest.Get();
	bIsExpand = false;
}

FVector2D SQuestNode::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	return FVector2D(180, 38);
}

int32 SQuestNode::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const
{
	// TitleText Box Render
	FVector2D TopBoxSize = FVector2D(180, 30);
	{
		FSlateBrush TopBox = FSlateBrush();
		BOX_BRUSH(TopBox, FVector4(4, 4, 0, 0))
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			++LayerId,
			AllottedGeometry.ToPaintGeometry(TopBoxSize, FSlateLayoutTransform(FVector2D(0, 0))),
			&TopBox,
			ESlateDrawEffect::None,
			FColor(0xDD, 0xDD, 0xDD)
		);
	}

	// Expand Metadata Render
	{
		if(!bIsExpand)
		{
			FSlateBrush NotExpand = FSlateBrush();
			BOX_BRUSH(NotExpand, FVector4(0, 0, 0, 0))
			FSlateDrawElement::MakeBox(
				OutDrawElements,
				++LayerId,
				AllottedGeometry.ToPaintGeometry(FVector2D(180, 8), FSlateLayoutTransform(FVector2D(0, 30))),
				&NotExpand,
				ESlateDrawEffect::None,
				FColor(0x80, 0x80, 0x80)
			);
		}
	}

	// Title Text Render and Wrapping
	{
		FSlateFontInfo TitleTextInfo;
		TitleTextInfo.CompositeFont = FCoreStyle::GetDefaultFont();
		TitleTextInfo.Size = 14;
		FVector2D TextSize;
		if(CachedWrapTitle.Key != QuestInfo->DisplayName)
		{
			FString WrapText = QuestInfo->DisplayName;
			while(true) {
				WrapText = WrapText.TrimChar(' ');
				TextSize = FSlateApplication::Get().GetRenderer()->GetFontMeasureService()->Measure(WrapText, TitleTextInfo);
				if(TextSize.X <= TopBoxSize.X - 16) break;
				if(!WrapText.EndsWith("...")) WrapText += "...";
				WrapText.RemoveAt(WrapText.Len()-4);
			}
			CachedWrapTitle = TPair<FString, FString>(QuestInfo->DisplayName, WrapText);
		}
		TextSize = FSlateApplication::Get().GetRenderer()->GetFontMeasureService()->Measure(CachedWrapTitle.Value, TitleTextInfo);
		FSlateDrawElement::MakeText(
			OutDrawElements,
			++LayerId,
			AllottedGeometry.ToPaintGeometry(TextSize, FSlateLayoutTransform((TopBoxSize - TextSize) / 2)),
			CachedWrapTitle.Value,
			0,
			CachedWrapTitle.Value.Len(),
			TitleTextInfo,
			ESlateDrawEffect::None,
			FColor::Black
			);
	}

	return LayerId;
}
