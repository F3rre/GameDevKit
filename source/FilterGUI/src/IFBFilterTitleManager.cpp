#include "IFBFilterTitleManager.h"
#include <ctime>
#include <GInterface.h>
#include <ICPlayer.h>
#include <CPSMission.h>

#define BFILTER_TManager_TITLES_BUTTON 10
#define BFILTER_TManager_GARNTNAME_BUTTON 11
#define BFILTER_TManager_UNIQUELOG_BUTTON 12
#define BFILTER_TManager_PVPMATCH_BUTTON 13
#define BFILTER_TManager_RANK_BUTTON 14
#define BFILTER_TManager_EVENTTIMER_BUTTON 15

#define BFILTER_TManager_FRAME 1
#define BFILTER_TManager_NORMALTITLE 2
#define BFILTER_TManager_CUSTOM 4
#define BFILTER_TManager_SWITCHTITLE 3

GFX_IMPLEMENT_DYNCREATE(CIFTitleManager, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFTitleManager, CIFMainFrame)
ONG_COMMAND(100, &CIFTitleManager::OnUnknownStuff)
ONG_COMMAND(101, &CIFTitleManager::OnUnknownStuff)
GFX_END_MESSAGE_MAP()


CIFTitleManager::CIFTitleManager(void)
{
	printf("> " __FUNCTION__ "\n");
    m_pTabs = 0;
}


CIFTitleManager::~CIFTitleManager(void)
{
	printf("> " __FUNCTION__ "\n");
    if (m_pTabs) {
        free(m_pTabs);
        m_pTabs = 0;
    }
}

bool CIFTitleManager::OnCreate(long ln)
{
	printf("> " __FUNCTION__ "(%d)\n", ln);

	// Populate inherited members
	CIFMainFrame::OnCreate(ln);

	m_IRM.LoadFromFile("resinfo\\ifbfiltertitlemanager.txt");
	m_IRM.CreateInterfaceSection("Create", this);

	NormalTitle = m_IRM.GetResObj<CIFStatic>(BFILTER_TManager_NORMALTITLE, 1);
	Frame = m_IRM.GetResObj<CIFFrame>(BFILTER_TManager_FRAME, 1);
	Custom = m_IRM.GetResObj<CIFCustomTitle>(BFILTER_TManager_CUSTOM, 1);
    Switch = m_IRM.GetResObj<CIFSwitchTitle>(BFILTER_TManager_SWITCHTITLE, 1);

    Frame->SetGWndSize(this->GetBounds().size.width - 20, this->GetBounds().size.height - 75);
    Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 65);
    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);

    NormalTitle->SetGWndSize(Frame->GetBounds().size.width - 20, Frame->GetBounds().size.height - 20);
    NormalTitle->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);

    m_title->SetText(L"Title Manager");

    m_pTabs = new CIFSelectableArea * [numberOfTabs];

    for (int i = 0; i < numberOfTabs; i++) {

        RECT selectable_area_size;
        selectable_area_size.top = 0;
        selectable_area_size.left = tabMarginLeft + tabWidth * i;
        selectable_area_size.right = tabWidth + 1;
        selectable_area_size.bottom = tabHeight;

        m_pTabs[i] = (CIFSelectableArea*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSelectableArea),
            selectable_area_size, tabFirstId + i, 0);

        m_pTabs[0]->MoveGWnd(Frame->GetBounds().pos.x + 10, Frame->GetBounds().pos.y - 23);
        //m_pTabs[1]->MoveGWnd(Frame->GetBounds().pos.x + 87, Frame->GetBounds().pos.y + 20);

        m_pTabs[i]->SetFont(this->N00009C2F);

        m_pTabs[i]->sub_64CE30("interface\\option\\opt_long_tab_on.ddj",
            "interface\\option\\opt_long_tab_off.ddj", "interface\\ifcommon\\com_long_tab_disable.ddj");

        if (i)
        {
            if (i == 1)
            {
                m_pTabs[1]->SetText(L"Custom Title");
                m_pTabs[1]->MoveGWnd(Frame->GetBounds().pos.x + 105, Frame->GetBounds().pos.y - 23);
            }
            m_pTabs[i]->sub_64CC30(0);
        }
        else
        {
            m_pTabs[0]->SetText(L"Switch Title");
            m_pTabs[i]->sub_64CC30(1);
        }
    }

	this->ShowGWnd(false);
    Custom->ShowGWnd(false);
    Custom->MoveGWnd(Frame->GetBounds().pos.x-20, Frame->GetBounds().pos.y);
    Custom->m_mybutton2->ShowGWnd(false);
    Custom->m_custom_label5->ShowGWnd(false);
    Custom->m_custom_label6->ShowGWnd(false);
    Custom->m_mybutton->TB_Func_13("interface\\system\\sys_button.ddj", 0, 0);
    Custom->m_mybutton->SetGWndSize(Custom->m_mybutton->GetBounds().size.width+90, Custom->m_mybutton->GetBounds().size.height);

    Switch->ShowGWnd(true);
    Switch->MoveGWnd(Frame->GetBounds().pos.x + 10, Frame->GetBounds().pos.y);
    Switch->Frame->ShowGWnd(false);
    Switch->m_custom_label3->ShowGWnd(false);

    ResetPosition();
	return true;
}

void CIFTitleManager::OnUnknownStuff() {
    int id = GetIDOfInterfaceUnderCursor();
    int i = 0;

    for (int i = 0; i < numberOfTabs; ++i) {
        if (id == m_pTabs[i]->UniqueID()) {
            ActivateTabPage(i);
            return;
        }
    }
}

void CIFTitleManager::ActivateTabPage(BYTE page) {

    for (int i = 0; i < numberOfTabs; i++) {
        if (i == page)
            continue;

        m_pTabs[i]->sub_64CC30(0);
    }

    m_pTabs[page]->sub_64CC30(1);

    switch (page)
    {
    case 0:
        Switch->ShowGWnd(true);
        Custom->ShowGWnd(false);
        Custom->m_edit->SetText(L"");
        Custom->m_custom_label3->SetText(L"");
        break;
    case 1:
        Custom->ShowGWnd(true);
        Switch->ShowGWnd(false);
        Switch->m_textbox->m_LinesOfHistory = 0;
        Switch->m_custom_label2->SetText(L"");
        break;
    }
}

void CIFTitleManager::OnUpdate()
{
}

void CIFTitleManager::ResetPosition()
{
    if (!CPSMission::Gui_CustomTitle)
    {
        m_pTabs[1]->ShowGWnd(false);
        Custom->ShowGWnd(false);
    }
    else
    {
        if (CPSMission::Gui_CustomTitle && CPSMission::Gui_SwitchTitle)
            ActivateTabPage(0);

        m_pTabs[1]->ShowGWnd(true);
        ActivateTabPage(1);
    }

    if (!CPSMission::Gui_SwitchTitle)
    {
        m_pTabs[0]->ShowGWnd(false);
        Switch->ShowGWnd(false);
    }
    else
    {
        m_pTabs[0]->ShowGWnd(true);
        ActivateTabPage(0);
    }

	USHORT PosX = 0, PosY = 165;
	PosX = CLIENT_SCREEN_WIDTH - 750;
	this->MoveGWnd(PosX, PosY);
}