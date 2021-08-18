#include "EventMenu/IFBFilterEventMenuSlot.h"
#include <GInterface.h>
#include <ClientNet\MsgStreamBuffer.h>
#include "MainMenu/IFBFilterMainMenu.h"

GFX_IMPLEMENT_DYNCREATE(CIFEventMenuSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFEventMenuSlot, CIFWnd)
GFX_END_MESSAGE_MAP()


CIFEventMenuSlot::CIFEventMenuSlot(void)
{
}


CIFEventMenuSlot::~CIFEventMenuSlot(void)
{
}

bool CIFEventMenuSlot::OnCreate(long ln)
{

	// Populate inherited members
	CIFWnd::OnCreate(ln);

	RECT rect1 = { 5,6,167,13 };

	m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, 37, 0);
	m_custom_label1->SetTextColor(0xffffff);


	this->ShowGWnd(false);
	return true;
}

int CIFEventMenuSlot::OnMouseLeftUp(int a1, int x, int y)
{
	CIFMainMenu::EventMenu->ClearDDJ();
	//CIFMainMenu::ChestGUI->SelectedItemName = m_custom_label2->GetNText();
	TB_Func_13("interface\\ifcommon\\com_bar01select_mid.ddj", 0, 0);
	if (m_custom_label1->GetNText() == L"Event 1")
	{
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu B�l�me Event 1'in tan�m� gelecektir\n�rnek tan�t�m sat�r� 1\n�rnek tan�t�m sat�r� 2\n�rnek tan�t�m sat�r� 3");
	}
	if (m_custom_label1->GetNText() == L"Event 2")
	{
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu B�l�me Event 2'in tan�m� gelecektir\n�rnek tan�t�m sat�r� 1\n�rnek tan�t�m sat�r� 2\n�rnek tan�t�m sat�r� 3");
	}
	if (m_custom_label1->GetNText() == L"Event 3")
	{
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu B�l�me Event 3'in tan�m� gelecektir\n�rnek tan�t�m sat�r� 1\n�rnek tan�t�m sat�r� 2\n�rnek tan�t�m sat�r� 3");
	}
	if (m_custom_label1->GetNText() == L"Event 4")
	{
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu B�l�me Event 4'in tan�m� gelecektir\n�rnek tan�t�m sat�r� 1\n�rnek tan�t�m sat�r� 2\n�rnek tan�t�m sat�r� 3");
	}
	if (m_custom_label1->GetNText() == L"Event 5")
	{
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu B�l�me Event 5'in tan�m� gelecektir\n�rnek tan�t�m sat�r� 1\n�rnek tan�t�m sat�r� 2\n�rnek tan�t�m sat�r� 3");
	}
	if (m_custom_label1->GetNText() == L"Event 6")
	{
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu B�l�me Event 6'in tan�m� gelecektir\n�rnek tan�t�m sat�r� 1\n�rnek tan�t�m sat�r� 2\n�rnek tan�t�m sat�r� 3");
	}
	if (m_custom_label1->GetNText() == L"Event 7")
	{
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu B�l�me Event 7'in tan�m� gelecektir\n�rnek tan�t�m sat�r� 1\n�rnek tan�t�m sat�r� 2\n�rnek tan�t�m sat�r� 3");
	}
	return 0;
}
