#include "ICPlayer.h"
#include <IFPlayerMiniInfo.h>
#include <GInterface.h>
#include <MainMenu/IFBFilterMainMenu.h>

GFX_IMPLEMENT_DYNAMIC_EXISTING(CICPlayer, 0x00ef1b44)

std::map<std::n_wstring, std::n_wstring> CustomTitle;
std::map<std::n_wstring, std::n_wstring> CustomCharnameRank;
std::map<std::n_wstring, std::n_wstring> CustomCharname;

std::map<std::n_wstring, int> TitleColor;
std::map<std::n_wstring, int> CharnameColor;

std::map<std::n_wstring, std::n_wstring>::iterator CustomTitleIt;
std::map<std::n_wstring, int>::iterator TitleColorIt;

std::map<std::n_wstring, int>::iterator CharnameColorIt;
std::map<std::n_wstring, std::n_wstring>::iterator CustomCharnameRankIt;
std::map<std::n_wstring, std::n_wstring>::iterator CustomCharnameIt;


wchar_t buffer[255];
std::n_wstring mymsg;

wchar_t CustomTitlebuffer[255];
std::n_wstring CustomTitleStr;

// CICPlayer::IsGameMasterMAYBE(void) .text 009D4C40 00000009   R . . . . T .
bool CICPlayer::IsGameMaster() {
    return N000094A7 & 1;
}

// sub_9D6580 .text 009D6580 00000032 00000008 00000004 R . . . . T .
// I am pretty sure this func simply returned a copy of the players name ... ridiculous!
std::n_wstring* CICPlayer::sub_9D6580(std::n_wstring* str) {
    return reinterpret_cast<std::n_wstring * (__thiscall*)(CICPlayer*, std::n_wstring*)>(0x9D6580)(this, str);
}

std::n_wstring CICPlayer::GetCharName() const {
    return m_charname;
}


void CICPlayer::Render()
{
    if (!CPSMission::Gui_ColorsRender)
    {
        reinterpret_cast<void(__thiscall*)(CICPlayer*)>(0x009D87C0)(this); //Render
    }

    CLASSLINK_LOOP_BEGIN(CICUser)
        TitleColorIt = TitleColor.find(obj->GetName().c_str());
        if (TitleColorIt != TitleColor.end())
        {
            obj->ChangeTitleColor(TitleColorIt->second);
        }

        CharnameColorIt = CharnameColor.find(obj->GetName().c_str());
        if (CharnameColorIt != CharnameColor.end())
        {
            obj->ChangeNameColor(CharnameColorIt->second);
        }
        CustomTitleIt = CustomTitle.find(obj->GetName().c_str());
        if (CustomTitleIt != CustomTitle.end())
        {
            if (CustomTitleIt->second.length() > 0)
            {
                swprintf_s(CustomTitlebuffer, sizeof(CustomTitlebuffer), L"%s ", CustomTitleIt->second.c_str());
                CustomTitleStr.assign(CustomTitlebuffer);
                obj->ChangeTitle(CustomTitleStr.c_str());
            }
        }
        CustomCharnameRankIt = CustomCharnameRank.find(obj->GetName().c_str());
        if (CustomCharnameRankIt != CustomCharnameRank.end())
        {
            swprintf_s(buffer, sizeof(buffer), L"<%s> %s", CustomCharnameRankIt->second.c_str(), obj->GetName().c_str());
            mymsg.assign(buffer);
            obj->ChangeName(mymsg.c_str());
        }

        CustomCharnameIt = CustomCharname.find(obj->GetName().c_str());
        if (CustomCharnameIt != CustomCharname.end())
        {
            obj->ChangeTitle(L" ");
            obj->ChangeName(CustomCharnameIt->second.c_str());
        }
    CLASSLINK_LOOP_END(CICUser)

    reinterpret_cast<void(__thiscall*)(CICPlayer*)>(0x009D87C0)(this); //Render
}

bool CICPlayer::CustomTitExists(const wchar_t* prefix)
{
    for (std::map<std::n_wstring, std::n_wstring>::iterator iter = CustomTitle.begin(); iter != CustomTitle.end(); iter++)
    {
        if (wcscmp(iter->first.c_str(), prefix) == 0)
            return true;
    }
    return false;
}

void CICPlayer::AddCustomTitle(const wchar_t* prefix , const wchar_t* title)
{
    if (!CICPlayer::CustomTitExists(prefix))
        CustomTitle.insert(std::pair<std::n_wstring, std::n_wstring>(prefix, title));
    else
    {
        for (std::map<std::n_wstring, std::n_wstring>::iterator iter = CustomTitle.begin(); iter != CustomTitle.end(); iter++)
        {
            if (wcscmp(iter->first.c_str(), prefix) == 0)
            {
                iter->second = title;
                return;
            }
        }
    }
}

void CICPlayer::RemoveCustomTitle(const wchar_t* prefix)
{
    if (!CustomTitExists(prefix))
        return;

    for (std::map<std::n_wstring, std::n_wstring>::iterator iter = CustomTitle.begin(); iter != CustomTitle.end(); iter++)
    {
        if (wcscmp(iter->first.c_str(), prefix) == 0)
        {
            CustomTitle.erase(iter->first);
        }
        break;
    }
}

bool CICPlayer::CustomNameRankExists(const wchar_t* prefix)
{
    for (std::map<std::n_wstring, std::n_wstring>::iterator iter = CustomCharnameRank.begin(); iter != CustomCharnameRank.end(); iter++)
    {
        if (wcscmp(iter->first.c_str(), prefix) == 0)
            return true;
    }
    return false;
}


void CICPlayer::AddCustomNameRank(const wchar_t* prefix, const wchar_t* title)
{
    if (!CICPlayer::CustomNameRankExists(prefix))
        CustomCharnameRank.insert(std::pair<std::n_wstring, std::n_wstring>(prefix, title));
    else
    {
        for (std::map<std::n_wstring, std::n_wstring>::iterator iter = CustomCharnameRank.begin(); iter != CustomCharnameRank.end(); iter++)
        {
            if (wcscmp(iter->first.c_str(), prefix) == 0)
            {
                iter->second = title;
                return;
            }
        }
    }
}

void CICPlayer::RemoveCustomNameRank(const wchar_t* prefix)
{
    if (!CustomNameRankExists(prefix))
        return;

    for (std::map<std::n_wstring, std::n_wstring>::iterator iter = CustomCharnameRank.begin(); iter != CustomCharnameRank.end(); iter++)
    {
        if (wcscmp(iter->first.c_str(), prefix) == 0)
        {
            CustomCharnameRank.erase(iter->first);
        }
        break;
    }
}


bool CICPlayer::CustomNameExists(const wchar_t* prefix)
{
    for (std::map<std::n_wstring, std::n_wstring>::iterator iter = CustomCharname.begin(); iter != CustomCharname.end(); iter++)
    {
        if (wcscmp(iter->first.c_str(), prefix) == 0)
            return true;
    }
    return false;
}


void CICPlayer::AddCustomName(const wchar_t* prefix, const wchar_t* title)
{
    if (!CICPlayer::CustomNameExists(prefix))
        CustomCharname.insert(std::pair<std::n_wstring, std::n_wstring>(prefix, title));
    else
    {
        for (std::map<std::n_wstring, std::n_wstring>::iterator iter = CustomCharname.begin(); iter != CustomCharname.end(); iter++)
        {
            if (wcscmp(iter->first.c_str(), prefix) == 0)
            {
                iter->second = title;
                return;
            }
        }
    }
}

void CICPlayer::RemoveCustomName(const wchar_t* prefix)
{
    if (!CustomNameExists(prefix))
        return;

    for (std::map<std::n_wstring, std::n_wstring>::iterator iter = CustomCharname.begin(); iter != CustomCharname.end(); iter++)
    {
        if (wcscmp(iter->first.c_str(), prefix) == 0)
        {
            CustomCharname.erase(iter->first);
        }
        break;
    }
}

bool CICPlayer::TitleColorTitExists(const wchar_t* prefix)
{
    for (std::map<std::n_wstring, int>::iterator iter = TitleColor.begin(); iter != TitleColor.end(); iter++)
    {
        if (wcscmp(iter->first.c_str(), prefix) == 0)
            return true;
    }
    return false;
}


void CICPlayer::AddTitleColor(const wchar_t* charname, int title)
{
    if (!CICPlayer::TitleColorTitExists(charname))
        TitleColor.insert(std::pair<std::n_wstring, int>(charname, title));
    else
    {
        for (std::map<std::n_wstring, int>::iterator iter = TitleColor.begin(); iter != TitleColor.end(); iter++)
        {
            if (wcscmp(iter->first.c_str(), charname) == 0)
            {
                iter->second = title;
                return;
            }
        }
    }
}

void CICPlayer::RemoveTitleColor(const wchar_t* prefix)
{
    if (!TitleColorTitExists(prefix))
        return;

    for (std::map<std::n_wstring, int>::iterator iter = TitleColor.begin(); iter != TitleColor.end(); iter++)
    {
        if (wcscmp(iter->first.c_str(), prefix) == 0)
        {
            TitleColor.erase(iter->first);
        }
        break;
    }
}

bool CICPlayer::CharColorTitExists(const wchar_t* prefix)
{
    for (std::map<std::n_wstring, int>::iterator iter = CharnameColor.begin(); iter != CharnameColor.end(); iter++)
    {
        if (wcscmp(iter->first.c_str(), prefix) == 0)
            return true;
    }
    return false;
}


void CICPlayer::AddCharColor(const wchar_t* charname, int title)
{
    if (!CICPlayer::CharColorTitExists(charname))
        CharnameColor.insert(std::pair<std::n_wstring, int>(charname, title));
    else
    {
        for (std::map<std::n_wstring, int>::iterator iter = CharnameColor.begin(); iter != CharnameColor.end(); iter++)
        {
            if (wcscmp(iter->first.c_str(), charname) == 0)
            {
                iter->second = title;
                return;
            }
        }
    }
}

void CICPlayer::RemoveCharColor(const wchar_t* prefix)
{
    if (!CharColorTitExists(prefix))
        return;

    for (std::map<std::n_wstring, int>::iterator iter = CharnameColor.begin(); iter != CharnameColor.end(); iter++)
    {
        if (wcscmp(iter->first.c_str(), prefix) == 0)
        {
            CharnameColor.erase(iter->first);
        }
        break;
    }
}