#include "View/Panel/QuestNodeGraphPanel.h"

#include "Control/EditorEventListener.h"
#include "Control/QuestAssetEditor.h"
#include "Model/QuestInfo.h"
#include "View/Leaf/QuestNode.h"

#pragma region Initializer
void SQuestNodeGraphPanel::PrivateRegisterAttributes(FSlateAttributeInitializer&)
{
	
}
SQuestNodeGraphPanel::SQuestNodeGraphPanel() : Children(this, GET_MEMBER_NAME_CHECKED(SQuestNodeGraphPanel, Children))
{
	
}
void SQuestNodeGraphPanel::Construct(const FArguments& InArgs)
{
	RenderOffset = FVector2D(0, 0);
	FQuestAssetEditor::Listener->OnAddQuest.AddRaw(this, &SQuestNodeGraphPanel::OnNewQuest);
}
void SQuestNodeGraphPanel::ClearChildren()
{
	Children.Empty();
}
FChildren* SQuestNodeGraphPanel::GetChildren()
{
	return &Children;
}
#pragma endregion 

#pragma region Paint API
int32 SQuestNodeGraphPanel::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FArrangedChildren ArrangedChildren(EVisibility::Visible);
	this->ArrangeChildren(AllottedGeometry, ArrangedChildren);

	// Draw Arranged Children
	const FPaintArgs ChildArgs = Args.WithNewParent(this);
	for(int32 Index = 0 ; Index < ArrangedChildren.Num() ; Index++)
	{
		FArrangedWidget& Widget = ArrangedChildren[Index];
		// UE_LOG(LogTemp, Log, TEXT("%s Render on (%.0f, %.0f)"), *Widget.Widget->GetType().ToString(), Widget.Geometry.Position.X, Widget.Geometry.Position.Y);
		Widget.Widget->Paint(ChildArgs, Widget.Geometry, MyCullingRect, OutDrawElements, ++LayerId, InWidgetStyle, bParentEnabled);
	}

	// Draw Big Border
	FSlateDrawElement::MakeLines(
		OutDrawElements,
		++LayerId,
		AllottedGeometry.ToPaintGeometry(),
		{FVector2D(0,0), FVector2D(AllottedGeometry.Size.X, 0), FVector2D(AllottedGeometry.Size.X, AllottedGeometry.Size.Y), FVector2D(0, AllottedGeometry.Size.Y), FVector2D(0, 0)},
		ESlateDrawEffect::None,
		FColor(0xFF, 0xFF, 0xFF),
		true,
		3.0
		);
	
	// Draw LT Texts
	FSlateFontInfo FontInfo = GetLTFont(24.0);
	const TArray LeftTopTexts = 
	{
		FString::Printf(TEXT("Zoom : x%.1f"), FQuestAssetEditor::ZoomMultiplier),
		FString::Printf(TEXT("Offset : %.0f, %.0f"), RenderOffset.X, RenderOffset.Y),
		FString::Printf(TEXT("Quests : 0"))
	};
	for(int Line = 0 ; Line < LeftTopTexts.Num() ; Line++)
	{
		FSlateDrawElement::MakeText(
			OutDrawElements,
			++LayerId,
			AllottedGeometry.ToOffsetPaintGeometry(FVector2D(4.0, 4.0 + Line * 30.0)),
			LeftTopTexts[Line],
			0,
			LeftTopTexts[Line].Len(),
			FontInfo,
			ESlateDrawEffect::None,
			FColor(0x50, 0x50, 0x50)
			);
	}
	
	return LayerId;
}
void SQuestNodeGraphPanel::OnArrangeChildren(const FGeometry& AllottedGeometry,
	FArrangedChildren& ArrangedChildren) const
{
	for(int Index = 0 ; Index < Children.Num() ; Index++)
	{
		if(!Children[Index].IsRenderable(RenderOffset, AllottedGeometry.Size)) continue;
		ArrangedChildren.AddWidget(EVisibility::Visible, AllottedGeometry.MakeChild(
			Children[Index].GetWidget(),
			Children[Index].GetPosition() - RenderOffset,
			Children[Index].GetSize()
		));
	}
}
#pragma endregion 

#pragma region Event Handler
FReply SQuestNodeGraphPanel::OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FQuestAssetEditor::Listener.Get()->OnZoomMultiplierChanged.Broadcast(MouseEvent.GetWheelDelta());
	return FReply::Handled();
}
FReply SQuestNodeGraphPanel::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FQuestAssetEditor::Listener.Get()->OnKeyDown.Broadcast(this, InKeyEvent.GetKey(), InKeyEvent.IsControlDown(), InKeyEvent.IsAltDown(), InKeyEvent.IsShiftDown());
	return FReply::Handled();
}
void SQuestNodeGraphPanel::OnNewQuest(UQuestInfo* NewQuest)
{
	FPanelSlot::FSlotArguments QuestChild = FPanelSlot::FSlotArguments(
		TPanelChildren<FPanelSlot>::FScopedWidgetSlotArguments{
			MakeUnique<FPanelSlot>(), Children, INDEX_NONE
		}
	);
	QuestChild.AttachWidget(SNew(SQuestNode).Quest(NewQuest));
	Children.AddSlot(MoveTemp(QuestChild));
}
#pragma endregion

#pragma region Paint Support
FSlateFontInfo SQuestNodeGraphPanel::GetLTFont(const float Size)
{
	FSlateFontInfo FontInfo;
	FontInfo.CompositeFont = FCoreStyle::GetDefaultFont();
	FontInfo.Size = Size;
	return FontInfo;
}
#pragma endregion 
