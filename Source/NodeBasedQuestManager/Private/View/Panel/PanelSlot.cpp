#include "View/Panel/PanelSlot.h"

bool FPanelSlot::IsRenderable(FVector2D ScreenOffset, FVector2D ScreenSize) const
{
	FVector2D ScreenLB = ScreenOffset - ScreenSize / 2;
	FVector2D Size = GetSize();
	if(Position.X + Size.X < ScreenLB.X || ScreenLB.X + ScreenSize.X < Position.X) return false;
	if(Position.Y + Size.Y < ScreenLB.Y || ScreenLB.Y + ScreenSize.Y < Position.Y) return false;
	return true;
}

FVector2D FPanelSlot::GetPosition() const
{
	return Position + GetSize() / 2;
}

FVector2D FPanelSlot::GetSize() const
{
	if(const TSharedPtr<SLeafWidget> LeafChild = StaticCastSharedPtr<SLeafWidget>(GetWidget().ToSharedPtr()))
		return LeafChild->GetDesiredSize();
	return FVector2D::Zero();
}

void FPanelSlot::Construct(const FChildren& SlotOwner, FSlotArguments&& InArgs)
{
	if(InArgs._Position.IsSet())
	{
		Position = InArgs._Position.Get();
	}
}
