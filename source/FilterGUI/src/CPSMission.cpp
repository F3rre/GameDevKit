#include "CPSMission.h"
#include <GInterface.h>
#include <BSLib\multiBYTE.h>
#include <GlobalDataManager.h>
#include <TextStringManager.h>
#include <PSOuterInterface.h>
#include "BSLib/BSLib.h"
#include <Game.h>
#include <IFBFilterTitles.h>
#include <ObjectData.h>
#include <IFBFilterMainMenu.h>

bool CPSMission::char_is_ready;
BYTE CPSMission::CurHawn = -1;

bool CPSMission::Gui_GrantName;
bool CPSMission::Gui_UniqueHistory;
bool CPSMission::Gui_CustomTitle;
bool CPSMission::Gui_SwitchTitle;
bool CPSMission::Gui_EventTimer;
bool CPSMission::Gui_CharacterLock;

bool CPSMission::OnServerPacketRecv(CMsgStreamBuffer* msg) {
	/// ORG PACKETS
	if (msg->msgid() == 0x3305)
	{
		BYTE JOBTYPE = g_pCICPlayer->GetJobType();
		BYTE CURLEVEL = g_pCICPlayer->m_level;
		uregion CurRegion = g_pCICPlayer->GetRegion();

		CMsgStreamBuffer buf(0x3560);
		buf << JOBTYPE;
		buf << CURLEVEL;
		buf << CurRegion.r;
		SendMsg(buf);

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
	if (msg->msgid() == 0x5101)//Show Form
	{
		

		int FormID = 0;
		bool ShowHide = 0;
		*msg >> FormID >> ShowHide;

		switch (FormID)
		{
		case DMGMeter:
		{
			if (ShowHide == 0) {
                CIFMainMenu::DmgMeterGui->Clear();
                CIFMainMenu::DmgMeterGui->ShowGWnd(true);
			}
			else
			{
				//get the target mob
				CIFTargetWindow* target = g_pCGInterface->m_IRM.GetResObj<CIFTargetWindow>(16, 1);
				CIFWnd* MOB = target->MobWindow();
				//show the dmg meter
                CIFMainMenu::DmgMeterGui->Clear();
                CIFMainMenu::DmgMeterGui->ShowGWnd(true);
				int x = MOB->GetPos().x * 2 - 150;
                CIFMainMenu::DmgMeterGui->MoveGWnd(x, MOB->GetPos().y);
			}
		}
		break;
		case FtwKillsCounter:
		{
			if (ShowHide == 0) {
                CIFMainMenu::FtwCunterGUI->Clear();
                CIFMainMenu::FtwCunterGUI->ShowGWnd(false);
			}
			else
			{
                CIFMainMenu::FtwCunterGUI->ResetPosition();
                CIFMainMenu::FtwCunterGUI->ShowGWnd(true);
			}
		}
		break;
		case SurvKillsCounter:
		{
			if (ShowHide == 0) {
                CIFMainMenu::SurvGuiGUI->Clear();
                CIFMainMenu::SurvGuiGUI->ShowGWnd(false);
			}
			else
			{
                CIFMainMenu::SurvGuiGUI->ResetPosition();
                CIFMainMenu::SurvGuiGUI->ShowGWnd(true);
			}
		}
		break;
		}

		msg->FlushRemaining();
	}
	//notices
	if (msg->msgid() == 0x5102) //notice
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
			g_pCGInterface->WriteSystemMessage(SYSLOG_NONE, Convert(notice));
		}

		if (Type == 5)
		{
			g_pCGInterface->WriteSystemMessage(SYSLOG_GUIDE, Convert(notice));
		}

		if (Type == 6)
		{
			int Color;
			*msg >> Color;
			g_pCGInterface->ShowLogMessage(Color, Convert(notice));
		}

		if (Type == 7)
		{
			std::n_string Key;
			int Color;
			*msg >> Color >> Key;
			WriteToChat(CHAT_Ask, L"", Convert(notice), 0, Color, Convert(Key));
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
				switch (i)
				{
				case 1:
                    CIFMainMenu::DmgMeterGui->WriteLine(1, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
					break;
				case 2:
                    CIFMainMenu::DmgMeterGui->WriteLine(2, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
					break;
				case 3:
                    CIFMainMenu::DmgMeterGui->WriteLine(3, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
					break;
				case 4:
                    CIFMainMenu::DmgMeterGui->WriteLine(4, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
					break;
				case 5:
                    CIFMainMenu::DmgMeterGui->WriteLine(5, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
					break;
				case 6:
                    CIFMainMenu::DmgMeterGui->WriteLine(6, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
					break;
				case 7:
                    CIFMainMenu::DmgMeterGui->WriteLine(7, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
					break;
				case 8:
                    CIFMainMenu::DmgMeterGui->WriteLine(8, Char->GetName().c_str(), TO_WSTRING(DMG).c_str());
					break;
				}
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
		//CIFSwitchTitle* Log = g_pCGInterface->m_IRM.GetResObj<CIFSwitchTitle>(SwitchTitles, 1);
        CIFMainMenu::SwitchTitleGUI->m_textbox->m_LinesOfHistory = count;

		while (i < count && count > 0)
		{
			i++;
			*msg >> ID >> Name >> Color;

			wchar_t buffer1[255];
			std::wstring TitleName = g_CTextStringManager->GetStringByNameStrID(&TO_WSTRING(Name))->c_str();
			if (TitleName.empty())
				TitleName = L"<Remove>";

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

		*msg >> GUIGrantName >> GUIUniqueHistory >> GUICustomTitle >> GUISwitchTitle  >> GUICharacterLock >> GUIEventTimer;

		CPSMission::Gui_GrantName = GUIGrantName;
		CPSMission::Gui_UniqueHistory = GUIUniqueHistory;
		CPSMission::Gui_CustomTitle = GUICustomTitle;
		CPSMission::Gui_SwitchTitle = GUISwitchTitle;
		CPSMission::Gui_CharacterLock = GUICharacterLock;
		CPSMission::Gui_EventTimer = GUIEventTimer;

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

			switch (i)
			{
			case 1:
                CIFMainMenu::FtwCunterGUI->WriteLine(1, TO_WSTRING(GuildName).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 2:
                CIFMainMenu::FtwCunterGUI->WriteLine(2, TO_WSTRING(GuildName).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 3:
                CIFMainMenu::FtwCunterGUI->WriteLine(3, TO_WSTRING(GuildName).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 4:
                CIFMainMenu::FtwCunterGUI->WriteLine(4, TO_WSTRING(GuildName).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 5:
                CIFMainMenu::FtwCunterGUI->WriteLine(5, TO_WSTRING(GuildName).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 6:
                CIFMainMenu::FtwCunterGUI->WriteLine(6, TO_WSTRING(GuildName).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 7:
                CIFMainMenu::FtwCunterGUI->WriteLine(7, TO_WSTRING(GuildName).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 8:
                CIFMainMenu::FtwCunterGUI->WriteLine(8, TO_WSTRING(GuildName).c_str(), TO_WSTRING(Kills).c_str());
				break;
			}
		}
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

		//CIFSurvCounter* Log = g_pCGInterface->m_IRM.GetResObj<CIFSurvCounter>(SurvKillsCounter, 1);
        CIFMainMenu::SurvGuiGUI->Clear();

		while (i < sCount && sCount > 0)
		{
			i++;
			*msg >> Player >> Kills;

			switch (i)
			{
			case 1:
                CIFMainMenu::SurvGuiGUI->WriteLine(1, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 2:
                CIFMainMenu::SurvGuiGUI->WriteLine(2, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 3:
                CIFMainMenu::SurvGuiGUI->WriteLine(3, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 4:
                CIFMainMenu::SurvGuiGUI->WriteLine(4, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 5:
                CIFMainMenu::SurvGuiGUI->WriteLine(5, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 6:
                CIFMainMenu::SurvGuiGUI->WriteLine(6, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 7:
                CIFMainMenu::SurvGuiGUI->WriteLine(7, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str());
				break;
			case 8:
                CIFMainMenu::SurvGuiGUI->WriteLine(8, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str());
				break;
			}
		}
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

wchar_t* CPSTitle::Convert(std::n_string name)
{
	wchar_t* szName;
	const char* p = name.c_str();
	int nChars = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
	szName = new WCHAR[nChars];
	MultiByteToWideChar(CP_ACP, 0, p, -1, (LPWSTR)szName, nChars);
	return szName;
}

bool CPSTitle::OnServerPacketRecv(CMsgStreamBuffer* msg) {
	

	if (msg->msgid() == 0xB003) //notice
	{
		int Color;
		std::n_string notice;
		*msg >> notice >> Color;

		this->ShowMessage(Convert(notice), Color);

		msg->m_currentReadBytes = 0;
	}

	//if (msg->msgid() == 0xA106)
	//{
	//	const char* hwid = HawidManager::GetHWID();
	//	const char* serial = HawidManager::GetSerial();
	//	const char* mac = HawidManager::GetMac();
	//	std::string hwid_1 = md5(hwid);
	//	const char* hwid_2 = hwid_1.c_str();
	//	std::string date = HawidManager::GetDate2();
	//	const char* date2 = date.c_str();
	//	BYTE v255 = 255;
	//	BYTE v237 = 237;
	//	BYTE v118 = 118;
	//	CMsgStreamBuffer packet(0x1789);
	//	if (mac != "0") {	

	//	SendMsg(packet);

	//	if (mac != "0")
	//		ShowErrorMessage(L"You are authorized to login in try now", 0x20ce88);


	//	msg->m_currentReadBytes = 0;
	//}
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
		//place for char info :P
		CIFWnd* Info = this->m_IRM.GetResObj<CIFWnd>(18, 1);
		CIFStatic* Cancle = this->m_IRM.GetResObj<CIFStatic>(13, 1);
		Info->MoveGWnd(Cancle->GetPos().x - 160, Cancle->GetPos().y - 170);
		this->ShowMessage(L"Welcome To Our Server\n© B-Filter", 0x20ce88);
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

#define GP_LIMIT 0x7FFFFFFF

void CInterfaceNetSender::DonateGuildPoints(unsigned int GP)
{
	if (GuildSkillPoints >= GP_LIMIT)
	{
		if (g_pCGInterface)
		{
			g_pCGInterface->ShowMessage_Warning (L"You have reached maximum limit of guild skills points.");
			g_pCGInterface->WriteSystemMessage(SYSLOG_NONE, L"You have reached maximum limit of guild skills points.");
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