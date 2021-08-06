#pragma once

#include "IFWnd.h"

class CIFEquipment : public CIFWnd
{
public:
	char pad_0x036C[0x2354]; //0x036C
    class CSOItem* GetEquipmentObjectBySlot(BYTE SlotIndex);
}; //Size=0x26C0