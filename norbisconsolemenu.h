#ifndef NORBISCONSOLEMENU_H_INCLUDED
#define NORBISCONSOLEMENU_H_INCLUDED
#include "database.h"

typedef enum MenuResultType{IsMenu = 0, IsFunction = 1}MenuResultType;

typedef struct MenuResult{
    MenuResultType type;
    unsigned int calledid;
}MenuResult;

typedef struct Menu{
    DATA name;
    DATA toptext;
    unsigned int id;
    unsigned int *callablemenuids;
    unsigned int numberofmenuids;
    unsigned int *callablefunctionids;
    unsigned int numberoffunctionids;
} Menu;

typedef struct Function{
    DATA name;
    unsigned int id;
}Function;

Menu *Menus;
unsigned int numberofmenus;
Function *Functions;
unsigned int numberoffunctions;
void VipeMenus();
void MenuInit();
void CreateMenus(unsigned int i);
void CreateFunctions(unsigned int i);
MenuResult CallMenu(Menu called,int callerid);
#endif // NORBISCONSOLEMENU_H_INCLUDED
