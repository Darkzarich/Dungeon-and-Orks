#pragma once

#include "level.h"

enum WeaponType
{
    WeaponType_None,
    WeaponType_Fist,
    WeaponType_Stick,
    WeaponType_Club,
    WeaponType_Spear,
    WeaponType_Saber,
    WeaponType_Flail,
    WeaponType_Scythe,
    WeaponType_Claymore,
    WeaponType_Dark,
};

const char* WeaponName_None     = "None";
const char* WeaponName_Fist     = "Fist";
const char* WeaponName_Stick    = "Stick";
const char* WeaponName_Club     = "Club";
const char* WeaponName_Spear    = "Spear";
const char* WeaponName_Saber    = "Saber";
const char* WeaponName_Flail    = "Flail";
const char* WeaponName_Scythe   = "Scythe";
const char* WeaponName_Claymore = "Claymore";

const char* GetWeaponName(WeaponType weaponType)
{
    switch(weaponType)
    {
        case WeaponType_Fist:        return WeaponName_Fist;
        case WeaponType_Stick:       return WeaponName_Stick;
        case WeaponType_Club:        return WeaponName_Club;
        case WeaponType_Spear:       return WeaponName_Spear;
        case WeaponType_Saber:       return WeaponName_Saber;
        case WeaponType_Flail:       return WeaponName_Flail;
        case WeaponType_Scythe:      return WeaponName_Scythe;
        case WeaponType_Claymore:    return WeaponName_Claymore;
    }
}

int GetWeaponDamage(WeaponType wt)
{
    switch(wt)
    {
        case WeaponType_Fist:        return 2;
        case WeaponType_Stick:       return 16;
        case WeaponType_Club:        return 24;
        case WeaponType_Spear:       return 32;
        case WeaponType_Saber:       return 40;
        case WeaponType_Flail:       return 48;
        case WeaponType_Scythe:      return 60;
        case WeaponType_Claymore:    return 100;
        case WeaponType_Dark:        return 400;
    }

    return 0;
}

int GetWeaponDamageRange(WeaponType wt)
{
    if (wt == WeaponType_Dark)
    {
        return 400;
    }
    return (GetWeaponDamage(wt)*0.7)+(rand()%(int(GetWeaponDamage(wt)*0.5)));
}

WeaponType GetWeaponTypeFromCell(unsigned char cellSymbol)
{
    switch(cellSymbol)
    {
        case CellSymbol_Stick:    return WeaponType_Stick;
        case CellSymbol_Club:     return WeaponType_Club;
        case CellSymbol_Spear:    return WeaponType_Spear;
        case CellSymbol_Saber:    return WeaponType_Saber;
        case CellSymbol_Flail:    return WeaponType_Flail;
        case CellSymbol_Scythe:   return WeaponType_Scythe;
        case CellSymbol_Claymore: return WeaponType_Claymore;
    }

    return WeaponType_None;
}
