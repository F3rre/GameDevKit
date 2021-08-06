#pragma once
#include <Windows.h>
class CSOItem // size = 464, approved by CIFExchange::ctor
{
public:
    char pad_0000[464]; //0x0000
    UINT ObjID; //0x0034
    char pad_0038[84]; //0x0038
    BYTE OptLevel; //0x008C
    char pad_008D[11]; //0x008D
    int CurrDurability; //0x0098
    char pad_009C[68]; //0x009C
    int PhyAtkPwrMax; //0x00E0
    int PhyAtkPwrMin; //0x00E4
    int MagAtkPwrMax; //0x00E8
    int MagAtkPwrMin; //0x00EC
    int BlockingRateValue; //0x00F0
    int MaxDurability; //0x00F4
    float PhyDefPwrValue; //0x00F8
    int ParryRateValue; //0x00FC
    float PhyAbsorption; //0x0100
    char pad_0104[4]; //0x0104
    int CriticalValue; //0x0108
    float MagDefPwrValue; //0x010C
    float MagAbsorption; //0x0110
    float PhyReinforcementMin; //0x0114
    float PhyReinforcementMax; //0x0118
    float MagReinforcementMin; //0x011C
    float MagReinforcementMax; //0x0120
    float PhyReinforcementValue; //0x0124
    float MagReinforcementValue; //0x0128
    char pad_012C[4]; //0x012C
    int AttackRateValue; //0x0130

    class ObjectData* GetObjectData();

}; //Size: 0x01D0
