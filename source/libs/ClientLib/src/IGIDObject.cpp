#include "IGIDObject.h"

const std::n_wstring &CIGIDObject::GetName() const {
    return m_name;
}

unsigned __int32 CIGIDObject::GetUniqueID()
{
    return m_uniqueID;
}
void CIGIDObject::ChangeTitleColor(D3DCOLOR Color)
{
    fonttexture_title.SetColor(Color);
}

void CIGIDObject::ChangeNameColor(D3DCOLOR Color)
{
    fonttexture_playername.SetColor(Color);
}


void CIGIDObject::ChangeTitle(std::n_wstring Title)
{
    fonttexture_title.sub_8B3B60(&Title);
}

void CIGIDObject::ChangeName(std::n_wstring Name)
{
    fonttexture_playername.sub_8B3B60(&Name);
}