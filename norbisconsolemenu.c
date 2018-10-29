#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "norbisconsolemenu.h"
#include "database.h"

int userinput()
{
    char c;
    int i;

    c='a';
    while(c=='a')
    {
        c = getch();
        switch(c)
        {
        case 72:
            i=-1;
            break;
        case 80:
            i=1;
            break;
        case 13:
            i=0;
            break;
        default:
            c='a';
            break;
        }
    }
    return i;
}


void MenuInit()
{
    numberoffunctions=0;
    numberofmenus=0;
}

void MenuCreated(Menu *A)
{
    (*A).name=datainit();
    (*A).toptext=datainit();
    (*A).numberofmenuids=0;
    (*A).numberoffunctionids=0;
}

void FunctionCreated(Function *A)
{
    (*A).name=datainit();
}

void CreateMenus(unsigned int i)
{
    if(numberofmenus>0)
    {
        free(Menus);
    }
    numberofmenus=i;
    Menus=(Menu*) malloc(i * sizeof(Menu));
    for(int j=0;j<i;j++)
    {
        MenuCreated(&Menus[j]);
        Menus[j].id=j;
    }
}

void CreateFunctions(unsigned int i)
{
    if(numberoffunctions>0)
    {
        free(Functions);
    }
    numberoffunctions=i;
    Functions=(Function*) malloc(i * sizeof(Function));
    for(int j=0;j<i;j++)
    {
        FunctionCreated(&Functions[j]);
        Functions[j].id=j;
    }
}

void VipeMenus()
{
    for(int i=0;i<numberofmenus;i++)
    {
        if(Menus[i].numberofmenuids>0)
        {
            free(Menus[i].callablemenuids);
        }
        if(Menus[i].numberoffunctionids>0)
        {
            free(Menus[i].callablefunctionids);
        }
    }
    if(numberofmenus>0)
    {
        free(Menus);
    }
    if(numberoffunctions>0)
    {
        free(Menus);
    }
}

MenuResult CallMenu(Menu called,int callerid)
{
    int selected; //Stores the id of the function or menu on which the cursor currently is
    unsigned short backbool; //Determines if there is an option to go back to the previous menu
    MenuResult result;

    system("cls");
    if(callerid<0)
    {
        selected=0;
        backbool=0;
    }
    else
    {
        selected=-1;
        backbool=1;
    }
    while(1)
    {
        printf("%s\n",called.toptext.data);
        if(backbool==1)
        {
            if(selected==-1)
            {
                printf(">|");
            }
            else
            {
                printf(" |");
            }
            printf("Back\n");
        }
        for(int i=0;i<called.numberofmenuids;i++)
        {
            if(selected==i)
            {
                printf(">|");
            }
            else
            {
                printf(" |");
            }
            printf("%s\n",Menus[called.callablemenuids[i]].name.data);
        }
        for(int i=0;i<called.numberoffunctionids;i++)
        {
            if(selected-called.numberofmenuids==i)
            {
                printf(">|");
            }
            else
            {
                printf(" |");
            }
            printf("%s\n",Functions[called.callablefunctionids[i]].name.data);
        }
        switch(userinput())
        {
        case 1:
            if(selected<(int)(called.numberofmenuids+called.numberoffunctionids-1))
            {
                selected++;
            }
            else
            {
                selected=0-backbool;
            }
            break;
        case -1:
            if(selected>0-backbool)
            {
                selected--;
            }
            else
            {
                selected=(int)(called.numberofmenuids+called.numberoffunctionids-1);
            }
            break;
        case 0:
            if(selected<called.numberofmenuids && selected!=-1)
            {
                result.type=IsMenu;
                result.calledid=called.callablemenuids[selected];
            }
            if(selected>=called.numberofmenuids && selected!=-1)
            {
                result.type=IsFunction;
                result.calledid=called.callablefunctionids[selected-called.numberofmenuids];
            }
            if(selected==-1)
            {
                result.type=IsMenu;
                result.calledid=callerid;
            }
            return result;
            break;
        }
        system("cls");
    }
}
