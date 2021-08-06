#pragma once

#include "IObject.h"

#include <GFX3DFunction/GFontTexture.h>

class CIGIDObject : public CIObject {
public:
    virtual void Func_18();

    virtual void Func_19();

    virtual void BringToFront();

    virtual void Func_21();

    virtual void Func_22();

    virtual void Func_23();

    virtual void Func_24();

    virtual void Func_25();

    virtual void Func_26();

    virtual void Func_27();

    virtual void Func_28();

    virtual void Func_29();

    virtual void Func_30();

    virtual void Func_31();

    virtual void Func_32();

    virtual void Func_33();

    void ChangeTitleColor(D3DCOLOR Color);
    void ChangeNameColor(D3DCOLOR Color);
    void ChangeTitle(std::n_wstring Title);
    void ChangeName(std::n_wstring Name);
public:
    /// \brief Get the assigned name of this object
    const std::n_wstring &GetName() const;
    /// Get Unique ID differenciating all objects in map
    unsigned __int32 GetUniqueID();
private:
    char pad_00DC[28]; //0x00DC
    unsigned __int32 m_uniqueID; // 0x00F8
    char pad_00FC[20]; //0x00FC
    std::n_wstring m_name; //0x0110
    CGFontTexture fonttexture_playername; //0x012C
    char pad_0194[28]; //0x0194
    CGFontTexture fonttexture_title; //0x01B0
    char pad_0218[60]; //0x0218

BEGIN_FIXTURE()
        ENSURE_SIZE(0x254)

        ENSURE_OFFSET(m_name, 0x110)
        ENSURE_OFFSET(fonttexture_playername, 0x12c)
        ENSURE_OFFSET(fonttexture_title, 0x1b0)

    END_FIXTURE()

    RUN_FIXTURE(CIGIDObject)
};
