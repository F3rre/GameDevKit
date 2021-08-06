#pragma once
#include "IFMainFrame.h"
#include "UniqueLog/IFBFilterUniqueList.h"
#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include "SpinButtonControl/IFBFilterSpinButton.h"
#include <list>

class CIFUniqueLog : public CIFMainFrame
{
	GFX_DECLARE_DYNCREATE(CIFUniqueLog)
		GFX_DECLARE_MESSAGE_MAP(CIFUniqueLog)

public:
	CIFUniqueLog(void);
	~CIFUniqueLog(void);

	bool OnCreate(long ln) override;
	void OnUpdate() override;
	void ResetPosition();

	void HideLists();
	void ShowList(BYTE listid);
	static bool UqListContains(const wchar_t* UqName);
	void UpdateLog();
	bool IsPageFull(BYTE PageID, BYTE LineID);

private:
	void On_BtnClick_1();

	void OnClick_Exit();

public:
	static struct UniqueLogstru
	{
		int Pagenum;
		int LineNum;
		std::wstring UqName;
		std::wstring LifeState;
		std::wstring Killer;
		std::wstring Time;
	};

	static std::vector<UniqueLogstru> UQlist;

	CIFUniqueList *m_slot1;
	CIFUniqueList* m_slot2;
	CIFUniqueList* m_slot3;
	CIFUniqueList* m_slot4;
	CIFUniqueList* m_slot5;
	CIFUniqueList* m_slot6;
	CIFUniqueList* m_slot7;
	CIFUniqueList* m_slot8;
	CIFUniqueList* m_slot9;
	CIFUniqueList* m_slot10;

	CIFSpinControl*m_spin;
	CIFStatic* m_custom_label;
	CIFStatic* m_custom_label2;
	CIFStatic* Count;
	CIFStatic* UniqueName;
	CIFStatic* AliveState;
	CIFStatic* KilledBy;
	CIFStatic* SpwanTime;
	CIFFrame* Frame;
};
