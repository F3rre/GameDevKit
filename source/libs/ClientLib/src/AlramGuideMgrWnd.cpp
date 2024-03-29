#include "AlramGuideMgrWnd.h"

#include "IFConfirmReputationGuide.h"
#include "IFEventGuide.h"
#include "IFQuestInfoGuide.h"
#include "IFLetterAlarmGuide.h"
#include "IFServerEventGuide.h"
#include "IFOpenMarketAlramGuide.h"
#include "IFEventGuideSecond.h"
#include "IFflorian0Guide.h"

GFX_IMPLEMENT_DYNAMIC_EXISTING(CAlramGuideMgrWnd, 0x00ee99a8)

#define GUIDE_CONFIRMREPUTATION 165
#define GUIDE_EVENT 41
#define GUIDE_QUESTINFO 46
#define GUIDE_LETTERALARM 55
#define GUIDE_SERVEREVENT  179
#define GUIDE_OPENMARKETALRAM  198
#define GUIDE_EVENTSECOND  30006

CAlramGuideMgrWnd::CAlramGuideMgrWnd() :
        m_numberOfIcons(0) {

}

CGWnd *CAlramGuideMgrWnd::GetGuide(int windowId) {

    // Try to find the element in the list
    for (std::list<CGWnd *>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if ((*it)->UniqueID() == windowId) {
            return *it;
        }
    }

    // List did not contain the element, try to create it
    RECT rect = {0,0, 0x28,0x28};

    CGWnd* pObj = 0;

    switch(windowId) {
        case GUIDE_CONFIRMREPUTATION:
            pObj = CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFConfirmReputationGuide), rect, GUIDE_CONFIRMREPUTATION, 0);
            break;

        case GUIDE_EVENT:
            pObj = CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventGuide), rect, GUIDE_EVENT, 0);
            break;

        case GUIDE_QUESTINFO:
            pObj = CreateInstance(this, GFX_RUNTIME_CLASS(CIFQuestInfoGuide), rect, GUIDE_QUESTINFO, 0);
            break;

        case GUIDE_LETTERALARM:
            pObj = CreateInstance(this, GFX_RUNTIME_CLASS(CIFLetterAlarmGuide), rect, GUIDE_LETTERALARM, 0);
            break;

        case GUIDE_SERVEREVENT:
            pObj = CreateInstance(this, GFX_RUNTIME_CLASS(CIFServerEventGuide), rect, GUIDE_SERVEREVENT, 0);
            break;

        case GUIDE_OPENMARKETALRAM:
            pObj = CreateInstance(this, GFX_RUNTIME_CLASS(CIFOpenMarketAlramGuide), rect, GUIDE_OPENMARKETALRAM, 0);
            break;

        case GUIDE_EVENTSECOND:
            pObj = CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventGuideSecond), rect, GUIDE_EVENTSECOND, 0);
            break;

        case GUIDE_MAINMENU:
            pObj = CreateInstance(this, GFX_RUNTIME_CLASS(CIFflorian0Guide), rect, GUIDE_MAINMENU, 0);
            break;

        case GUIDE_DISCORD:
            pObj = CreateInstance(this, GFX_RUNTIME_CLASS(CIFflorian0Guide), rect, GUIDE_DISCORD, 0);
            break;

        case GUIDE_FACEBOOK:
            pObj = CreateInstance(this, GFX_RUNTIME_CLASS(CIFflorian0Guide), rect, GUIDE_FACEBOOK, 0);
            break;
        case GUIDE_WEB:
            pObj = CreateInstance(this, GFX_RUNTIME_CLASS(CIFflorian0Guide), rect, GUIDE_WEB, 0);
            break;
        case GUIDE_RELOAD:
            pObj = CreateInstance(this, GFX_RUNTIME_CLASS(CIFflorian0Guide), rect, GUIDE_RELOAD, 0);
            break;
        default:
            assert(false);
    }

    m_list.push_back(pObj);
    m_numberOfIcons++;

    UpdatePositions();

    return pObj;
}

void CAlramGuideMgrWnd::UpdatePositions() {
    reinterpret_cast<void(__thiscall*)(CAlramGuideMgrWnd*)>(0x0065c430)(this);
}
