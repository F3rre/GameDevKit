#include "IFHelperBubbleWindow.h"
#include <BSLib\multibyte.h>
#include <sstream>
#include <TextStringManager.h>

void CIFHelperBubbleWindow::Write(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex)
{
    // Redirection to original client code
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, ForegroundColor, a4, FontIndex);
}

void CIFHelperBubbleWindow::WriteLine(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex)
{
    if (text.size() >= 4) {
        std::wstring unit = text.substr(text.size() - 4);

        if (text.find(L"price") != std::string::npos || text.find(L"Price") != std::string::npos || text.find(L"Coin") != std::string::npos)
        {
            std::wstring amountNumberText = text.substr(text.find(L" ") + 1);
            if (unit == L"Gold" || unit == L"Unit")
            {
                amountNumberText = text.substr(0, text.find(unit)).substr(text.find(L": ") + 1);
            }
            if (text.find(L"Store purchasing") != std::string::npos)
            {
                amountNumberText = text.substr(text.find(L"price ") + 6);
            }
            std::wstring unitName = text.substr(0, text.find(amountNumberText));

            std::stringstream buffer(acp_encode(amountNumberText));
            long unitAmount;
            buffer >> unitAmount;

            std::wstring commafiedAmount;
            int cnt = 0;
            do
            {
                commafiedAmount.insert(0, 1, char('0' + unitAmount % 10));
                unitAmount /= 10;
                if (++cnt == 3 && unitAmount)
                {
                    commafiedAmount.insert(0, 1, ',');
                    cnt = 0;
                }
            } while (unitAmount);

            text = unitName + L" " + commafiedAmount + L" ";
            UINT msgcolor = 0xffFF0000; //No Difference: FFFEFEFF | Better: FFFFD953 | Worse: FFFF4A4A
            ForegroundColor = msgcolor;
        }
    }
    if (text[0] == 'A') {

        UINT msgcolor = 0xffFF0000; //No Difference: FFFEFEFF | Better: FFFFD953 | Worse: FFFF4A4A
        ForegroundColor = msgcolor;
    }
    else if (text[0] == 'E') {

        UINT msgcolor = 0xff22ff00; //No Difference: FFFEFEFF | Better: FFFFD953 | Worse: FFFF4A4A
        ForegroundColor = msgcolor;
    }
    else if (text[0] == 'S') {

        UINT msgcolor = 0xffFF1493; //No Difference: FFFEFEFF | Better: FFFFD953 | Worse: FFFF4A4A
        ForegroundColor = msgcolor;
    }
    else if (text[0] == 'G') {

        UINT msgcolor = 0xffb739ff; //No Difference: FFFEFEFF | Better: FFFFD953 | Worse: FFFF4A4A
        ForegroundColor = msgcolor;
    }
    else if (text[0] == 'P') {

        UINT msgcolor = 0xff00FFFF; //No Difference: FFFEFEFF | Better: FFFFD953 | Worse: FFFF4A4A
        ForegroundColor = msgcolor;
    }


    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, ForegroundColor, a4, FontIndex);
}
