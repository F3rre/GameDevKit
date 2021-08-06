#include "CPSMission.h"
#include <GInterface.h>
#include <BSLib\multiBYTE.h>
#include <GlobalDataManager.h>
#include <TextStringManager.h>
#include <PSOuterInterface.h>
#include "BSLib/BSLib.h"
#include <Game.h>
#include "SwitchTitles/IFBFilterTitles.h"
#include <ObjectData.h>
#include <sstream>
#include <string>
#include <algorithm>
#include <MainMenu/IFBFilterMainMenu.h>
#include <DiscordRichPresence/DiscordManager.h>
#include <Hwid Manager/HawidManager.h>
#include <Hwid Manager/base64.h>
#include <Hwid Manager/md5.h>

bool CPSMission::char_is_ready;
BYTE CPSMission::CurHawn = -1;

bool CPSMission::Gui_GrantName;
bool CPSMission::Gui_UniqueHistory;
bool CPSMission::Gui_CustomTitle;
bool CPSMission::Gui_SwitchTitle;
bool CPSMission::Gui_EventTimer;
bool CPSMission::Gui_CharacterLock;
bool CPSMission::Gui_CustomRank;
bool CPSMission::Gui_ColorsRender;
bool CPSMission::Gui_GlobalColors;

bool CPSMission::OnServerPacketRecv(CMsgStreamBuffer* msg) {

    switch (msg->msgid())
    {
		// SERVER_ENVIROMENT_CELESTIAL_POSITION
        case 0x3020: {      
			if (g_pCICPlayer) {
			BYTE JOBTYPE = g_pCICPlayer->GetJobType();
			BYTE CURLEVEL = g_pCICPlayer->m_level;
			uregion CurRegion = g_pCICPlayer->GetRegion();
			USHORT RegionID = CurRegion.r;

			CMsgStreamBuffer buf(0x3560);
			buf << JOBTYPE;
			buf << CURLEVEL;
			buf << RegionID;
			SendMsg(buf);
		}
		// Called after every teleport
		DiscordManager::Instance().UpdateState(GAME_STATE::IN_GAME);
		msg->m_currentReadBytes = 0;
		}
            break;
		// SERVER_ENTITY_LEVEL_UP
        case 0x3054:{
            uint32_t uniqueID; *msg >> uniqueID;

            // Check if my character level up
            if (uniqueID == GET_OWN_GAME_ID())
            {
                DiscordManager::Instance().UpdateState();
            }
            msg->m_currentReadBytes = 0;
        }
            break;
		// SERVER_ENTITY_MOVEMENT
        case 0xB021: {
            uint32_t uniqueID; *msg >> uniqueID;
            // Check my character movements
            if (uniqueID == GET_OWN_GAME_ID())
            {
                // Check if new zone has been triggered
                if (DiscordManager::Instance().m_IsRegionChange)
                {
                    DiscordManager::Instance(). m_IsRegionChange = false;
                    DiscordManager::Instance().UpdateState();
                }
                // Read packet
                byte hasCoordinate; *msg >> hasCoordinate;
                if (hasCoordinate == 1)
                {
                    short newRegionID; *msg >> newRegionID;
                    // Check if the region will be changed in the next step
                    if (g_pCICPlayer->GetRegion().r != newRegionID)
                    {
                        // We guess the next movement will be from a new region
                        DiscordManager::Instance(). m_IsRegionChange = true;
                    }
                }
            }
            msg->m_currentReadBytes = 0;
        }
            break;
		// SERVER_GUILD_DATA_END
        case 0x34B4: {
            // Updates guild name after client reading guild data
            DiscordManager::Instance().UpdateState();
        }
        break;
    }
	/// ORG PACKETS
	if (msg->msgid() == 0x3305)
	{
		//if (g_pCICPlayer) {
		//	BYTE JOBTYPE = g_pCICPlayer->GetJobType();
		//	BYTE CURLEVEL = g_pCICPlayer->m_level;
		//	uregion CurRegion = g_pCICPlayer->GetRegion();

		//	CMsgStreamBuffer buf(0x3560);
		//	buf << JOBTYPE;
		//	buf << CURLEVEL;
		//	buf << CurRegion.r;
		//	SendMsg(buf);
		//}
		if (!CPSMission::char_is_ready)
		{
			if (g_pCICPlayer)
			{
				wchar_t buffer1[45];
				std::wstring mymsg1;
				swprintf_s(buffer1, sizeof(buffer1), L"Welcome back %s", g_pCICPlayer->GetCharName().c_str());
				mymsg1.assign(buffer1);
				g_pCGInterface->ShowLogMessage(D3DCOLOR_RGBA(0x64, 0xc7, 0xff, 255), mymsg1.c_str());
				CPSMission::char_is_ready = true;
				CIFMainMenu::CharLockGUI->ResetPosition();
				CIFMainMenu::CharLockGUI->ShowGWnd(true);
			}
		}

		msg->m_currentReadBytes = 0;
	}
	if (msg->msgid() == 0x30DF)
	{
		unsigned int ID;
		BYTE Hawn;
		*msg >> ID >> Hawn;

		if (ID == GET_OWN_GAME_ID())
		{
			CurHawn = Hawn;
		}
		msg->m_currentReadBytes = 0;
	}
	if (msg->msgid() == 0x300c)
	{
		unsigned short type;
		*msg >> type;
		CIFUniqueLog::UniqueLogstru newuq = CIFUniqueLog::UniqueLogstru();
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, sizeof(buffer), "%I:%M %p", timeinfo);
		std::string str(buffer);

		switch (type)
		{
		case 0x0C05: //Unique Spawn
		{
			unsigned int UniqueID;
			*msg >> UniqueID;
			if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
			{
				if (CharData* uqdata = g_datamanager->GetCharData(UniqueID))
				{
					std::wstring UniqueName = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
					// std::wcout <<L"Spawn " << UniqueName << L"\n" << std::endl;

					if (CIFUniqueLog::UqListContains(UniqueName.c_str()))
					{
						for (int i = 0; i < CIFUniqueLog::UQlist.size(); ++i)
						{
							if (wcscmp(CIFUniqueLog::UQlist[i].UqName.c_str(), UniqueName.c_str()) == 0)
							{
								CIFUniqueLog::UQlist[i].LifeState = L"Alive";
								CIFUniqueLog::UQlist[i].Killer = L"<NONE>";
								CIFUniqueLog::UQlist[i].Time = TO_WSTRING(str).c_str();
                                CIFMainMenu::UniqueLogGUI->UpdateLog();
								break;
							}
						}
					}
					else
					{
						if (CIFUniqueLog::UQlist.size() > 0)
						{
							if (CIFMainMenu::UniqueLogGUI->IsPageFull(CIFUniqueLog::UQlist.back().Pagenum, 39))
							{
								newuq.Pagenum = CIFUniqueLog::UQlist.back().Pagenum + 1;
								newuq.LineNum = 30;
							}
							else
							{
								newuq.Pagenum = CIFUniqueLog::UQlist.back().Pagenum;
								newuq.LineNum = CIFUniqueLog::UQlist.back().LineNum + 1;
							}

							newuq.LifeState = L"Alive";
							newuq.Killer = L"<NONE>";
							newuq.Time = TO_WSTRING(str).c_str();
							newuq.UqName = UniqueName.c_str();
							CIFUniqueLog::UQlist.push_back(newuq);
                            CIFMainMenu::UniqueLogGUI->UpdateLog();
						}
						else
						{
							newuq.Pagenum = 1;
							newuq.LineNum = 30;
							newuq.LifeState = L"Alive";
							newuq.Killer = L"<NONE>";
							newuq.Time = TO_WSTRING(str).c_str();
							newuq.UqName = UniqueName.c_str();
							CIFUniqueLog::UQlist.push_back(newuq);
                            CIFMainMenu::UniqueLogGUI->UpdateLog();
						}
					}
				}
			}
			break;

		}

		case 0x0C06: //Unique Kill
		{
			unsigned int UniqueID;
			*msg >> UniqueID;
			std::n_string KillerName;
			*msg >> KillerName;
			if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
			{
				if (CharData* uqdata = g_datamanager->GetCharData(UniqueID))
				{
					std::wstring UniqueName = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
					//std::wcout << L"Kill " << UniqueName << L"\n" << std::endl;

					if (CIFUniqueLog::UqListContains(UniqueName.c_str()))
					{
						for (int i = 0; i < CIFUniqueLog::UQlist.size(); ++i)
						{
							if (wcscmp(CIFUniqueLog::UQlist[i].UqName.c_str(), UniqueName.c_str()) == 0)
							{
								CIFUniqueLog::UQlist[i].LifeState = L"Killed";
								CIFUniqueLog::UQlist[i].Killer = TO_WSTRING(KillerName).c_str();
								CIFUniqueLog::UQlist[i].Time = TO_WSTRING(str).c_str();
                                CIFMainMenu::UniqueLogGUI->UpdateLog();
								break;
							}
						}
					}
					else
					{
						if (CIFUniqueLog::UQlist.size() > 0)
						{
							if (CIFMainMenu::UniqueLogGUI->IsPageFull(CIFUniqueLog::UQlist.back().Pagenum, 39))
							{
								newuq.Pagenum = CIFUniqueLog::UQlist.back().Pagenum + 1;
								newuq.LineNum = 30;
							}
							else
							{
								newuq.Pagenum = CIFUniqueLog::UQlist.back().Pagenum;
								newuq.LineNum = CIFUniqueLog::UQlist.back().LineNum + 1;
							}

							newuq.LifeState = L"Killed";
							newuq.Killer = TO_WSTRING(KillerName).c_str();
							newuq.Time = TO_WSTRING(str).c_str();
							newuq.UqName = UniqueName.c_str();
							CIFUniqueLog::UQlist.push_back(newuq);
                            CIFMainMenu::UniqueLogGUI->UpdateLog();
						}
						else
						{
							newuq.Pagenum = 1;
							newuq.LineNum = 30;
							newuq.LifeState = L"Killed";
							newuq.Killer = TO_WSTRING(KillerName).c_str();
							newuq.Time = TO_WSTRING(str).c_str();
							newuq.UqName = UniqueName.c_str();
							CIFUniqueLog::UQlist.push_back(newuq);
                            CIFMainMenu::UniqueLogGUI->UpdateLog();
						}
					}
				}
			}
			break;
		}
		}
		msg->m_currentReadBytes = 0;
	}
	///CUSTOM PACKETS
	//unique log
	if (msg->msgid() == 0x5100)
	{
		BYTE sCount;
		BYTE PageNum;
		BYTE No;
		int DBID;
		std::n_string State;
		std::n_string Killer;
		std::n_string Time;
		*msg >> sCount;
		BYTE i = 0;

		//CIFUniqueLog* Log = g_pCGInterface->m_IRM.GetResObj<CIFUniqueLog>(UniqueLog, 1);
		CIFUniqueLog::UQlist.clear();

		while (i < sCount && sCount > 0)
		{
			i++;

			*msg >> PageNum >> No >> DBID >> State >> Killer >> Time;

			std::wstring UqName = L"<NONE>";
			if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
			{
				if (CharData* uqdata = g_datamanager->GetCharData(DBID))
				{
					UqName = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
				}
			}

			CIFUniqueLog::UniqueLogstru uq = CIFUniqueLog::UniqueLogstru();
			uq.Pagenum = PageNum;
			uq.LineNum = No;
			uq.LifeState = TO_WSTRING(State).c_str();
			uq.Killer = TO_WSTRING(Killer).c_str();
			uq.UqName = UqName.c_str();
			uq.Time = TO_WSTRING(Time).c_str();
			CIFUniqueLog::UQlist.push_back(uq);
		}

        CIFMainMenu::UniqueLogGUI->UpdateLog();

		msg->FlushRemaining();
		//msg->m_currentReadBytes = 0;
	}
	//show forms
	if (msg->msgid() == 0x5101) {


		int FormID = 0;
		bool ShowHide = 0;
		*msg >> FormID >> ShowHide;

		switch (FormID)
		{
		case CharLock:
		{
			if (ShowHide == 0) {
				CIFMainMenu::CharLockGUI->Clear();
				CIFMainMenu::CharLockGUI->ShowGWnd(false);
			}
		}
		case DMGMeter:
		{
			if (ShowHide == 0) {
				CIFMainMenu::DmgMeterGui->Clear();
				CIFMainMenu::DmgMeterGui->ShowGWnd(false);
			}
		}
		break;
		case FtwKillsCounter:
		{
			if (ShowHide == 0) {
				CIFMainMenu::FtwCunterGUI->Clear();
				CIFMainMenu::FtwCunterGUI->ShowGWnd(false);
			}
		}
		break;
		case SurvKillsCounter:
		{
			if (ShowHide == 0) {
				CIFMainMenu::SurvGuiGUI->Clear();
				CIFMainMenu::SurvGuiGUI->ShowGWnd(false);
			}
		}
		break;
		}

		msg->FlushRemaining();
	}
	//notices
	if (msg->msgid() == 0x5102)
	{
		/*
		Notice Types
		1- Notice Red?
		2- Blue Noitfy
		3- Green Quest huh?
		4- Normal System Msg Yellow one.
		5- Guide System Msg seems blue?
		6- Colored System Msg thx flo <3
		7- Colored Chat Msg like PM,ALL CHAT,GLOBAL
		*/
		BYTE Type;
		std::n_string notice;

		*msg >> Type >> notice;

		if (Type == 1)
		{
			g_pCGInterface->ShowMessage_Notice(Convert(notice));
		}

		if (Type == 2)
		{
			g_pCGInterface->ShowMessage_Warning(Convert(notice));
		}

		if (Type == 3)
		{
			g_pCGInterface->ShowMessage_Quest(Convert(notice));
		}

		if (Type == 4)
		{
			CIFMainMenu::PurbleNoitfy->ShowMessage(Convert(notice));
		}

		if (Type == 5)
		{
			CIFMainMenu::PurbleNoitfy->ShowMessage(Convert(notice));
		}

		if (Type == 6)
		{
			g_pCGInterface->WriteSystemMessage(SYSLOG_NONE, Convert(notice));
		}

		if (Type == 7)
		{
			g_pCGInterface->WriteSystemMessage(SYSLOG_GUIDE, Convert(notice));
		}

		if (Type == 8)
		{
			int Color;
			*msg >> Color;
			g_pCGInterface->ShowLogMessage(Color, Convert(notice));
		}

		if (Type == 9)
		{
			//std::n_string Key;
			//UINT Color;
			//*msg >> Color >> Key;
			//WriteToChat(CHAT_Ask, L"", Convert(notice), 0, Color, Convert(Key));

			std::n_string Key;
			UINT Color;
			*msg >> Color >> Key;

			std::n_wstring local_64;
			local_64 = L"(";
			local_64 += Convert(Key);
			local_64 += L"):";

			std::n_wstring local_80 = local_64 + Convert(notice);

			g_pCGInterface->FUN_00777c30(CHAT_Ask, local_80.c_str(), Color, 1);

		}

		if (Type == 10)
		{
			std::n_string Key;
			*msg >> Key;

			wchar_t buffer1[255];
			std::wstring Name = g_CTextStringManager->GetStringByNameStrID(&TO_WSTRING(Key))->c_str();

			if (Name.empty())
				Name = L"<UnKnown Item>";

			swprintf_s(buffer1, sizeof(buffer1), TO_WSTRING(notice).c_str(), Name.c_str());
			std::n_wstring strmsg;
			strmsg.assign(buffer1);

			CIFMainMenu::PurbleNoitfy->ShowMessage(strmsg.c_str());
		}

		msg->FlushRemaining();
	}
	//DMG METER
	if (msg->msgid() == 0x5103)
	{
		//BYTE sCount;
		//std::n_string Name;
		std::n_string DMG;
		int PlayerID;
		//int DMG;
		int MobID;
		int RecordCount;
		std::wstring UniqueName = L"";
		*msg >> MobID >> RecordCount;
		BYTE i = 0;

		if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
		{
			if (CharData* uqdata = g_datamanager->GetCharData(MobID))
			{
				UniqueName = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
			}
		}

        CIFMainMenu::DmgMeterGui->Clear();
        CIFMainMenu::DmgMeterGui->m_title->SetText(UniqueName.c_str());

		//get the target mob
		CIFTargetWindow* target = g_pCGInterface->m_IRM.GetResObj<CIFTargetWindow>(16, 1);
		CIFWnd* MOB = target->MobWindow();
		//show the dmg meter
        CIFMainMenu::DmgMeterGui->Clear();
        CIFMainMenu::DmgMeterGui->ShowGWnd(true);
		int x = MOB->GetPos().x * 2 - 150;
        CIFMainMenu::DmgMeterGui->MoveGWnd(x, MOB->GetPos().y);

		while (i < RecordCount && RecordCount > 0)
		{
			i++;
			*msg >> PlayerID >> DMG;
			CICharactor* Char = 0;
			Char = GetCharacterObjectByID_MAYBE(PlayerID);
			if (Char != 0)
			{
                CIFMainMenu::DmgMeterGui->WriteLine(i, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());

                //switch (i)
				//{
				//case 1:
					//break;
				//case 2:
                //    CIFMainMenu::DmgMeterGui->WriteLine(2, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
				//	break;
				//case 3:
               //     CIFMainMenu::DmgMeterGui->WriteLine(3, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
				//	break;
				//case 4:
               //     CIFMainMenu::DmgMeterGui->WriteLine(4, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
				//	break;
				//case 5:
                 //   CIFMainMenu::DmgMeterGui->WriteLine(5, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
				//	break;
				//case 6:
               //     CIFMainMenu::DmgMeterGui->WriteLine(6, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
				//	break;
				//case 7:
               //     CIFMainMenu::DmgMeterGui->WriteLine(7, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
				//	break;
				//case 8:
                //    CIFMainMenu::DmgMeterGui->WriteLine(8, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
				//	break;
				//}
			}
		}

		msg->FlushRemaining();
	}
	//SWITCH TITLE
	if (msg->msgid() == 0x5104)
	{
		BYTE count;
		BYTE ID;
		std::n_string Name;
		int Color;
		*msg >> count;
		BYTE i = 0;
        CIFMainMenu::SwitchTitleGUI->m_textbox->m_LinesOfHistory = count;

		while (i < count && count > 0)
		{
			i++;
			*msg >> ID >> Name >> Color;

			wchar_t buffer1[255];
			std::wstring TitleName = g_CTextStringManager->GetStringTextByCode(Convert(Name))->c_str();

			//std::wcout << "TitleName " << TitleName << std::endl;

			if (TitleName.empty())
				TitleName = L"<NULL>";

			swprintf_s(buffer1, sizeof(buffer1), L"%d. %s", i, TitleName.c_str());
			std::n_wstring strmsg;
			strmsg.assign(buffer1);
            CIFMainMenu::SwitchTitleGUI->AddTitle(strmsg.c_str(), ID, Color);
            CIFMainMenu::SwitchTitleGUI->m_textbox->sub_64F8A0(strmsg, 0, Color, Color, -1, 0, 0);
		}

		msg->FlushRemaining();
	}
	//custom title info
	if (msg->msgid() == 0x5105)
	{
		int count;
		std::n_string Name;
		std::n_string Title;
		*msg >> count;
		int i = 0;

		while (i < count && count > 0)
		{
			i++;
			*msg >> Name >> Title;

			g_pCICPlayer->AddCustomTitle(TO_NWSTRING(Name).c_str(), TO_NWSTRING(Title).c_str());
		}

		msg->FlushRemaining();
	}
	//Add Custom title
	if (msg->msgid() == 0x5106)
	{
		std::n_string Name;
		std::n_string Title;
		*msg >> Name >> Title;

		g_pCICPlayer->AddCustomTitle(TO_NWSTRING(Name).c_str(), TO_NWSTRING(Title).c_str());
		msg->FlushRemaining();
	}
	//Remove Custom title
	if (msg->msgid() == 0x5107)
	{
		std::n_string Name, OrgTitle;
		*msg >> Name >> OrgTitle;
		g_pCICPlayer->RemoveCustomTitle(TO_NWSTRING(Name).c_str());

		//refresh?
		CLASSLINK_LOOP_BEGIN(CICUser)
			if (wcscmp(obj->GetName().c_str(), TO_NWSTRING(Name).c_str()) == 0)
				obj->ChangeTitle(g_CTextStringManager->GetString(Convert(OrgTitle))->c_str());
		CLASSLINK_LOOP_END(CICUser)
			msg->FlushRemaining();
	}
	//Title Color info
	if (msg->msgid() == 0x5108)
	{
		int count;
		std::n_string Name;
		int Color;
		*msg >> count;
		int i = 0;
		while (i < count && count > 0)
		{
			i++;
			*msg >> Name >> Color;

			if (Color != 0)
				g_pCICPlayer->AddTitleColor(TO_NWSTRING(Name).c_str(), Color);
			else
				g_pCICPlayer->RemoveTitleColor(TO_NWSTRING(Name).c_str());
		}

		msg->FlushRemaining();
	}
	//Add Title Color
	if (msg->msgid() == 0x5109)
	{
		std::n_string Name;
		int Color;
		*msg >> Name >> Color;

		if (Color != 0)
			g_pCICPlayer->AddTitleColor(TO_NWSTRING(Name).c_str(), Color);
		else
			g_pCICPlayer->RemoveTitleColor(TO_NWSTRING(Name).c_str());

		msg->FlushRemaining();
	}
	//Remove Title Color
	if (msg->msgid() == 0x5110)
	{
		std::n_string Name;
		*msg >> Name;

		g_pCICPlayer->RemoveTitleColor(TO_NWSTRING(Name).c_str());

		//refresh?
		CLASSLINK_LOOP_BEGIN(CICUser)
			if (wcscmp(obj->GetName().c_str(), TO_NWSTRING(Name).c_str()) == 0)
				obj->ChangeTitleColor(0xFFE65B);
		CLASSLINK_LOOP_END(CICUser)

			msg->FlushRemaining();
	}
	//Charname Color Info
	if (msg->msgid() == 0x5111)
	{
		int count;
		std::n_string Name;
		int Color;
		*msg >> count;
		int i = 0;

		while (i < count && count > 0)
		{
			i++;
			*msg >> Name >> Color;

			g_pCICPlayer->AddCharColor(TO_NWSTRING(Name).c_str(), Color);
		}

		msg->FlushRemaining();
	}
	//Add Charname Color
	if (msg->msgid() == 0x5112)
	{
		std::n_string Name;
		int Color;
		*msg >> Name >> Color;

		g_pCICPlayer->AddCharColor(TO_NWSTRING(Name).c_str(), Color);
		msg->FlushRemaining();
	}
	//Remove Charname Color
	if (msg->msgid() == 0x5113)
	{
		std::n_string Name;
		*msg >> Name;

		g_pCICPlayer->RemoveCharColor(TO_NWSTRING(Name).c_str());

		//refresh?
		CLASSLINK_LOOP_BEGIN(CICUser)
			if (wcscmp(obj->GetName().c_str(), TO_NWSTRING(Name).c_str()) == 0)
				obj->ChangeNameColor(0xFFFFFFFE);
		CLASSLINK_LOOP_END(CICUser)

			msg->FlushRemaining();
	}
	//GUI SETTING
	if (msg->msgid() == 0x5114)
	{
		bool GUIGrantName;
		bool GUIUniqueHistory;
		bool GUICustomTitle;
		bool GUISwitchTitle;
		bool GUICharacterLock;
		bool GUIEventTimer;
		bool GUIRank;
		bool GUIRender;
		bool GUIGlobalColor;

		*msg >>
			GUIGrantName >> GUIUniqueHistory >>
			GUICustomTitle >> GUISwitchTitle  >>
			GUICharacterLock >> GUIEventTimer>>
			GUIRank >> GUIRender >> GUIGlobalColor;

		CPSMission::Gui_GrantName = GUIGrantName;
		CPSMission::Gui_UniqueHistory = GUIUniqueHistory;
		CPSMission::Gui_CustomTitle = GUICustomTitle;
		CPSMission::Gui_SwitchTitle = GUISwitchTitle;
		CPSMission::Gui_CharacterLock = GUICharacterLock;
		CPSMission::Gui_EventTimer = GUIEventTimer;
		CPSMission::Gui_CustomRank = GUIRank;
		CPSMission::Gui_ColorsRender = GUIRender;
		CPSMission::Gui_GlobalColors = GUIGlobalColor;

		msg->FlushRemaining();
	}
	//Custom name rank info
	if (msg->msgid() == 0x5115)
	{
		int count;
		std::n_string Name;
		std::n_string Rank;
		*msg >> count;
		int i = 0;

		while (i < count && count > 0)
		{
			i++;
			*msg >> Name >> Rank;

			g_pCICPlayer->AddCustomNameRank(TO_NWSTRING(Name).c_str(), TO_NWSTRING(Rank).c_str());
		}

		msg->FlushRemaining();
	}
	//Add Custom rank
	if (msg->msgid() == 0x5116)
	{
		std::n_string Name;
		std::n_string Rank;
		*msg >> Name >> Rank;

		g_pCICPlayer->AddCustomNameRank(TO_NWSTRING(Name).c_str(), TO_NWSTRING(Rank).c_str());
		msg->FlushRemaining();
	}
	//Remove Custom rank
	if (msg->msgid() == 0x5117)
	{
		std::n_string Name;
		*msg >> Name;
		g_pCICPlayer->RemoveCustomNameRank(TO_NWSTRING(Name).c_str());

		//refresh?
		CLASSLINK_LOOP_BEGIN(CICUser)
			if (wcscmp(obj->GetName().c_str(), TO_NWSTRING(Name).c_str()) == 0)
				obj->ChangeName(TO_NWSTRING(Name).c_str());
		CLASSLINK_LOOP_END(CICUser)

			msg->FlushRemaining();
	}
	//Custom name info
	if (msg->msgid() == 0x5118)
	{
		int count;
		std::n_string Name;
		std::n_string Rank;
		*msg >> count;
		int i = 0;

		while (i < count && count > 0)
		{
			i++;
			*msg >> Name >> Rank;

			g_pCICPlayer->AddCustomName(TO_NWSTRING(Name).c_str(), TO_NWSTRING(Rank).c_str());
		}

		msg->FlushRemaining();
	}
	//Add Custom name
	if (msg->msgid() == 0x5119)
	{
		std::n_string Name;
		std::n_string Rank;
		*msg >> Name >> Rank;

		g_pCICPlayer->AddCustomName(TO_NWSTRING(Name).c_str(), TO_NWSTRING(Rank).c_str());
		msg->FlushRemaining();
	}
	//Remove Custom name
	if (msg->msgid() == 0x5120)
	{
		

		std::n_string Name;
		*msg >> Name;
		g_pCICPlayer->RemoveCustomName(TO_NWSTRING(Name).c_str());

		//refresh?
		CLASSLINK_LOOP_BEGIN(CICUser)
			if (wcscmp(obj->GetName().c_str(), TO_NWSTRING(Name).c_str()) == 0)
				obj->ChangeName(TO_NWSTRING(Name).c_str());
		CLASSLINK_LOOP_END(CICUser)

			msg->FlushRemaining();
	}
	//FORTRESS KILLS
	if (msg->msgid() == 0x5122)
	{
		BYTE sCount;
		std::n_string GuildName;
		std::n_string Kills;
		*msg >> sCount;
		BYTE i = 0;

        CIFMainMenu::FtwCunterGUI->Clear();

		while (i < sCount && sCount > 0)
		{
			i++;
			*msg >> GuildName >> Kills;
            CIFMainMenu::FtwCunterGUI->WriteLine(i, TO_WSTRING(GuildName).c_str(), TO_WSTRING(Kills).c_str());
			//std::wcout << "Guild " << TO_WSTRING(GuildName).c_str() << " Kills " << TO_WSTRING(Kills).c_str() << std::endl;
		}

		CIFMainMenu::FtwCunterGUI->ResetPosition();
		CIFMainMenu::FtwCunterGUI->ShowGWnd(true);

		msg->FlushRemaining();
	}
	// SURVIVAL KILLS
	if (msg->msgid() == 0x5123)
    {
		BYTE sCount;
		std::n_string Player;
		std::n_string Kills;
		*msg >> sCount;
		BYTE i = 0;

        CIFMainMenu::SurvGuiGUI->Clear();

		while (i < sCount && sCount > 0)
		{
			i++;
			*msg >> Player >> Kills;
            CIFMainMenu::SurvGuiGUI->WriteLine(i, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str());
			//std::wcout << "Player " << TO_WSTRING(Player).c_str() << " Kills " << TO_WSTRING(Kills).c_str() << std::endl;

		}

		CIFMainMenu::SurvGuiGUI->ResetPosition();
		CIFMainMenu::SurvGuiGUI->ShowGWnd(true);

		msg->FlushRemaining();
	}
	//Rank info
	if (msg->msgid() == 0x5124)
	{
		BYTE sCount;
		BYTE RankType;
		BYTE No;
		std::n_string Name;
		std::n_string Guild;
		std::n_string Points;
		*msg >> RankType >> sCount;
		BYTE i = 0;

		if (RankType == 1)//uq rank
		{
			CIFCustomRank::UniquesRankList.clear();
		}
		else if (RankType == 2)//honor rank
		{
			CIFCustomRank::HonorRankList.clear();
		}
		else if (RankType == 3)//pvp rank
		{
			CIFCustomRank::PVPRankList.clear();
		}
		else if (RankType == 4)//Trader rank
		{
			CIFCustomRank::JobTraderRank.clear();
		}
		else if (RankType == 5)//Hunter rank
		{
			CIFCustomRank::JobHunterRank.clear();
		}
		else if (RankType == 6)//Thief rank
		{
			CIFCustomRank::JobThiefRank.clear();
		}
		else if (RankType == 7)//item rank
		{
			CIFCustomRank::CharRankList.clear();
		}
		else if (RankType == 8)//job kills rank
		{
			CIFCustomRank::JobRankList.clear();
		}
		while (i < sCount && sCount > 0)
		{
			i++;

			*msg >> No >> Name >> Guild >> Points;

			CIFCustomRank::RankStruct uqR = CIFCustomRank::RankStruct();
			uqR.LineNum = No;
			uqR.Charname = TO_WSTRING(Name).c_str();
			uqR.Guild = TO_WSTRING(Guild).c_str();
			uqR.Points = TO_WSTRING(Points).c_str();

			if (RankType == 1)//uq rank
			{
				CIFCustomRank::UniquesRankList.push_back(uqR);
			}
			else if (RankType == 2)//honor rank
			{
				CIFCustomRank::HonorRankList.push_back(uqR);
			}
			else if (RankType == 3)//pvp rank
			{
				CIFCustomRank::PVPRankList.push_back(uqR);
			}
			else if (RankType == 4)//Trader rank
			{
				CIFCustomRank::JobTraderRank.push_back(uqR);
			}
			else if (RankType == 5)//Hunter rank
			{
				CIFCustomRank::JobHunterRank.push_back(uqR);
			}
			else if (RankType == 6)//Thief rank
			{
				CIFCustomRank::JobThiefRank.push_back(uqR);
			}
			else if (RankType == 7)//item rank
			{
				CIFCustomRank::CharRankList.push_back(uqR);
			}
			else if (RankType == 8)//job kills rank
			{
				CIFCustomRank::JobRankList.push_back(uqR);
			}
		}

        CIFMainMenu::CustomRankGUI->ActivateTabPage(0);
		msg->FlushRemaining();
	}
	//Event Time List
	if (msg->msgid() == 0x5128)
	{
		BYTE sCount;
		std::n_string EventName;
		std::n_string Day;
		std::n_string Time;
		*msg >> sCount;
		BYTE i = 0;

		CIFEventTime::EventList.clear();
		while (i < sCount && sCount > 0)
		{
			i++;

			*msg >> EventName >> Day >> Time;

			CIFEventTime::EventSetting Evs = CIFEventTime::EventSetting();
			Evs.LineNum = i;
			Evs.EventName = TO_WSTRING(EventName).c_str();
			Evs.Day = TO_WSTRING(Day).c_str();
			Evs.Time = TO_WSTRING(Time).c_str();
			Evs.State = L"";

			CIFEventTime::EventList.push_back(Evs);
		}

		CIFMainMenu::EventTimeGUI->UpdateLog();
		msg->FlushRemaining();
	}

    ////Chest info
    //if (msg->msgid() == 0x5125) {
    //    int sCount;
    //    int No;
    //    int ItemID;
    //    bool RandomStat;
    //    std::n_string Count;
    //    std::n_string From;
    //    std::n_string Date;
    //    std::n_string OptLevel;
    //    *msg >> sCount;
    //    BYTE i = 0;
    //    while (i < sCount && sCount > 0) {
    //        i++;
    //        *msg >> No >> ItemID >> Count >> RandomStat >> OptLevel >> From >> Date;
    //        if (CGlobalDataManager *g_datamanager = CGlobalDataManager::Get())
    //        {
    //            if (ObjectData *uqdata = g_datamanager->GetObjectData(ItemID))
    //            {
    //                CIFPlayerChest::Chest ChestStru = CIFPlayerChest::Chest();
    //                ChestStru.LineNum = No;
    //                ChestStru.NameStrID128 = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
    //                ChestStru.CodeName128 = uqdata->ObjCodeName.c_str();
    //                ChestStru.Count = TO_WSTRING(Count).c_str();
    //                ChestStru.RandomStat = RandomStat;
    //                ChestStru.OptLevel = OptLevel;
    //                ChestStru.From = TO_WSTRING(From).c_str();
    //                ChestStru.Date = TO_WSTRING(Date).c_str();
    //                CIFMainMenu::ChestGUI->ChestList.push_back(ChestStru);
    //            }
    //        }
    //    }
    //    CIFMainMenu::ChestGUI->UpdateChest();
    //    msg->FlushRemaining();
    //}
    ////Add Item To Chest
    //if (msg->msgid() == 0x5126) {
    //    BYTE No;
    //    int ItemID;
    //    std::n_string Count;
    //    std::n_string From;
    //    std::n_string Date;
    //    bool RandomStat;
    //    std::n_string OptLevel;
    //    *msg >> No >> ItemID >> Count >> RandomStat>>OptLevel >> From >> Date;
    //    if (CGlobalDataManager *g_datamanager = CGlobalDataManager::Get()) {
    //        if (ObjectData *uqdata = g_datamanager->GetObjectData(ItemID)) {
    //            CIFPlayerChest::Chest ChestStru = CIFPlayerChest::Chest();
    //            ChestStru.LineNum = No;
    //            ChestStru.NameStrID128 = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
    //            ChestStru.CodeName128 = uqdata->ObjCodeName.c_str();
    //            ChestStru.Count = TO_WSTRING(Count).c_str();
    //            ChestStru.RandomStat = RandomStat;
    //            ChestStru.OptLevel = OptLevel;
    //            ChestStru.From = TO_WSTRING(From).c_str();
    //            ChestStru.Date = TO_WSTRING(Date).c_str();
    //            if (CIFMainMenu::ChestGUI->ChestContains(ChestStru.NameStrID128.c_str())) {
    //                for (int i = 0; i < CIFPlayerChest::ChestList.size(); ++i) {
    //                    if (wcscmp(CIFPlayerChest::ChestList[i].NameStrID128.c_str(), ChestStru.NameStrID128.c_str()) ==
    //                        0) {
    //                        CIFPlayerChest::ChestList[i].Count = ChestStru.Count;
    //                        CIFMainMenu::ChestGUI->UpdateChest();
    //                        break;
    //                    }
    //                }
    //            } else {
    //                if (CIFPlayerChest::ChestList.size() < 51) {
    //                    CIFPlayerChest::ChestList.push_back(ChestStru);
    //                    CIFMainMenu::ChestGUI->UpdateChest();
    //                }
    //            }
    //        }
    //    }
    //    msg->FlushRemaining();
    //}
    ////Remove Item To Chest
    //if (msg->msgid() == 0x5127) {
    //    int ItemID;
    //    *msg  >> ItemID;
    //    if (CGlobalDataManager *g_datamanager = CGlobalDataManager::Get()) {
    //        if (ObjectData *uqdata = g_datamanager->GetObjectData(ItemID)) {
    //            for (int i = 0; i < CIFPlayerChest::ChestList.size(); ++i) {
    //                if (wcscmp(CIFPlayerChest::ChestList[i].CodeName128.c_str(), uqdata->ObjCodeName.c_str()) == 0) {
    //                    CIFPlayerChest::ChestList.erase(CIFPlayerChest::ChestList.begin() + i);
    //                    CIFMainMenu::ChestGUI->UpdateChest();
    //                    break;
    //                }
    //            }
    //        }
    //    }
    //    msg->FlushRemaining();
    //}
    //if (msg->msgid() == 0x5128)
    //{
    //    BYTE EmptySlots=0;
    //    *msg >> EmptySlots;
    //   // std::cout << "EMPTY SLOTS : "<<EmptySlots <<"\n";
    //    std::wostringstream myStringStream;
    //    myStringStream << EmptySlots;
    //    std::wstring concatenatedStr = myStringStream.str();
    //    CIFMainMenu::ChestGUI->SlotCount->SetText(concatenatedStr.c_str());
    //    msg->FlushRemaining();
    //}

	//Returning true means packet is accepted & read, false means fail & afair client may crash if you do return false
	//Also, if you're planning to read original packets, set TotalReadBYTEs to 0 after you finish reading, because sro_client will re-read this stuff and if any BYTE were read before, it'll crash because it attempts to read over max BYTEs limit.
	return reinterpret_cast<int(__thiscall*)(CPSMission*, CMsgStreamBuffer*)>(0x0084CAB0)(this, msg);
}

wchar_t* CPSMission::Convert(std::n_string name)
{
	wchar_t* szName;
	const char* p = name.c_str();
	int nChars = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
	szName = new WCHAR[nChars];
	MultiByteToWideChar(CP_ACP, 0, p, -1, (LPWSTR)szName, nChars);
	return szName;
}

//bool CPSVersionCheck::OnServerPacketRecv(CMsgStreamBuffer* msg) {
//
//	return reinterpret_cast<int(__thiscall*)(CPSVersionCheck*, CMsgStreamBuffer*)>(0x0086d2a0)(this, msg);
//}

bool CPSTitle::OnServerPacketRecv(CMsgStreamBuffer* msg) {

	switch (msg->msgid()) {

	case 0x0FF2: // SERVER_SHARD_LIST_RESPONSE = 0xA101 but coded
	{
		const char* hwid = HawidManager::GetHWID();
		std::string hwid_X = HawidManager::Xor(hwid);
		std::string hwid_1 = base64_encode(hwid_X);

		byte v255 = rand() % 2;
		byte v237 = 0;
		byte v118 = 0;

		if (v255==1)
		{
			 v237 = 237;
		}
		else if (v255 == 2)
		{
			v237 = 220;
		}


		CMsgStreamBuffer packet(0x1789);

		if (!hwid_1.empty())
		{
			packet << v255;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			packet << v237;
			
			//packet << std::n_string(hwid_1);
			packet << std::n_string(hwid_1.c_str());

			SendMsg(packet);
			//ShowMessage(L"You are authorized to login in try now", 0xfc3103);

		}
		DiscordManager::Instance().UpdateState(GAME_STATE::SERVER_SELECTION);
	}
	break;
	}

	if (msg->msgid() == 0xB003) //notice
	{
		int Color;
		std::n_string notice;
		*msg >> notice >> Color;

		this->ShowMessage(TO_WSTRING(notice).c_str(), Color);

		msg->m_currentReadBytes = 0;
	}

	return reinterpret_cast<int(__thiscall*)(CPSTitle*, CMsgStreamBuffer*)>(0x0086bfc0)(this, msg);
}

bool CPSTitle::OnCreateTMEP(long ln)
{
	bool b = reinterpret_cast<bool(__thiscall*)(CPSTitle*, long)>(0x0086b190)(this, ln);
	
	return b;
}

bool CPSCharacterSelect::OnServerPacketRecv(CMsgStreamBuffer* msg) {

	if (msg->msgid() == 0xB003) //notice
	{
		int Color;
		std::n_string notice;
		*msg >> notice >> Color;

		this->ShowMessage(Convert(notice), Color);

		//msg->FlushRemaining();
		msg->m_currentReadBytes = 0;
	}

	if (msg->msgid() == 0xB007)
	{
	    byte action; *msg >> action;

        //place for char info :P
		/*CIFWnd* Info = this->m_IRM.GetResObj<CIFWnd>(18, 1);
		CIFStatic* Cancle = this->m_IRM.GetResObj<CIFStatic>(13, 1);
		Info->MoveGWnd(Cancle->GetPos().x - 160, Cancle->GetPos().y - 170);
		this->ShowMessage(L"© B-Filter", 0xfc3103);*/
        // Update on character list display
        if (action == 2)
        {
            DiscordManager::Instance().UpdateState(GAME_STATE::CHARACTER_SELECTION);
        }
        msg->m_currentReadBytes = 0;
	}

	return reinterpret_cast<int(__thiscall*)(CPSCharacterSelect*, CMsgStreamBuffer*)>(0x0085fc60)(this, msg);
}

wchar_t* CPSCharacterSelect::Convert(std::n_string name)
{
	wchar_t* szName;
	const char* p = name.c_str();
	int nChars = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
	szName = new WCHAR[nChars];
	MultiByteToWideChar(CP_ACP, 0, p, -1, (LPWSTR)szName, nChars);
	return szName;
}

CIFWnd* CIFTargetWindow::MobWindow()
{
	return  this->m_IRM.GetResObj(2, 1);
}

#define GP_LIMIT 0x1388

void CInterfaceNetSender::DonateGuildPoints(unsigned int GP)
{
	if (GuildSkillPoints >= GP_LIMIT)
	{
		if (g_pCGInterface)
		{
			g_pCGInterface->ShowMessage_Warning (L"Donations cannot be made if the guild points is higher than 5000.");
			g_pCGInterface->WriteSystemMessage(SYSLOG_NONE, L"Donations cannot be made if the guild points is higher than 5000.");
		}
	}
	else
	{
		unsigned int TotalGP = GuildSkillPoints + GP;
		if (TotalGP > GP_LIMIT && GuildSkillPoints < GP_LIMIT)
			GP = GP_LIMIT - GuildSkillPoints;
		reinterpret_cast<void(__thiscall*)(CInterfaceNetSender*, unsigned int)>(0x0081FAB0)(this, GP);
	}
}