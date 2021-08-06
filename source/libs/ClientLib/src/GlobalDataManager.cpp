#include "GlobalDataManager.h"



undefined4 CGlobalDataManager::FUN_008cbac0(int a1) {
    return reinterpret_cast<undefined4 (__thiscall *)(CGlobalDataManager *, int)>(0x008cbac0)(this, a1);
}
void CGlobalDataManager::TEMPLE_93AEF0(unsigned char flag, unsigned char templething)
{
    reinterpret_cast<void(__thiscall*)(CGlobalDataManager*, unsigned char, unsigned char)>(0x0093AEF0)(this, flag, templething);
}

void CGlobalDataManager::TEMPLE_93ADB0(int a1, unsigned char uniontype)
{
    reinterpret_cast<void(__thiscall*)(CGlobalDataManager*, int, unsigned char)>(0x0093AEF0)(this, a1, uniontype);
}

void CGlobalDataManager::GetWorldCodeByID(std::wstring* code, unsigned short ID)
{
    reinterpret_cast<void(__thiscall*)(CGlobalDataManager*, std::wstring*, unsigned short)>(0x009399B0)(this, code, ID);
}

CharData* CGlobalDataManager::GetCharData(unsigned int ObjID)
{
    return reinterpret_cast<CharData*(__thiscall*)(CGlobalDataManager*, unsigned int)>(0x0093F630)(this, ObjID);
}

CGlobalDataManager* CGlobalDataManager::Get(void)
{
    return reinterpret_cast<CGlobalDataManager*>(0xEEDF08);
}

ObjectData* CGlobalDataManager::GetObjectData(unsigned int ObjID)
{
    return reinterpret_cast<ObjectData * (__thiscall*)(CGlobalDataManager*, unsigned int)>(0x0093F710)(this, ObjID);
}