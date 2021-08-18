#include "IFBFilterMainMenu.h"

#define BFILTER_MENU_TITLES_BUTTON 10
#define BFILTER_MENU_GARNTNAME_BUTTON 11
#define BFILTER_MENU_UNIQUELOG_BUTTON 12
#define BFILTER_MENU_CHARLOCK_BUTTON 13
#define BFILTER_MENU_RANK_BUTTON 14
#define BFILTER_MENU_EVENTTIMER_BUTTON 15
#define BFILTER_MENU_CHANGELOG_BUTTON 24

#define GUIMENU_ENGLISH 26
#define GUIMENU_TURKISH 27
#define BFILTER_MENU_FRAME 6
#define BFILTER_MENU_NORMALTITLE 5

#define GUIMENU_TITLES_TEXT 16
#define GUIMENU_TITLES_TEXT1 18
#define GUIMENU_TITLES_TEXT2 19
#define GUIMENU_TITLES_TEXT3 20
#define GUIMENU_TITLES_TEXT4 21
#define GUIMENU_TITLES_TEXT5 22
#define GUIMENU_TITLES_TEXT6 23

GFX_IMPLEMENT_DYNCREATE(CIFMainMenu, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFMainMenu, CIFMainFrame)
ONG_CHAR()
ONG_COMMAND(BFILTER_MENU_TITLES_BUTTON, &CIFMainMenu::On_BtnClick_1)
ONG_COMMAND(BFILTER_MENU_GARNTNAME_BUTTON, &CIFMainMenu::On_BtnClick_2)
ONG_COMMAND(BFILTER_MENU_UNIQUELOG_BUTTON, &CIFMainMenu::On_BtnClick_3)
ONG_COMMAND(BFILTER_MENU_CHARLOCK_BUTTON, &CIFMainMenu::On_BtnClick_4)
ONG_COMMAND(BFILTER_MENU_RANK_BUTTON, &CIFMainMenu::On_BtnClick_5)
ONG_COMMAND(BFILTER_MENU_EVENTTIMER_BUTTON, &CIFMainMenu::On_BtnClick_6)
ONG_COMMAND(GUIMENU_TURKISH, &CIFMainMenu::On_Btn_turkishLang)
ONG_COMMAND(GUIMENU_ENGLISH, &CIFMainMenu::On_Btn_EnglishLang)

GFX_END_MESSAGE_MAP()


 CIFMainMenu* CIFMainMenu::MenuGui;
 CIFGrantName* CIFMainMenu::GrantNameGUI;
 CIFSwitchTitle* CIFMainMenu::SwitchTitleGUI;
 CIFUniqueLog* CIFMainMenu::UniqueLogGUI;
 CIFEventTime* CIFMainMenu::EventTimeGUI;
 CIFCharLock* CIFMainMenu::CharLockGUI;
 CIFCustomRank* CIFMainMenu::CustomRankGUI;
 CIFDMGMeter* CIFMainMenu::DmgMeterGui;
 CIFCustomTitle* CIFMainMenu::CustomTitleGUI;
 CIFSurvCounter* CIFMainMenu::SurvGuiGUI;
 CIFFTWCounter* CIFMainMenu::FtwCunterGUI;
 CIFNotify* CIFMainMenu::PurbleNoitfy;
 CIFNotify* CIFMainMenu::OrangeNoitfy;
 CIFEventMenu* CIFMainMenu::EventMenu;

 CGWnd* CIFMainMenu::MenuIcon;
 CGWnd* CIFMainMenu::DiscordIcon;
 CGWnd* CIFMainMenu::FacebookIcon;
CGWnd* CIFMainMenu::ReloadIcon;

CIFMainMenu::CIFMainMenu(void)
{
	//printf("> " __FUNCTION__ "\n");
}


CIFMainMenu::~CIFMainMenu(void)
{
	//printf("> " __FUNCTION__ "\n");
}

bool CIFMainMenu::OnCreate(long ln)
{
	//printf("> " __FUNCTION__ "(%d)\n", ln);

	// Populate inherited members
	CIFMainFrame::OnCreate(ln);

	//m_IRM.LoadFromFile("resinfo\\ifbfiltermenu.txt");
	//m_IRM.CreateInterfaceSection("Create", this);
	RECT rect = { 0,0,0,0 };
	m_mybutton = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), rect, BFILTER_MENU_TITLES_BUTTON, 0);
	m_mybutton2 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), rect, BFILTER_MENU_GARNTNAME_BUTTON, 0);
	m_mybutton3 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), rect, BFILTER_MENU_UNIQUELOG_BUTTON, 0);
	m_mybutton4 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), rect, BFILTER_MENU_CHARLOCK_BUTTON, 0);
	m_mybutton5 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), rect, BFILTER_MENU_RANK_BUTTON, 0);
	m_mybutton6 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), rect, BFILTER_MENU_EVENTTIMER_BUTTON, 0);
	m_mybutton7 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), rect, BFILTER_MENU_CHANGELOG_BUTTON, 0);
	m_mybutton9 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), rect, GUIMENU_TURKISH, 0);
	m_mybutton10 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), rect, GUIMENU_ENGLISH, 0);
	Frame = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, BFILTER_MENU_FRAME, 0);
	//LABELS
	LAB_TITLES = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, GUIMENU_TITLES_TEXT, 0);
	LAB_TITLES1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, GUIMENU_TITLES_TEXT1, 0);
	LAB_TITLES2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, GUIMENU_TITLES_TEXT2, 0);
	LAB_TITLES3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, GUIMENU_TITLES_TEXT3, 0);
	LAB_TITLES4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, GUIMENU_TITLES_TEXT4, 0);
	LAB_TITLES5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, GUIMENU_TITLES_TEXT5, 0);
	LAB_TITLES6 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, GUIMENU_TITLES_TEXT6, 0);

	m_handleBar->MoveGWnd(GetPos().x, GetPos().y);
	m_handleBar->SetGWndSize(165, 20);


	Frame->TB_Func_13("interface\\gui\\gui_frame.ddj", 0, 0);
	Frame->SetGWndSize(165, 420);

	LAB_TITLES->SetText(L"Title Storage");
	LAB_TITLES1->SetText(L"Grant Name");
	LAB_TITLES2->SetText(L"Unique History");
	LAB_TITLES3->SetText(L"Character Lock");
	LAB_TITLES4->SetText(L"Custom Rank");
	LAB_TITLES5->SetText(L"Event Schedule");
	LAB_TITLES6->SetText(L"Change Log");

	LAB_TITLES->m_FontTexture.sub_8B4400(0, 0);
	LAB_TITLES->m_FontTexture.sub_8B4750(0);
	LAB_TITLES->TB_Func_5(0);
	LAB_TITLES->TB_Func_6(0);

	LAB_TITLES1->m_FontTexture.sub_8B4400(0, 0);
	LAB_TITLES1->m_FontTexture.sub_8B4750(0);
	LAB_TITLES1->TB_Func_5(0);
	LAB_TITLES1->TB_Func_6(0);

	LAB_TITLES2->m_FontTexture.sub_8B4400(0, 0);
	LAB_TITLES2->m_FontTexture.sub_8B4750(0);
	LAB_TITLES2->TB_Func_5(0);
	LAB_TITLES2->TB_Func_6(0);

	LAB_TITLES3->m_FontTexture.sub_8B4400(0, 0);
	LAB_TITLES3->m_FontTexture.sub_8B4750(0);
	LAB_TITLES3->TB_Func_5(0);
	LAB_TITLES3->TB_Func_6(0);

	LAB_TITLES4->m_FontTexture.sub_8B4400(0, 0);
	LAB_TITLES4->m_FontTexture.sub_8B4750(0);
	LAB_TITLES4->TB_Func_5(0);
	LAB_TITLES4->TB_Func_6(0);

	LAB_TITLES5->m_FontTexture.sub_8B4400(0, 0);
	LAB_TITLES5->m_FontTexture.sub_8B4750(0);
	LAB_TITLES5->TB_Func_5(0);
	LAB_TITLES5->TB_Func_6(0);

	LAB_TITLES6->m_FontTexture.sub_8B4400(0, 0);
	LAB_TITLES6->m_FontTexture.sub_8B4750(0);
	LAB_TITLES6->TB_Func_5(0);
	LAB_TITLES6->TB_Func_6(0);

	m_close->MoveGWnd(Frame->GetPos().x + Frame->GetSize().width - 22, Frame->GetPos().y + 5);

	m_mybutton->MoveGWnd(20, 58);
	m_mybutton->SetGWndSize(32, 32);
	m_mybutton->TB_Func_13("interface\\gui\\titlestorage1.ddj", 0, 0);

	m_mybutton2->MoveGWnd(m_mybutton->GetPos().x, m_mybutton->GetPos().y + 43);
	m_mybutton2->SetGWndSize(32, 32);
	m_mybutton2->TB_Func_13("interface\\gui\\grantname1.ddj", 0, 0);

	m_mybutton3->MoveGWnd(m_mybutton2->GetPos().x, m_mybutton2->GetPos().y + 43);
	m_mybutton3->SetGWndSize(32, 32);
	m_mybutton3->TB_Func_13("interface\\gui\\uniquenotices1.ddj", 0, 0);

	m_mybutton4->MoveGWnd(m_mybutton3->GetPos().x, m_mybutton3->GetPos().y + 43);
	m_mybutton4->SetGWndSize(32, 32);
	m_mybutton4->TB_Func_13("interface\\gui\\uniquenotices1.ddj", 0, 0);

	m_mybutton5->MoveGWnd(m_mybutton4->GetPos().x, m_mybutton4->GetPos().y + 43);
	m_mybutton5->SetGWndSize(32, 32);
	m_mybutton5->TB_Func_13("interface\\gui\\uniquenotices1.ddj", 0, 0);

	m_mybutton6->MoveGWnd(m_mybutton5->GetPos().x, m_mybutton5->GetPos().y + 43);
	m_mybutton6->SetGWndSize(32, 32);
	m_mybutton6->TB_Func_13("interface\\gui\\uniquenotices1.ddj", 0, 0);

	m_mybutton7->MoveGWnd(m_mybutton6->GetPos().x, m_mybutton6->GetPos().y + 43);
	m_mybutton7->SetGWndSize(32, 32);
	m_mybutton7->TB_Func_13("interface\\gui\\uniquenotices1.ddj", 0, 0);

	m_mybutton9->MoveGWnd(m_mybutton7->GetPos().x + 30, m_mybutton7->GetPos().y + 72);
	m_mybutton9->SetGWndSize(25, 20);
	m_mybutton9->TB_Func_13("interface\\gui\\guimenu_turkish.ddj", 0, 0);

	m_mybutton10->MoveGWnd(m_mybutton9->GetPos().x + 40, m_mybutton7->GetPos().y + 72);
	m_mybutton10->SetGWndSize(25, 20);
	m_mybutton10->TB_Func_13("interface\\gui\\guimenu_english.ddj", 0, 0);

	LAB_TITLES->MoveGWnd(m_mybutton->GetPos().x + 40, m_mybutton->GetPos().y + 8);
	LAB_TITLES1->MoveGWnd(m_mybutton2->GetPos().x + 40, m_mybutton2->GetPos().y + 8);
	LAB_TITLES2->MoveGWnd(m_mybutton3->GetPos().x + 40, m_mybutton3->GetPos().y + 8);
	LAB_TITLES3->MoveGWnd(m_mybutton4->GetPos().x + 40, m_mybutton4->GetPos().y + 8);
	LAB_TITLES4->MoveGWnd(m_mybutton5->GetPos().x + 40, m_mybutton5->GetPos().y + 8);
	LAB_TITLES5->MoveGWnd(m_mybutton6->GetPos().x + 40, m_mybutton6->GetPos().y + 8);
	LAB_TITLES6->MoveGWnd(m_mybutton7->GetPos().x + 40, m_mybutton7->GetPos().y + 8);

	m_close->BringToFront();
	//m_handleBar->BringToFront();

	m_mybutton->BringToFront();
	m_mybutton2->BringToFront();
	m_mybutton3->BringToFront();
	m_mybutton4->BringToFront();
	m_mybutton5->BringToFront();
	m_mybutton6->BringToFront();
	m_mybutton7->BringToFront();
	m_mybutton9->BringToFront();
	m_mybutton10->BringToFront();
	LAB_TITLES->BringToFront();
	LAB_TITLES1->BringToFront();
	LAB_TITLES2->BringToFront();
	LAB_TITLES3->BringToFront();
	LAB_TITLES4->BringToFront();
	LAB_TITLES5->BringToFront();
	LAB_TITLES6->BringToFront();

	ResetPosition();
	this->ShowGWnd(false);
	return true;
}

void CIFMainMenu::OnUpdate()
{
}

void CIFMainMenu::On_BtnClick_1()
{
	/*if (!CPSMission::Gui_SwitchTitle)
	{
        g_pCGInterface->ShowMessage_Notice(L"Service not available");
		return;
	}*/

	if (CIFMainMenu::CustomRankGUI->IsVisible()) {
        CIFMainMenu::CustomRankGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::GrantNameGUI->IsVisible()) {
        CIFMainMenu::GrantNameGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::UniqueLogGUI->IsVisible()) {
		CIFMainMenu::UniqueLogGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::EventTimeGUI->IsVisible()) {
		CIFMainMenu::EventTimeGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::CharLockGUI->IsVisible()) {
		CIFMainMenu::CharLockGUI->ShowGWnd(false);
	}

	CIFMainMenu::SwitchTitleGUI->ShowGWnd(true);
	CIFMainMenu::SwitchTitleGUI->ResetPosition();
	CIFMainMenu::SwitchTitleGUI->BringToFront();

	CIFMainMenu::EventMenu->ShowGWnd(true);
	CIFMainMenu::EventMenu->ResetPosition();
	CIFMainMenu::EventMenu->BringToFront();

}
void CIFMainMenu::On_BtnClick_2()
{
	/*if (!CPSMission::Gui_GrantName)
	{
        g_pCGInterface->ShowMessage_Notice(L"Service not available");
		return;
	}*/

	if (CIFMainMenu::CustomRankGUI->IsVisible()) {
		CIFMainMenu::CustomRankGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::SwitchTitleGUI->IsVisible()) {
		CIFMainMenu::SwitchTitleGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::UniqueLogGUI->IsVisible()) {
		CIFMainMenu::UniqueLogGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::EventTimeGUI->IsVisible()) {
		CIFMainMenu::EventTimeGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::CharLockGUI->IsVisible()) {
		CIFMainMenu::CharLockGUI->ShowGWnd(false);
	}

	CIFMainMenu::GrantNameGUI->ShowGWnd(true);
	CIFMainMenu::GrantNameGUI->ResetPosition();
	CIFMainMenu::GrantNameGUI->BringToFront();
}
void CIFMainMenu::On_BtnClick_3()
{
	/*if (!CPSMission::Gui_UniqueHistory)
	{
        g_pCGInterface->ShowMessage_Notice(L"Service not available");
		return;
	}*/

	if (CIFMainMenu::CustomRankGUI->IsVisible()) {
		CIFMainMenu::CustomRankGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::SwitchTitleGUI->IsVisible()) {
		CIFMainMenu::SwitchTitleGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::GrantNameGUI->IsVisible()) {
		CIFMainMenu::GrantNameGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::EventTimeGUI->IsVisible()) {
		CIFMainMenu::EventTimeGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::CharLockGUI->IsVisible()) {
		CIFMainMenu::CharLockGUI->ShowGWnd(false);
	}

	CIFMainMenu::UniqueLogGUI->ShowGWnd(true);
	CIFMainMenu::UniqueLogGUI->ResetPosition();
	CIFMainMenu::UniqueLogGUI->BringToFront();
}
void CIFMainMenu::On_BtnClick_4()
{/*
	if (!CPSMission::Gui_CharacterLock)
	{
        g_pCGInterface->ShowMessage_Notice(L"Service not available");
		return;
	}
	*/
	if (CIFMainMenu::CustomRankGUI->IsVisible()) {
		CIFMainMenu::CustomRankGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::SwitchTitleGUI->IsVisible()) {
		CIFMainMenu::SwitchTitleGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::GrantNameGUI->IsVisible()) {
		CIFMainMenu::GrantNameGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::EventTimeGUI->IsVisible()) {
		CIFMainMenu::EventTimeGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::UniqueLogGUI->IsVisible()) {
		CIFMainMenu::UniqueLogGUI->ShowGWnd(false);
	}

	CIFMainMenu::CharLockGUI->ShowGWnd(true);
	CIFMainMenu::CharLockGUI->ResetPosition();
	CIFMainMenu::CharLockGUI->BringToFront();
}

void CIFMainMenu::On_BtnClick_5()
{/*
	if (!CPSMission::Gui_CustomRank)
	{
		g_pCGInterface->ShowMessage_Notice(L"Service not available");
		return;
	}
*/
	if (CIFMainMenu::CharLockGUI->IsVisible()) {
		CIFMainMenu::CharLockGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::SwitchTitleGUI->IsVisible()) {
		CIFMainMenu::SwitchTitleGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::GrantNameGUI->IsVisible()) {
		CIFMainMenu::GrantNameGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::EventTimeGUI->IsVisible()) {
		CIFMainMenu::EventTimeGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::UniqueLogGUI->IsVisible()) {
		CIFMainMenu::UniqueLogGUI->ShowGWnd(false);
	}

	CIFMainMenu::CustomRankGUI->ShowGWnd(true);
	CIFMainMenu::CustomRankGUI->ResetPosition();
	CIFMainMenu::CustomRankGUI->BringToFront();
}

void CIFMainMenu::On_BtnClick_6()
{/*
	if (!CPSMission::Gui_EventTimer)
	{
		g_pCGInterface->ShowMessage_Notice(L"Service not available");
		return;
	}
*/
	if (CIFMainMenu::CharLockGUI->IsVisible()) {
		CIFMainMenu::CharLockGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::SwitchTitleGUI->IsVisible()) {
		CIFMainMenu::SwitchTitleGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::GrantNameGUI->IsVisible()) {
		CIFMainMenu::GrantNameGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::CustomRankGUI->IsVisible()) {
		CIFMainMenu::CustomRankGUI->ShowGWnd(false);
	}

	if (CIFMainMenu::UniqueLogGUI->IsVisible()) {
		CIFMainMenu::UniqueLogGUI->ShowGWnd(false);
	}


	CIFMainMenu::EventTimeGUI->ShowGWnd(true);
	CIFMainMenu::EventTimeGUI->ResetPosition();
	CIFMainMenu::EventTimeGUI->BringToFront();
}


void CIFMainMenu::ResetPosition()
{
	USHORT PosX = 0, PosY = 165;
	PosY = CLIENT_SCREEN_HEIGHT - 300;
	PosX = CLIENT_SCREEN_WIDTH - 300;
	this->MoveGWnd(PosX, PosY);
}

void CIFMainMenu::On_Btn_turkishLang()
{
	LAB_TITLES->SetText(L"Title Deposu");
	LAB_TITLES1->SetText(L"Grant Name Deðiþtir");
	LAB_TITLES2->SetText(L"Unique Unique Geçmiþi");
	LAB_TITLES3->SetText(L"Karakter Kilit");
	LAB_TITLES4->SetText(L"Özel Rank");
	LAB_TITLES5->SetText(L"Event Takvimi");
}
void CIFMainMenu::On_Btn_EnglishLang()
{
	LAB_TITLES->SetText(L"Title Storage");
	LAB_TITLES1->SetText(L"Grant Name");
	LAB_TITLES2->SetText(L"Unique History");
	LAB_TITLES3->SetText(L"Character Lock");
	LAB_TITLES4->SetText(L"Custom Rank");
	LAB_TITLES5->SetText(L"Event Schedule");
}

int CIFMainMenu::OnChar(UINT nChar, UINT a2, UINT a3) {

    switch (nChar) {
        case 'b':
        case 'B': {
            if (this->IsVisible())
                this->ShowGWnd(false);
            else {
                this->ShowGWnd(true);
                this->ResetPosition();
            }
            return 1;
        }
            break;
    }
    return 0;
}