#pragma once

class FPanelSlot : public TSlotBase<FPanelSlot>
{
public:
	
	SLATE_SLOT_BEGIN_ARGS(FPanelSlot, TSlotBase<FPanelSlot>)
		SLATE_ATTRIBUTE(FVector2D, Position)
	SLATE_SLOT_END_ARGS()
	
	FPanelSlot() : Position(0, 0) {}
	void Construct(const FChildren& SlotOwner, FSlotArguments&& InArgs);
	bool IsRenderable(FVector2D ScreenOffset, FVector2D ScreenSize) const;
	FVector2D GetPosition() const;
	FVector2D GetSize() const;

private:
	FVector2D Position;
};
