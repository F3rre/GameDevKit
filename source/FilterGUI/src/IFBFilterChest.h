#pragma once
#include "IFMainFrame.h"
#include "IFBFilterChestSlotList.h"
#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include <IFBFilterSpinButton.h>
#include <list>

class CIFPlayerChest : public CIFMainFrame
{
	GFX_DECLARE_DYNCREATE(CIFPlayerChest)
		GFX_DECLARE_MESSAGE_MAP(CIFPlayerChest)

public:
	CIFPlayerChest(void);
	~CIFPlayerChest(void);

	bool OnCreate(long ln) override;
	void OnUpdate() override;
	void ResetPosition();

	void HideLists();
	void ShowList(BYTE listid);
	static bool UqListContains(const wchar_t* UqName);
	bool IsPageFull(BYTE PageID, BYTE LineID);
private:
	void On_BtnClick_1();

	void OnClick_Exit();

public:
	static struct Chest
	{
		int ItemID;
		std::wstring ItemName;
		int Count;
		std::wstring From;
		std::wstring Date;
	};

	static std::vector<Chest> ChestList;

	CIFPlayerChestSlotList *m_slot1;
	CIFPlayerChestSlotList* m_slot2;
	CIFPlayerChestSlotList* m_slot3;
	CIFPlayerChestSlotList* m_slot4;
	CIFPlayerChestSlotList* m_slot5;
	CIFPlayerChestSlotList* m_slot6;
	CIFPlayerChestSlotList* m_slot7;
	CIFPlayerChestSlotList* m_slot8;
	CIFPlayerChestSlotList* m_slot9;
	CIFPlayerChestSlotList* m_slot10;

	CIFSpinControl*m_spin;
	CIFStatic* m_custom_label;
	CIFStatic* m_custom_label2;
	CIFStatic* Count;
	CIFStatic* UniqueName;
	CIFStatic* AliveState;
	CIFStatic* KilledBy;
	CIFStatic* SpwanTime;
	CIFButton* Conform;
	CIFFrame* Frame;
};
