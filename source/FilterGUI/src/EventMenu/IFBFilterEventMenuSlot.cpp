#include "EventMenu/IFBFilterEventMenuSlot.h"
#include <GInterface.h>
#include <ClientNet\MsgStreamBuffer.h>
#include "MainMenu/IFBFilterMainMenu.h"
#include <GEffSoundBody.h>

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
	if (m_custom_label1->GetNText() == L"Random PVP Event")
	{
		CIFMainMenu::EventMenu->SelectedEventName = m_custom_label1->GetNText();
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu Event'te tak�m renginizi\nse�emezsiniz.\nKarakterinize uygun\nherhangi bir tak�m verilir.\nEvent tek tak�m kazanana kadar\ndevam eder.\nEvent'i kazanan tak�m\npuan ve �d�l almaya hak kazan�r.\nKaybeden tak�mlar�n ise\npuanlar� d��er.");
		//CGEffSoundBody::get()->PlaySound(L"snd_event_01");
	}
	if (m_custom_label1->GetNText() == L"Random Guild PVP Event")
	{
		CIFMainMenu::EventMenu->SelectedEventName = m_custom_label1->GetNText();
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu Event'te Guild liderleri kay�t yapt�rabilirler.\nGuild'e 4 tak�mdan birisinin rengi verilir.\nEvent tek tak�m kalana kadar devam eder.\nEvent'i kazanan tak�m�n Guild liderlerine\nGuild �yeleri i�in kullanabilecekleri �d�ller\nve Guild'e ek puan  verilir.\nKaybeden tak�mlardaki Guildlerin ise\n puan� d��er.");
	}
	if (m_custom_label1->GetNText() == L"PVP Event")
	{
		CIFMainMenu::EventMenu->SelectedEventName = m_custom_label1->GetNText();
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu Event'te kendi tak�m renginizi\nse�ebilirsiniz.\nEvent ba�lad���nda\nse�ti�iniz tak�m�n renginde g�z�k�rs�n�z\nve tak�m�n�z ile kazanmak i�in\n�abalayabilirsiniz.\nGalip tak�m, Event �d�l� ve puan kazan�r.\nYenilen tak�mlar�n puan� eksilir.");
	}
	if (m_custom_label1->GetNText() == L"Guild Pvp Event")
	{
		CIFMainMenu::EventMenu->SelectedEventName = m_custom_label1->GetNText();
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu Event'te sadece Guild liderleri\nkay�t yapt�rabilir.\nGuild'inize se�ti�iniz\ntak�m�n rengi verilir.\nEvent, sadece\ntek tak�m kalana kadar devam eder.\nEvent'i kazanan tak�m�n Guild liderlerine\nGuild i�in kullanabilece�i �d�ller ve\nGuild'e ek puan verilir.\nKaybeden tak�mlardaki\nGuildlerin puanlar� d��er.");
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
