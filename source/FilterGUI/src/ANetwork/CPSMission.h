#pragma once
#include "ClientNet/MsgStreamBuffer.h"
#include <GInterface.h>
#include <ICPlayer.h>
#include "PSilkroad.h"
#include <memory\hook.h>
#include <Test/Test.h>
#include <ghidra/undefined.h>
#include "NetProcessIn.h"

#define GET_OWN_GAME_ID() \
	MEMUTIL_READ_BY_PTR_OFFSET(g_pCICPlayer, 0xF8, DWORD)

class CPSMission : public CPSilkroad {
public:
	bool OnServerPacketRecv(class CMsgStreamBuffer* MsgBuffer);
	wchar_t* Convert(std::n_string name);
	static bool char_is_ready;
	static BYTE CurHawn;
	static bool Gui_GrantName;
	static bool Gui_UniqueHistory;
	static bool Gui_CustomTitle;
	static bool Gui_SwitchTitle;
	static bool Gui_EventTimer;
	static bool Gui_CharacterLock;
	static bool Gui_CustomRank;
	static bool Gui_ColorsRender;
	static bool Gui_GlobalColors;

    wchar_t *Convert(const char *p);
};

//class CPSVersionCheck : public CPSilkroad
//{
//public:
//	bool OnServerPacketRecv(class CMsgStreamBuffer* msg);
//};

class CPSTitle : public CPSilkroad
{
public:
	bool OnServerPacketRecv(class CMsgStreamBuffer* MsgBuffer);
	wchar_t* Convert(std::n_string name);
	bool OnCreateTMEP(long ln);
};

class CPSCharacterSelect : public CPSilkroad
{
public:
	bool OnServerPacketRecv(class CMsgStreamBuffer* MsgBuffer);
	wchar_t* Convert(std::n_string name);

};

class CIFTargetWindow : public CIFWnd
{
public:
	CIFWnd* MobWindow();
};

#pragma once
#include <iostream>

class CInterfaceNetSender
{
private:
	char pad_0000[8504]; //0x0000
	unsigned int GuildSkillPoints; //0x2138
	char pad_2140[8]; //0x213C
	std::wstring GuildName; //0x2140
	std::wstring CharName; //0x2160

public:
	void DonateGuildPoints(unsigned int GP);
};