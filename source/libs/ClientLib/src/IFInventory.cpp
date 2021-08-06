#include "IFInventory.h"
#include "SOItem.h"

CSOItem* CIFInventory::GetItemBySlot(BYTE SlotIndex)
{
	return reinterpret_cast<CSOItem*(__thiscall*)(CIFInventory*, BYTE)>(0x006B3E50)(this, SlotIndex);
}

CSOItem* CIFInventory::GetItemBySlot(int slotId) {
	return reinterpret_cast<CSOItem * (__thiscall*)(CIFInventory*, int)>(0x6b3e50)(this, slotId);
}
