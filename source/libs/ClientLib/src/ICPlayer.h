#pragma once

#include "ICUser.h"
#include "SOItem.h"

class CICPlayer : public CICUser {
    GFX_DECLARE_DYNAMIC_EXISTING(CICPlayer, 0x00ef1b44)
public:

    bool IsGameMaster();

    std::n_wstring *sub_9D6580(std::n_wstring *str);

    /// \address 009d6580
    std::n_wstring GetCharName() const;

    void Render(void);
    bool CustomTitExists(const wchar_t* prefix);
    void AddCustomTitle(const wchar_t* prefix , const wchar_t* title);
    void RemoveCustomTitle(const wchar_t* prefix);
    bool CustomNameRankExists(const wchar_t* prefix);
    void AddCustomNameRank(const wchar_t* prefix, const wchar_t* title);
    void RemoveCustomNameRank(const wchar_t* prefix);
    bool CustomNameExists(const wchar_t* prefix);
    void AddCustomName(const wchar_t* prefix, const wchar_t* title);
    void RemoveCustomName(const wchar_t* prefix);
    bool TitleColorTitExists(const wchar_t* prefix);
    void AddTitleColor(const wchar_t* charname, int title);
    void RemoveTitleColor(const wchar_t* prefix);
    bool CharColorTitExists(const wchar_t* prefix);
    void AddCharColor(const wchar_t* charname, int title);
    void RemoveCharColor(const wchar_t* prefix);

private:
    char pad_082C[32]; //0x082C
    std::n_wstring m_charname; //0x084C
public:

    unsigned char m_level; //0x0868 level of your character, crashes when set too high
private:
    char pad_0869[7]; //0x0869
public:
    long long int m_exp_current; //0x0870
    int m_skillpoint_progress; //0x0878
private:
    short m_str_stat; //0x087C
    short m_int_stat; //0x087E
public:
    int m_skillpoint; //0x0880
private:
    short m_statpoint_available; //0x0884
    char pad_0886[26]; //0x0886
    CSOItem N0000947A; //0x08A0
    CSOItem N0000947B; //0x0A70
    CSOItem N0000947C; //0x0C40
    CSOItem N0000947D; //0x0E10
    CSOItem N0000947E; //0x0FE0
    CSOItem N0000947F; //0x11B0
    CSOItem N00009480; //0x1380
    CSOItem N00009481; //0x1550
    CSOItem N00009482; //0x1720
    CSOItem N00009483; //0x18F0
    CSOItem N00009484; //0x1AC0
    CSOItem N00009485; //0x1C90
    CSOItem N00009486; //0x1E60
    char pad_2030[96]; //0x2030
    char N000094A7; //0x2090 bit 0 = isGameMaster
    char pad_2091[135]; //0x2091


    BEGIN_FIXTURE()
//        ENSURE_SIZE(0x2118)

        ENSURE_OFFSET(m_charname, 0x084C)
        ENSURE_OFFSET(m_level, 0x0868)
        ENSURE_OFFSET(m_exp_current, 0x0870)
        ENSURE_OFFSET(m_skillpoint_progress, 0x0878)
        ENSURE_OFFSET(m_str_stat, 0x087C)
        ENSURE_OFFSET(m_int_stat, 0x087E)
        ENSURE_OFFSET(m_skillpoint, 0x0880)
        ENSURE_OFFSET(m_statpoint_available, 0x0884)

    END_FIXTURE()

    RUN_FIXTURE(CICPlayer)
};

#define g_pCICPlayer (*((CICPlayer**)0x00EEF5EC))
