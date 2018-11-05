#pragma once

#include "level.h"
#include "weaponType.h"

enum UnitType
{
    UnitType_None,
    UnitType_Hero,
    UnitType_Orc,
    UnitType_Skeleton,
    UnitType_ShadowDemon,
};

const char* UnitName_None     = "None";
const char* UnitName_Hero     = "Hero";
const char* UnitName_Orc      = "Orc";
const char* UnitName_Skeleton = "Skeleton";
const char* UnitName_ShadowDemon = "Shadow Demon";

const char* GetUnitName(UnitType ut)
{
    switch(ut)
    {
        case UnitType_Hero:        return UnitName_Hero;
        case UnitType_Orc:         return UnitName_Orc;
        case UnitType_Skeleton:    return UnitName_Skeleton;
        case UnitType_ShadowDemon: return UnitName_ShadowDemon;
    }

    return UnitName_None;
}

WeaponType GetUnitDefaultWeapon(UnitType ut)
{
    switch(ut)
    {
        case UnitType_Hero:        return WeaponType_Fist;
        case UnitType_Orc:         return WeaponType_Club;
        case UnitType_Skeleton:    return WeaponType_Saber;
        case UnitType_ShadowDemon: return WeaponType_Dark;
    }

    return WeaponType_None;
}

int GetUnitDefaultHealth(UnitType ut)
{
    switch(ut)
    {
        case UnitType_Hero:        return 400;
        case UnitType_Orc:         return 60;
        case UnitType_Skeleton:    return 80;
        case UnitType_ShadowDemon: return 3000;
    }

    return 0;
}

UnitType GetUnitTypeFromCell(unsigned char cellSymbol)
{
    switch(cellSymbol)
    {
        case CellSymbol_Hero:          return UnitType_Hero;
        case CellSymbol_Orc:           return UnitType_Orc;
        case CellSymbol_Skeleton:      return UnitType_Skeleton;
        case CellSymbol_ShadowDemon:   return UnitType_ShadowDemon;
    }

    return UnitType_None;
}
