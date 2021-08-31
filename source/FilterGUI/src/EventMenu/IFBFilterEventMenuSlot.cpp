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
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu Event'te takım renginizi\nseçemezsiniz.\nKarakterinize uygun\nherhangi bir takım verilir.\nEvent tek takım kazanana kadar\ndevam eder.\nEvent'i kazanan takım\npuan ve ödül almaya hak kazanır.\nKaybeden takımların ise\npuanları düşer.");
		//CGEffSoundBody::get()->PlaySound(L"snd_event_01");
	}
	if (m_custom_label1->GetNText() == L"Random Guild PVP Event")
	{
		CIFMainMenu::EventMenu->SelectedEventName = m_custom_label1->GetNText();
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu Event'te Guild liderleri kayıt yaptırabilirler.\nGuild'e 4 takımdan birisinin rengi verilir.\nEvent tek takım kalana kadar devam eder.\nEvent'i kazanan takımın Guild liderlerine\nGuild üyeleri için kullanabilecekleri ödüller\nve Guild'e ek puan  verilir.\nKaybeden takımlardaki Guildlerin ise\n puanı düşer.");
	}
	if (m_custom_label1->GetNText() == L"PVP Event")
	{
		CIFMainMenu::EventMenu->SelectedEventName = m_custom_label1->GetNText();
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu Event'te kendi takım renginizi\nseçebilirsiniz.\nEvent başladığında\nseçtiğiniz takımın renginde gözükürsünüz\nve takımınız ile kazanmak için\nçabalayabilirsiniz.\nGalip takım, Event ödülü ve puan kazanır.\nYenilen takımların puanı eksilir.");
	}
	if (m_custom_label1->GetNText() == L"Guild Pvp Event")
	{
		CIFMainMenu::EventMenu->SelectedEventName = m_custom_label1->GetNText();
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu Event'te sadece Guild liderleri\nkayıt yaptırabilir.\nGuild'inize seçtiğiniz\ntakımın rengi verilir.\nEvent, sadece\ntek takım kalana kadar devam eder.\nEvent'i kazanan takımın Guild liderlerine\nGuild için kullanabileceği ödüller ve\nGuild'e ek puan verilir.\nKaybeden takımlardaki\nGuildlerin puanları düşer.");
	}
	if (m_custom_label1->GetNText() == L"Event 5")
	{
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu Bölüme Event 5'in tanımı gelecektir\nÖrnek tanıtım satırı 1\nÖrnek tanıtım satırı 2\nÖrnek tanıtım satırı 3");
	}
	if (m_custom_label1->GetNText() == L"Event 6")
	{
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu Bölüme Event 6'in tanımı gelecektir\nÖrnek tanıtım satırı 1\nÖrnek tanıtım satırı 2\nÖrnek tanıtım satırı 3");
	}
	if (m_custom_label1->GetNText() == L"Event 7")
	{
		CIFMainMenu::EventMenu->EventText->SetText(L"Bu Bölüme Event 7'in tanımı gelecektir\nÖrnek tanıtım satırı 1\nÖrnek tanıtım satırı 2\nÖrnek tanıtım satırı 3");
	}
	return 0;
}
