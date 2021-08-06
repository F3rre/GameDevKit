#pragma once
#include "IFMainFrame.h"
#include "IFBFilterUniqueLogSlot.h"


class CIFUniqueList : public CIFWnd
{
	GFX_DECLARE_DYNCREATE(CIFUniqueList)
	GFX_DECLARE_MESSAGE_MAP(CIFUniqueList)

public:
	CIFUniqueList(void);
	~CIFUniqueList(void);

	bool OnCreate(long ln) override;
	void OnUpdate() override;

	void WriteLine(BYTE num, const wchar_t* UQName, const wchar_t* State, const wchar_t* Killer, const wchar_t* STme);

	CIFUniqueLogSlot* line1;
	CIFUniqueLogSlot* line2;
	CIFUniqueLogSlot* line3;
	CIFUniqueLogSlot* line4;
	CIFUniqueLogSlot* line5;
	CIFUniqueLogSlot* line6;
	CIFUniqueLogSlot* line7;
	CIFUniqueLogSlot* line8;
	CIFUniqueLogSlot* line9;
	CIFUniqueLogSlot* line10;
};
