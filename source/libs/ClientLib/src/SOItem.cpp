#include "SOItem.h"
#include "ObjectData.h"

ObjectData* CSOItem::GetObjectData(void)
{
    return reinterpret_cast<ObjectData*(__thiscall*)(CSOItem*)>(0x008BA440)(this);
}