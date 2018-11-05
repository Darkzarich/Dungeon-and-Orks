#pragma once

#include "consoleColor.h"

typedef const unsigned char obj;

const int rowsCount = 15;
const int columnsCount = 35;
const int levelCount = 1; // Counting with zero

obj CellSymbol_Empty       = ' ';
obj CellSymbol_Wall        = '#';
obj CellSymbol_Hero        = 'h';
obj CellSymbol_Exit        = 'e';
obj CellSymbol_Orc         = 'o';
obj CellSymbol_Skeleton    = 's';
obj CellSymbol_Stick       = '1';
obj CellSymbol_Club        = '2';
obj CellSymbol_Spear       = '3';
obj CellSymbol_Saber       = '4';
obj CellSymbol_Hp          = '~';
obj CellSymbol_Flail       = '5';
obj CellSymbol_Scythe      = '6';
obj CellSymbol_Claymore    = '7';
obj CellSymbol_ShadowDemon = 'K';

obj allLevels [ ][rowsCount][columnsCount+1] = {

                                            {

                                                "###################################",
                                                "#s##s      o  ~##o           s ~###",
                                                "# #####  3### ### ##~### ######## e",
                                                "# #  ~# ## ##  # o#####~      s   #",
                                                "# # ##  ##o           #############",
                                                "# #    ######## ## #####4        ##",
                                                "# # #### K    #o      s######### ##",
                                                "#   o# ##### ###### #### o  #   s##",
                                                "# #        #  o o          o##   ##",
                                                "# ### ##  ############ ######## ###",
                                                "#o##  #      #o #   #   o# ##    ##",
                                                "#  #2###  #####  #####         ####",
                                                "#######  ##~###   1##### ### ######",
                                                "# h             #         #~o #####",
                                                "###################################",
                                            },

                                            {

                                                "###################################",
                                                "#o    # o    o# #o  ~   #o       o#",
                                                "## ## ### ##### # ##### # ## ### ##",
                                                "#   o             #o      #   #   #",
                                                "##### ### ##### # ############## ##",
                                                "#o        #~o   #s               o#",
                                                "##### ############ #### ####### ###",
                                                "# ### ##s## ##      ##7  #s      o#",
                                                "#            #K6##  ####### #######",
                                                "# ##o ##5 ## #####  ##o          ##",
                                                "#o##########     #  ############ ##",
                                                "#         #### ~##  o    o#       #",
                                                "####### ################### ### ###",
                                                "#~                      o~#o#o   ~#",
                                                "################h##########e#######",
                                            }

                                            };

unsigned char GetRenderCellSymbol(unsigned char cellSymbol)
{
    switch(cellSymbol)
    {
        case CellSymbol_Empty:        return ' ';
        case CellSymbol_Wall:         return 219;
        case CellSymbol_Hero:         return 2;
        case CellSymbol_Orc:          return 2;
        case CellSymbol_Skeleton:     return 2;
        case CellSymbol_Stick:        return 47;
        case CellSymbol_Club:         return 33;
        case CellSymbol_Spear:        return 24;
        case CellSymbol_Saber:        return 108;
        case CellSymbol_Exit:         return 178;
        case CellSymbol_Hp:           return 3;
        case CellSymbol_Flail:        return 64;
        case CellSymbol_Scythe:       return 251;
        case CellSymbol_Claymore :    return 197;
        case CellSymbol_ShadowDemon : return 1;
    }

    return '?';
}

ConsoleColor GetRenderSymbolColor(unsigned char CellSymbol)
{
    switch(CellSymbol)
    {
        case CellSymbol_Empty:      return ConsoleColor_Black;
        case CellSymbol_Wall:       return ConsoleColor_Gray;
        case CellSymbol_Hero:       return ConsoleColor_Yellow;
        case CellSymbol_Exit:       return ConsoleColor_DarkRed;
        case CellSymbol_Orc:        return ConsoleColor_Green;
        case CellSymbol_Skeleton:   return ConsoleColor_White;
        case CellSymbol_Stick:      return ConsoleColor_DarkYellow;
        case CellSymbol_Club:       return ConsoleColor_DarkRed;
        case CellSymbol_Spear:      return ConsoleColor_DarkCyan;
        case CellSymbol_Saber:      return ConsoleColor_Cyan;
        case CellSymbol_Hp:         return ConsoleColor_Red;
        case CellSymbol_Flail:      return ConsoleColor_DarkGray;
        case CellSymbol_Scythe:     return ConsoleColor_Cyan;
        case CellSymbol_Claymore :  return ConsoleColor_Magenta;
        case CellSymbol_ShadowDemon:return ConsoleColor_Red;
    }

    return ConsoleColor_Gray;
}

ConsoleColor GetRenderSymbolColorDark(unsigned char CellSymbol)
{
    switch(CellSymbol)
    {
        case CellSymbol_Wall:       return ConsoleColor_DarkGray;
        case CellSymbol_Exit:       return ConsoleColor_DarkRed;
        case CellSymbol_Stick:      return ConsoleColor_DarkYellow;
        case CellSymbol_Club:       return ConsoleColor_DarkRed;
        case CellSymbol_Spear:      return ConsoleColor_DarkCyan;
        case CellSymbol_Saber:      return ConsoleColor_DarkCyan;
        case CellSymbol_Hp:         return ConsoleColor_DarkRed;
        case CellSymbol_Flail:      return ConsoleColor_DarkGray;
        case CellSymbol_Scythe:     return ConsoleColor_DarkCyan;
        case CellSymbol_Claymore :  return ConsoleColor_DarkMagenta;
    }

    return ConsoleColor_Gray;
}
