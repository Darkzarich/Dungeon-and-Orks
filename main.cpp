#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>

#include "consoleColor.h"
#include "level.h"
#include "weaponType.h"
#include "unitType.h"
#include "unitData.h"

#define MAX_SIZE_STATUS 128

// Constants
const int maxUnitCount = 35;

// Logic variables
HANDLE console = 0;
bool isGameActive = true;

unsigned char levelData[rowsCount][columnsCount];
UnitData unitsData[maxUnitCount];
int unitsCount = 0;
int heroIndex = 0;

int currentLevel = 0;

char fullStatus[MAX_SIZE_STATUS];
char currentStatus[128];

UnitData GlobalHero;

unsigned char fogOfWar[rowsCount][columnsCount];

// Core

void SetupSystem()
{
    srand(time(NULL));
    memset(fullStatus, 0, MAX_SIZE_STATUS);
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    // hide cursor
    CONSOLE_CURSOR_INFO inf;
    inf.dwSize = 1;
    inf.bVisible = 0;
    SetConsoleCursorInfo(console, &inf);

    currentLevel = 0;
    isGameActive = true;
}

bool DistanseForFogOfWar_1(int r, int c)
{
    if (
        (unitsData[heroIndex].row == r && unitsData[heroIndex].column == c) ||
        (unitsData[heroIndex].row == r && unitsData[heroIndex].column+1 == c) ||
        (unitsData[heroIndex].row == r && unitsData[heroIndex].column-1 == c) ||
        (unitsData[heroIndex].row == r+1 && unitsData[heroIndex].column == c) ||
        (unitsData[heroIndex].row == r+1 && unitsData[heroIndex].column-1 == c) ||
        (unitsData[heroIndex].row == r+1 && unitsData[heroIndex].column+1 == c) ||
        (unitsData[heroIndex].row == r-1 && unitsData[heroIndex].column == c) ||
        (unitsData[heroIndex].row == r-1 && unitsData[heroIndex].column-1 == c) ||
        (unitsData[heroIndex].row == r-1 && unitsData[heroIndex].column+1 == c)
       )
        {
            return false;
        }
    return true;
}

void FillFogOfWar()
{
    fogOfWar[unitsData[heroIndex].row][unitsData[heroIndex].column] = 2;
    fogOfWar[unitsData[heroIndex].row][unitsData[heroIndex].column+1] = 2;
    fogOfWar[unitsData[heroIndex].row][unitsData[heroIndex].column-1] = 2;
    fogOfWar[unitsData[heroIndex].row+1][unitsData[heroIndex].column] = 2;
    fogOfWar[unitsData[heroIndex].row+1][unitsData[heroIndex].column-1] = 2;
    fogOfWar[unitsData[heroIndex].row+1][unitsData[heroIndex].column+1] = 2;
    fogOfWar[unitsData[heroIndex].row-1][unitsData[heroIndex].column] = 2;
    fogOfWar[unitsData[heroIndex].row-1][unitsData[heroIndex].column-1] = 2;
    fogOfWar[unitsData[heroIndex].row-1][unitsData[heroIndex].column+1] = 2;

    for(int i = 0; i<rowsCount; i++)
    {
        for(int j = 0; j < columnsCount; j++)
        {
            if (fogOfWar[i][j] != 1 && fogOfWar[i][j] != 2)
            {
                fogOfWar[i][j] = 0;
            }
            else if (fogOfWar[i][j] == 2 && DistanseForFogOfWar_1(i, j))
            {
                fogOfWar[i][j] = 1;
            }
        }
    }
}

void Initialize()
{
    unitsCount = 0;
    memset(fullStatus, 0, MAX_SIZE_STATUS);

    for(int i = 0; i<rowsCount; i++)
    {
        for(int j = 0; j < columnsCount; j++)
        {
            fogOfWar[i][j] = 0;
            unsigned char cell = allLevels[currentLevel][i][j];
            levelData[i][j] = cell;

            switch(cell)
            {
                case CellSymbol_Hero:
                    heroIndex = unitsCount;
                case CellSymbol_Orc:
                case CellSymbol_ShadowDemon:
                case CellSymbol_Skeleton:
                {
                    UnitType ut = GetUnitTypeFromCell(cell);
                    unitsData[unitsCount].type = ut;
                    unitsData[unitsCount].row = i;
                    unitsData[unitsCount].column = j;
                    unitsData[unitsCount].weapon = GetUnitDefaultWeapon(ut);
                    unitsData[unitsCount].health = GetUnitDefaultHealth(ut);
                    if(currentLevel == 0 && ut == UnitType_Hero)
                    {
                        GlobalHero = unitsData[heroIndex];
                    }
                    else if (ut == UnitType_Hero)
                    {
                        unitsData[heroIndex].weapon = GlobalHero.weapon;
                        unitsData[heroIndex].health = GlobalHero.health;
                    }
                    unitsCount++;
                    break;
                }
            }
        }
    }
}

void Render()
{
    COORD cursor;
    cursor.X = 0;
    cursor.Y = 0;
    SetConsoleCursorPosition(console, cursor);

    SetConsoleTextAttribute(console, ConsoleColor_Green);
    printf("\n\t\t  DUNGEONS AND ORKS\n\t");
    SetConsoleTextAttribute(console, ConsoleColor_DarkGray);
    printf("\n\t\t      Level: %i\n\t", currentLevel+1);

    SetConsoleTextAttribute(console, ConsoleColor_Red);
    printf("\n\tHP: %i  ", unitsData[heroIndex].health);

    SetConsoleTextAttribute(console, ConsoleColor_Cyan);
    printf("  Weapon: ");
    SetConsoleTextAttribute(console, ConsoleColor_White);
    printf("%s ", GetWeaponName(unitsData[heroIndex].weapon));
    SetConsoleTextAttribute(console, ConsoleColor_DarkGray);
    printf("(Dmg: %i - %i)         \n\n\t",
                int(GetWeaponDamage(unitsData[heroIndex].weapon)*0.7),
                int(GetWeaponDamage(unitsData[heroIndex].weapon)*0.7)+(int(GetWeaponDamage(unitsData[heroIndex].weapon)*0.5)));

    FillFogOfWar();

    for(int i = 0; i<rowsCount; i++)
    {
        for(int j = 0; j < columnsCount; j++)
        {
            if (fogOfWar[i][j] == 0)
            {
                SetConsoleTextAttribute(console, ConsoleColor_DarkGray);
                printf("%c", 178);
            }
            else if (fogOfWar[i][j] == 1)
            {
                SetConsoleTextAttribute(console, GetRenderSymbolColorDark(levelData[i][j]));
                if (GetRenderCellSymbol(levelData[i][j]) == GetRenderCellSymbol(CellSymbol_Orc) ||
                    GetRenderCellSymbol(levelData[i][j]) == GetRenderCellSymbol(CellSymbol_Skeleton) ||
                    GetRenderCellSymbol(levelData[i][j]) == GetRenderCellSymbol(CellSymbol_ShadowDemon)
                    )
                {
                    printf("%c", ' ');
                    continue;
                }
                printf("%c", GetRenderCellSymbol(levelData[i][j]));
            }
            else
            {
                SetConsoleTextAttribute(console, GetRenderSymbolColor(levelData[i][j]));
                printf("%c", GetRenderCellSymbol(levelData[i][j]));
            }
        }
    printf("\n\t");
    }

    // Fill status message with spaces
    while(strlen(fullStatus) < 160)
    {
        strcat(fullStatus, " ");
    }
    SetConsoleTextAttribute(console, ConsoleColor_Yellow);
    printf("\n\n\t%s", fullStatus);

    // Clear status message
    fullStatus[0] = 0;

    if (unitsData[heroIndex].health <= 0)
    {
        SetConsoleTextAttribute(console, ConsoleColor_Red);
        printf("\n\tHERO IS DEAD");
        getch();
        getch();
        isGameActive = false;
    }
    else if(unitsData[heroIndex].health < GetUnitDefaultHealth(unitsData[heroIndex].type))
    {
        unitsData[heroIndex].health++;
    }
}

void MoveUnitTo(UnitData* unit, int row, int column)
{
    if (unit->health <= 0)
    {
        return;
    }

    unsigned char unitSymbol = levelData[unit->row][unit->column];
    unsigned char destinationSymbol = levelData[row][column];
    bool canMoveToCell = false;

    switch(destinationSymbol)
    {
        // Empty Cell
        case CellSymbol_Empty:
        {
            canMoveToCell = true;
            break;
        }
        case CellSymbol_Hero:
        case CellSymbol_Orc:
        case CellSymbol_ShadowDemon:
        case CellSymbol_Skeleton:
        {
            UnitType destinationUnitType = GetUnitTypeFromCell(destinationSymbol);

            if(unit->type != destinationUnitType)
            {
                for(int i = 0; i < unitsCount; i++)
                {
                    if (unitsData[i].health <= 0)
                    {
                        continue;
                    }

                    if (unitsData[i].row == row && unitsData[i].column == column)
                    {
                        int damage = GetWeaponDamageRange(unit->weapon);
                        unitsData[i].health -= damage;
                        sprintf(currentStatus, " %s dealt %i damage to %s.",
                        GetUnitName(unit->type), GetWeaponDamageRange(unit->weapon), GetUnitName(unitsData[i].type));
                        strcat(fullStatus, currentStatus);
                        if (unitsData[i].health <= 0.0f)
                        {
                            sprintf(currentStatus, " %s died.", GetUnitName(unitsData[i].type));
                            strcat(fullStatus, currentStatus);
                            levelData[row][column] = CellSymbol_Empty;
                        }

                        break;
                    }
                }
            }

            break;
        }
    }

    if (unit->type == UnitType_Hero)
    {
        switch(destinationSymbol)
        {
            case CellSymbol_Hp:
                if (unitsData[heroIndex].health < GetUnitDefaultHealth(unitsData[heroIndex].type))
                {
                    unitsData[heroIndex].health += 50;
                    sprintf(currentStatus, "Hero to repair one's health!");
                    strcat(fullStatus, currentStatus);
                    if (unitsData[heroIndex].health > GetUnitDefaultHealth(unitsData[heroIndex].type))
                    {
                        unitsData[heroIndex].health = GetUnitDefaultHealth(unitsData[heroIndex].type);
                    }
                }
                canMoveToCell = true;
                break;
            case CellSymbol_Stick:
            case CellSymbol_Club:
            case CellSymbol_Spear:
            case CellSymbol_Scythe:
            case CellSymbol_Claymore:
            case CellSymbol_Flail:
            case CellSymbol_Saber:
            {
                canMoveToCell = true;

                WeaponType thisWeapon = GetWeaponTypeFromCell(destinationSymbol);
                if (unitsData[heroIndex].weapon < thisWeapon)
                {
                    unitsData[heroIndex].weapon = thisWeapon;
                    sprintf(currentStatus, " Hero found %s.", GetWeaponName(thisWeapon));
                    strcat(fullStatus, currentStatus);
                    levelData[row][column] = CellSymbol_Empty;
                }
                break;
            }
            case CellSymbol_Exit:
            {
                if (currentLevel == levelCount)
                {
                    isGameActive = false;
                    break;
                }
                else
                {
                    currentLevel += 1;
                    GlobalHero.weapon = unitsData[heroIndex].weapon;
                    GlobalHero.health = unitsData[heroIndex].health;
                    Initialize();
                    break;
                }
            }
        }
    }

    if (canMoveToCell)
    {
        levelData[unit->row][unit->column] = CellSymbol_Empty;

        unit->row = row;
        unit->column = column;

        levelData[unit->row][unit->column] = unitSymbol;
    }
}

void UpdateAI()
{
    for(int i = 0; i < unitsCount; i++)
    {
        if (unitsData[i].type == UnitType_Hero || unitsData[i].health <= 0)
        {
            continue;
        }

        int heroDistanceR = abs(unitsData[heroIndex].row-unitsData[i].row);
        int heroDistanceC = abs(unitsData[heroIndex].column-unitsData[i].column);

        if (heroDistanceR+heroDistanceC == 1)
        {
            MoveUnitTo(&unitsData[i], unitsData[heroIndex].row, unitsData[heroIndex].column);
        }
        else
        {
            switch(rand()%4)
            {
                case 0: MoveUnitTo(&unitsData[i], unitsData[i].row+1, unitsData[i].column); break;
                case 1: MoveUnitTo(&unitsData[i], unitsData[i].row-1, unitsData[i].column); break;
                case 2: MoveUnitTo(&unitsData[i], unitsData[i].row, unitsData[i].column+1); break;
                case 3: MoveUnitTo(&unitsData[i], unitsData[i].row, unitsData[i].column-1); break;
            }
            if (unitsData[i].type == UnitType_ShadowDemon)
            {
                switch(rand()%4)
                {
                    case 0: MoveUnitTo(&unitsData[i], unitsData[i].row+1, unitsData[i].column); break;
                    case 1: MoveUnitTo(&unitsData[i], unitsData[i].row-1, unitsData[i].column); break;
                    case 2: MoveUnitTo(&unitsData[i], unitsData[i].row, unitsData[i].column+1); break;
                    case 3: MoveUnitTo(&unitsData[i], unitsData[i].row, unitsData[i].column-1); break;
                }

                if (rand()%3 == 0)
                {
                    int tp_row = rand()%16;
                    int tp_column = rand()%36;
                    if (levelData[tp_row][tp_column] == CellSymbol_Empty)
                    {
                        MoveUnitTo(&unitsData[i], tp_row, tp_column);
                    }
                }
            }
        }
    }
}

void Update()
{
    unsigned char inp = getch();
    inp = tolower(inp);

    switch(inp)
    {
        case 'w':
        {
           MoveUnitTo(&unitsData[heroIndex], unitsData[heroIndex].row-1, unitsData[heroIndex].column);
           break;
        }
        case 's':
        {
           MoveUnitTo(&unitsData[heroIndex], unitsData[heroIndex].row+1, unitsData[heroIndex].column);
           break;
        }
        case 'a':
        {
           MoveUnitTo(&unitsData[heroIndex], unitsData[heroIndex].row, unitsData[heroIndex].column-1);
           break;
        }
        case 'd':
        {
           MoveUnitTo(&unitsData[heroIndex], unitsData[heroIndex].row, unitsData[heroIndex].column+1);
           break;
        }
        case 'r':
        {
            Initialize();
            break;
        }
    }

    UpdateAI();

}

void Shutdown()
{
    system("cls");
    if (unitsData[heroIndex].health > 0)
    {
        SetConsoleTextAttribute(console, ConsoleColor_Green);
        printf("\n\n\tAll level completed!");
        printf("\n\n\tGame over!");
        getch();
        exit(0);
    }
    else
    {
        printf("\n\n\tGame over... Play again!");
        getch();
        SetupSystem();
        Initialize();
    }

}

int main()
{
    SetupSystem();
    Initialize();
    while(1)
    {
        while(isGameActive)
        {
            Render();
            Update();
        }

        Shutdown();
    }

    return 0;
}
