#include "OnGameNotify.h"
#include "ObjectData.h"
#include "GInterface.h"
#include "NotificationHandler.h"
#include <TextStringManager.h>
#include <IFSystemMessage.h>
#include <GlobalDataManager.h>
#include <BSLib\multiBYTE.h>
#include <IFSystemMessage.h>

//#define UNIQUE_SPAWN_SYSTEM_COLOR 0xFFDBC99B
//#define UNIQUE_KILL_SYSTEM_COLOR 0xFFDBC99B
//#define DEFAULT_SYSTEM_COLOR 0xFFDBC99B

#define UNIQUE_SPAWN_SYSTEM_COLOR 0x990012
#define UNIQUE_KILL_SYSTEM_COLOR 0x990012
#define DEFAULT_SYSTEM_COLOR 0xFFDBC99B

void Notify::OnGameNotify(CMsgStreamBuffer* msg)
{
	if (msg && g_pCGInterface && g_CTextStringManager)
	{
		if (CIFSystemMessage* sysmsg = g_pCGInterface->GetSystemMessageView())
		{
			unsigned short type;
			*msg >> type;
			std::wstring* chat;
			//printf("%d\n", type);

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
						std::wstring* UniqueName = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID);

						/*if (chat = g_notificationhandler.GetSpawnNotify(uqdata->ObjNameStrID))
						{
							chat = g_CTextStringManager->GetStringByNameStrID(chat);
							g_pCGInterface->ShowMessage_Warning(chat->c_str());
							g_pCGInterface->ShowLogMessage(UNIQUE_SPAWN_SYSTEM_COLOR, chat->c_str());
						}
						else
						{
							wchar_t buffer[0x100];
							std::wstring* Notice = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_APPEAR_UNIC");
							swprintf(buffer, sizeof(buffer), Notice->c_str(), UniqueName->c_str());
							std::wstring* msg;
							msg->assign(buffer);
							g_pCGInterface->ShowMessage_Warning(msg->c_str());
							g_pCGInterface->ShowLogMessage(UNIQUE_SPAWN_SYSTEM_COLOR, msg->c_str());
						}*/

                        if (chat = g_notificationhandler.GetSpawnNotify(uqdata->ObjNameStrID))
                        {
                            chat = g_CTextStringManager->GetStringTextByCode(chat->c_str());
                            g_pCGInterface->ShowMessage_Warning(chat->c_str());
                            g_pCGInterface->ShowLogMessage(UNIQUE_SPAWN_SYSTEM_COLOR, chat->c_str());
                        }
                        else
                        {
                            wchar_t buffer[0x100];
                            swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_APPEAR_UNIC")->c_str(), UniqueName->c_str());
                            g_pCGInterface->ShowMessage_Warning(buffer);
                            g_pCGInterface->ShowLogMessage(UNIQUE_SPAWN_SYSTEM_COLOR, buffer);
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
						std::wstring* UniqueName = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID);

						if (TO_WSTRING(KillerName).compare(L"???") == 0)
						{
							if (chat = g_notificationhandler.GetDespawnNotify(uqdata->ObjNameStrID))
							{
								chat = g_CTextStringManager->GetStringByNameStrID(chat);
								g_pCGInterface->ShowMessage_Warning(chat->c_str());
								g_pCGInterface->ShowLogMessage(UNIQUE_KILL_SYSTEM_COLOR, chat->c_str());
							}
							else
							{
								wchar_t buffer[0x100];
								swprintf(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_DEAD_UNIC")->c_str(), UniqueName->c_str());
								g_pCGInterface->ShowMessage_Warning(buffer);
								g_pCGInterface->ShowLogMessage(UNIQUE_KILL_SYSTEM_COLOR, buffer);
							}
						}
						else
						{
							wchar_t buffer[0x100];

							if (chat = g_notificationhandler.GetKillNotify(uqdata->ObjNameStrID))
							{
								swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringByNameStrID(chat)->c_str(), TO_WSTRING(KillerName).c_str());
								g_pCGInterface->ShowMessage_Warning(buffer);
								g_pCGInterface->ShowLogMessage(UNIQUE_KILL_SYSTEM_COLOR, buffer);
							}
							else
							{
								swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_ANYONE_DEAD_UNIC")->c_str(),TO_WSTRING(KillerName).c_str(), UniqueName->c_str());
								g_pCGInterface->ShowMessage_Warning(buffer);
								g_pCGInterface->ShowLogMessage(UNIQUE_KILL_SYSTEM_COLOR, buffer);
							}
						}
					}
				}
				break;
			}

			case 0x0C07:
			{
				unsigned char type;
				*msg >> type;
				std::n_string guildname;
				*msg >> guildname;
				switch (type)
				{
				case 1:
				{
					chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EVENT_051021_BADGEGAIN_BLUEDRAGON");
					break;
				}
				case 2:
				{
					chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EVENT_051021_BADGEGAIN_PHOENIX");
					break;
				}
				case 3:
				{
					chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EVENT_051021_BADGEGAIN_WHITETIGER");
					break;
				}
				case 4:
				{
					chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EVENT_051021_BADGEGAIN_TURTLE");
					break;
				}
				case 5:
				{
					chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EVENT_051021_BADGEGAIN_WHITETIGER");
					break;
				}
				case 6:
				{
					chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EVENT_051021_BADGEGAIN_WHITETIGER");
					break;
				}
				}

				wchar_t buffer[0x100];
				swprintf_s(buffer, sizeof(buffer), chat->c_str(), TO_WSTRING(guildname).c_str());
				g_pCGInterface->ShowMessage_Warning(buffer);
				g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);
				break;
			}

			case 0x0C08:
			{
				g_pCGInterface->OnNotifyAction(17, type, DEFAULT_SYSTEM_COLOR, 0, 1);
				break;
			}

			case 0x0C10:
			{
				chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_TQ_F4_TELEPORT_OPEN");
				g_pCGInterface->ShowMessage_Warning(chat->c_str());
				g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
				break;
			}

			case 0x0C11:
			{
				chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_TQ_F4_TELEPORT_CLOSE");
				g_pCGInterface->ShowMessage_Warning(chat->c_str());
				g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
				break;
			}

			case 0x0C12:
			{
				chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_QUEST_ROC_APPEAR");
				g_pCGInterface->ShowMessage_Warning(chat->c_str());
				g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
				break;
			}

			case 0x0C13:
			{
				chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_QUEST_ROC_DISAPPEAR");
				g_pCGInterface->ShowMessage_Warning(chat->c_str());
				g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
				break;
			}

			case 0x0C14:
			{
				char mins;
				*msg >> mins;
				switch (mins)
				{
				case 0:
				{
					chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_QUEST_ROC_BERSERKER_START");
					g_pCGInterface->ShowMessage_Warning(chat->c_str());
					g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
					break;
				}

				case -1:
				{
					chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_QUEST_ROC_BERSERKER_AGAIN");
					g_pCGInterface->ShowMessage_Warning(chat->c_str());
					g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
					break;
				}

				default:
				{
					chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_QUEST_ROC_BERSERKER");
					wchar_t buffer[0x100];
					swprintf_s(buffer, sizeof(buffer), chat->c_str(), mins);
					g_pCGInterface->ShowMessage_Warning(buffer);
					g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);
					break;
				}
				}
				break;
			}

			case 0x0C15:
			{
				wchar_t buffer[0x100];
				chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_QUEST_ROC_BYEBYE");
				char tq;
				*msg >> tq;
				swprintf_s(buffer, sizeof(buffer), chat->c_str(), tq);
				g_pCGInterface->ShowMessage_Warning(buffer);
				g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);
				break;
			}

			case 0x0C16:
			{
				std::n_string cht;
				*msg >> cht;
				g_pCGInterface->WriteSystemMessage(SYSLOG_NONE, TO_WSTRING(cht).c_str());
				g_pCGInterface->ShowMessage_Warning(TO_WSTRING(cht).c_str());
				break;
			}

			case 0x0C17:
			{
				wchar_t buffer[0x100];
				std::wstring fullchat;
				unsigned char flag;
				*msg >> flag;
				//unsigned char mins = msg->Read<unsigned char>();

				switch (flag)
				{
				case 0:
				{
					fullchat.assign(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21837_2"));
					fullchat.append(L"]/[");
					fullchat.append(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_2"));
					break;
				}

				case 1:
				{
					fullchat.assign(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_4"));
					break;
				}

				case 2:
				{
					fullchat.assign(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21835_3"));
					fullchat.append(L"]/[");
					fullchat.append(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21835_5"));
					break;
				}
				}

				unsigned char flag1;
				*msg >> flag1;
				swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_SHRINE_ENTRANCE_ALARM")->c_str(), fullchat.c_str(), flag1);

				g_pCGInterface->ShowMessage_Warning(buffer);
				g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);
				break;
			}

			case 0x0C18:
			{
				wchar_t buffer[0x100];
				std::wstring fullchat, dunion;
				unsigned char flag;
				unsigned char uniontype;
				*msg >> flag >> uniontype;
				switch (flag)
				{
				case 0:
				{
					fullchat.assign(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21837_2"));
					fullchat.append(L"]/[");
					fullchat.append(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_2"));
					break;
				}

				case 1:
				{
					fullchat.assign(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_4"));
					break;
				}

				case 2:
				{
					fullchat.assign(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21835_3"));
					fullchat.append(L"]/[");
					fullchat.append(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21835_5"));
					break;
				}
				}

				switch (uniontype)
				{
				case 0:
				{
					dunion.assign(*g_CTextStringManager->GetStringTextByCode(L"UIIT_STT_EGYPT_SHRINE_ENTRANCE_UNION_EMPTY"));
					break;
				}

				case 1:
				{
					dunion.assign(*g_CTextStringManager->GetStringTextByCode(L"UIIT_PAG_COMPANY_MERCHANT"));
					fullchat.append(L" / ");
					break;
				}

				case 2:
				{
					dunion.assign(*g_CTextStringManager->GetStringTextByCode(L"UIIT_PAG_COMPANY_THIEF"));
					break;
				}

				case 3:
				{
					dunion.assign(*g_CTextStringManager->GetStringTextByCode(L"UIIT_STT_EGYPT_SHRINE_ENTRANCE_UNION_ALL"));
					break;
				}
				}

				if (flag == 1 && !uniontype)
					swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_SHRINE_ENTRANCE_UNION_ALARM_04")->c_str(), g_CTextStringManager->GetStringTextByCode(L"UIIT_STT_EGYPT_SHRINE_ENTRANCE_UNION_ALL")->c_str(), fullchat.c_str());
				else
					swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_SHRINE_ENTRANCE_UNION_ALARM_01")->c_str(), dunion.c_str(), fullchat.c_str());

				g_pCGInterface->ShowMessage_Warning(buffer);
				g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);

				if (flag < 2)
				{
					/*msg->Read<unsigned char>();
					msg->Read<unsigned char>();
					msg->Read<unsigned char>();
					msg->Read<unsigned char>();
					msg->Read<unsigned char>();
					msg->Read<unsigned char>();
					msg->Read<unsigned char>();
					msg->Read<unsigned char>();*/
					// msg->Read<long long>();
					long uk;
					*msg >> uk;
					if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
					{
						g_datamanager->TEMPLE_93AEF0(0, uniontype);
						if (g_pCGInterface->sub_799970())
							g_pCGInterface->sub_799970();
					}
				}
				break;
			}

			case 0x0C19:
			{
				unsigned char flag;
				*msg >> flag;
				if (flag < 2)
				{
					unsigned char templething;
					*msg >> templething;
					CGlobalDataManager* g_datamanager = CGlobalDataManager::Get();
					if (g_datamanager)
					{
						g_datamanager->TEMPLE_93AEF0(flag, templething);
						if (g_pCGInterface->sub_799970())
							g_pCGInterface->sub_799970();
					}
				}
				break;
			}

			case 0x0C1A:
			{
				chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_DUNGEON_DESTROY_ALARM");
				wchar_t buffer[0x100];
				unsigned char flag;
				*msg >> flag;
				swprintf_s(buffer, sizeof(buffer), chat->c_str(), flag);
				g_pCGInterface->ShowMessage_Warning(buffer);
				g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);
				break;
			}

			case 0x0C1B:
			{
				unsigned short WorldID;
				*msg >> WorldID;
				if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
				{
					std::wstring WorldCode;
					g_datamanager->GetWorldCodeByID(&WorldCode, WorldID);

					wchar_t buffer[0x100];
					if (WorldCode.compare(L"INS_PHARAOH_NOVICE") == 0)
						swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_TOMB_ENTRANCE_CONDITION_ERROR_04")->c_str(), g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_10")->c_str());
					else if (WorldCode.compare(L"INS_PHARAOH_EXPERT") == 0)
						swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_TOMB_ENTRANCE_CONDITION_ERROR_04")->c_str(), g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_11")->c_str());
					else if (WorldCode.compare(L"INS_PHARAOH_MASTER") == 0)
						swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_TOMB_ENTRANCE_CONDITION_ERROR_04")->c_str(), g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_12")->c_str());
					else
						swprintf_s(buffer, sizeof(buffer), WorldCode.c_str());

					g_pCGInterface->ShowMessage_Warning(buffer);
					g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);
				}
				break;
			}

			case 0x0C1C:
			{
				unsigned char flag;
				*msg >> flag;
				// std::wstring msgcode(msg->ReadStringW());
				std::n_string msgcode;
				*msg >> msgcode;
				switch (flag)
				{
				case 1:
				{
					chat = g_CTextStringManager->GetStringByNameStrID(&TO_WSTRING(msgcode));
					g_pCGInterface->ShowMessage_Warning(chat->c_str());
					break;
				}

				case 2:
				{
					chat = g_CTextStringManager->GetStringByNameStrID(&TO_WSTRING(msgcode));
					g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
					break;
				}
				}
				break;
			}

			default:
			{
				g_pCGInterface->OnNotifyAction(17, type, DEFAULT_SYSTEM_COLOR, 0, 1);
				break;
			}
			}
		}
	}

	//reinterpret_cast<void(__thiscall*)(CNetProcessIn*, MsgStreamBuffer*)>(0x00874EA0)(this, msg);
}
