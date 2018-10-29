#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"
#include "libary.h"
#include "norbisconsolemenu.h"

#define BaseFunctions 6 //this is the number of functions that don't belong to any specified Book but rather are globally available
#define pp '"'

char filename[FILENAME_MAX];
int quit=0;

void LoadFromDB(LIBARY *Konyvtar)
{

    MenuResult result;
    CreateMenus(1);
    Menus[0].id=0;
    Menus[0].numberoffunctionids=2;
    Menus[0].callablefunctionids=(int*)malloc(2 *(sizeof(int)));
    Menus[0].callablefunctionids[0]=0;
    Menus[0].callablefunctionids[1]=1;
    Menus[0].numberofmenuids=0;
    Menus[0].toptext=stringtodata("Please Select");
    CreateFunctions(2);
    Functions[0].id=0;
    Functions[0].name=stringtodata("Create Database");
    Functions[1].id=0;
    Functions[1].name=stringtodata("Read Database");
    result = CallMenu(Menus[0],-1);
    switch(result.calledid)
    {
    case 0:
        system("cls");
        printf("Please name your database\n");
        scanf("%s",filename);
        createdatabase(Konyvtar);
        break;
    case 1:
        system("cls");
        ChooseFile();
        readdatabase(&(*Konyvtar),filename);
        break;
    }

    return Konyvtar;
}

void ModifyBook(BOOK *A)
{
    MenuResult result;
    char input[128];
    int end=0;

    VipeMenus();
    CreateMenus(1);
    CreateFunctions(5);
    Menus[0].numberoffunctionids=5;
    Menus[0].toptext=stringtodata("Modify");
    Menus[0].callablefunctionids=(int*)malloc(5 *(sizeof(int)));
    for(int i=0;i<5;i++)
    {
        Menus[0].callablefunctionids[i]=i;
    }
    Functions[0].name=mergedata(stringtodata("Author's name"),(*A).author,':');
    Functions[1].name=mergedata(stringtodata("Title"),(*A).title,':');
    Functions[2].name=mergedata(stringtodata("Year of Realease"),(*A).ryear,':');
    Functions[3].name=mergedata(stringtodata("Topic"),(*A).topic,':');
    Functions[4].name=stringtodata("Save");
    while(end!=1)
    {
        result=CallMenu(Menus[0],-1);
        switch(result.calledid)
        {
        case 0:
            system("cls");
            printf("Enter the new author\n");
            (*A).author=readline();
            Functions[0].name=mergedata(stringtodata("Author's name"),(*A).author,':');
            break;
        case 1:
            system("cls");
            printf("Enter the new title\n");
            (*A).title=readline();
            Functions[1].name=mergedata(stringtodata("Title"),(*A).title,':');
            break;
        case 2:
            system("cls");
            printf("Enter the new year of realase\n");
            (*A).ryear=readline();
            Functions[2].name=mergedata(stringtodata("Year of Realease"),(*A).ryear,':');
            break;
        case 3:
            system("cls");
            printf("Enter the new topic\n");
            (*A).topic=readline();
            Functions[3].name=mergedata(stringtodata("Topic"),(*A).topic,':');
            break;
        case 4:
            end=1;
            break;
        }
    }

}

void EstablishUI(LIBARY Konyvtar,unsigned int isshearch)
{
    if(isshearch!=0)
    {
        isshearch=1;
    }
    CreateMenus(2+Konyvtar.numberofbooks-isshearch);
    CreateFunctions(BaseFunctions+(Konyvtar.numberofbooks*2)-(BaseFunctions*isshearch));
    for(int i=0;i<Konyvtar.numberofbooks;i++)
    {
        Menus[i+2-isshearch].name=BookToData(Konyvtar.Books[i]);
        copydata(&Menus[i+2-isshearch].toptext,Konyvtar.Books[i].title);
        Menus[i+2-isshearch].numberoffunctionids=2;
        Menus[i+2-isshearch].callablefunctionids=(int*)malloc(2 *(sizeof(int)));
        Menus[i+2-isshearch].callablefunctionids[0]=BaseFunctions-(BaseFunctions*isshearch)+i;
        Menus[i+2-isshearch].callablefunctionids[1]=BaseFunctions-(BaseFunctions*isshearch)+Konyvtar.numberofbooks+i;
        Menus[i+2-isshearch].numberofmenuids=0;
        Functions[BaseFunctions+i-(BaseFunctions*isshearch)].name=stringtodata("Modify");
        Functions[BaseFunctions-(BaseFunctions*isshearch)+Konyvtar.numberofbooks+i].name=stringtodata("Delete");

    }
    //BaseFunctions
    if(isshearch==0)
    {
        Menus[1].name=stringtodata("Actions");
        Menus[1].toptext=stringtodata("Actions");
        Menus[1].numberoffunctionids=BaseFunctions;
        Menus[1].callablefunctionids=(int*)malloc(BaseFunctions *(sizeof(int)));
        Menus[1].numberofmenuids=0;
        for(int i=0;i<BaseFunctions;i++)
        {
            Menus[1].callablefunctionids[i]=i;
        }
        Functions[0].name=stringtodata("Add Book");
        Functions[1].name=stringtodata("Load New Libary");
        Functions[2].name=stringtodata("Delete Everything");
        Functions[3].name=stringtodata("Save Progress");
        Functions[4].name=stringtodata("Shearch");
        Functions[5].name=stringtodata("Quit");
    }
    Menus[0].name=stringtodata("Base");
    Menus[0].toptext=stringtodata("Libary");
    Menus[0].numberoffunctionids=0;
    Menus[0].numberofmenuids=numberofmenus-1;
    Menus[0].callablemenuids=(int*)malloc((numberofmenus-1) *(sizeof(int)));
    for(int i=0;i<numberofmenus-1;i++)
    {
        Menus[0].callablemenuids[i]=i+1;
    }

}

void shearchfunction(LIBARY *Konyvtar)
{
    MenuResult result;
    Mode selected;
    char input[128];
    int end=0;
    DATA A;
    LIBARY results;
    int callerid;
    int newcallerid;

    VipeMenus();
    CreateMenus(1);
    CreateFunctions(5);
    Menus[0].numberoffunctionids=5;
    Menus[0].toptext=stringtodata("Please select the category in which you wish to shearch");
    Menus[0].callablefunctionids=(int*)malloc(5 *(sizeof(int)));
    for(int i=0;i<5;i++)
    {
        Menus[0].callablefunctionids[i]=i;
    }
    Functions[0].name=stringtodata("Author's name");
    Functions[1].name=stringtodata("Title");
    Functions[2].name=stringtodata("Year of Realease");
    Functions[3].name=stringtodata("Topic");
    Functions[4].name=stringtodata("Back");
    result=CallMenu(Menus[0],-1);
    system("cls");
    printf("Enter the shearchphrase\n");
    switch(result.calledid)
    {
    case 0:
        A=readline();
        selected=Author;
        break;
    case 1:
        A=readline();
        selected=Title;
        break;
    case 2:
        A=readline();
        selected=RealaseYear;
        break;
    case 3:
        A=readline();
        selected=Topic;
        break;
    case 4:
        break;
    }
    if(result.calledid!=4)
    {
        results=shearch(*Konyvtar,selected,A);
        VipeMenus();
        EstablishUI(results,1);
        Menus[0].toptext=stringtodata("Shearch results:");
        result.calledid=0;
        result.type=IsMenu;
        end=0;
        while(end!=1)
        {
            if(result.calledid==0)
            {
                result=CallMenu(Menus[result.calledid],(2*results.numberofbooks));
                newcallerid=0;
            }
            else
            {
                newcallerid=result.calledid;
                result=CallMenu(Menus[result.calledid],callerid);
            }
            switch(result.type)
            {
            case IsMenu:
                if(result.calledid!=2*results.numberofbooks)
                {
                    callerid=newcallerid;
                }
                else
                {
                    end=1;
                }
                break;
            case IsFunction:
                if(result.calledid<results.numberofbooks)
                {
                    ModifyBook(&((*Konyvtar).Books[results.Books[result.calledid].id]));
                }
                else
                {
                    libarydelete(Konyvtar,results.Books[result.calledid-results.numberofbooks].id);
                }
                end=1;
                break;
            }
        }
    }
}

void CallFunction(unsigned int id,LIBARY *Konyvtar)
{
    BOOK A;

    if(id<BaseFunctions)
    {
        switch(id)
        {
        case 0:
            A=bookinit();
            ModifyBook(&A);
            expandlibary(Konyvtar,A);
            bookvipe(&A);
            break;
        case 1:
            libaryvipe(Konyvtar);
            (*Konyvtar)=libaryinit();
            LoadFromDB(Konyvtar);
            break;
        case 2:
            libaryvipe(Konyvtar);
            (*Konyvtar)=libaryinit();
            break;
        case 3:
            writedatabase(*Konyvtar,filename);
            break;
        case 4:
            shearchfunction(Konyvtar);
            break;
        case 5:
            quit=1;
            break;
        }
    }
    else
    {
        if(id<BaseFunctions+(*Konyvtar).numberofbooks)
        {
            ModifyBook(&((*Konyvtar).Books[id-BaseFunctions]));
        }
        else
        {
           libarydelete(Konyvtar,(id-BaseFunctions-(*Konyvtar).numberofbooks));
        }
    }
    VipeMenus();
    EstablishUI((*Konyvtar),0);
}

void ChooseFile()
{
    DATA input;
    DATA dir;
    DATA *files;
    DATA *copy;
    int numberoffiles=0;
    FILE* fp;
    MenuResult result;

    fp = fopen("dir.bat","wt");
    fprintf(fp,"@echo off\ndir\necho ");
    fprintf(fp,"%c",pp);
    fprintf(fp,"                       <END>");
    fprintf(fp,"%c",pp);
    fclose(fp);
    fp = popen("dir.bat","r");
    for(int i=0;i<4;i++)
    {
        input = freadline(fp);
    }
    while(1)
    {
        if(feof(fp))
        {
            break;
        }
        input = freadline(fp);
        dir = cutdata(input,24,29);
        if(comparedata(dir,stringtodata("<END>"))==1)
        {
            break;
        }
        input = cutdata(input,39,input.length);
        if(comparedata(dir,stringtodata("<DIR>"))==0)
        {
            numberoffiles++;
            copy = (DATA*)malloc(numberoffiles *(sizeof(DATA)));
            for(int i=0;i<numberoffiles-1;i++)
            {
                copydata(&copy[i],files[i]);
            }
            copydata(&copy[numberoffiles-1],input);
            if(numberoffiles>1)
            {
                free(files);
            }
            files=copy;

        }
        //printf("%s | %s\n",input.data,dir.data);
    }
    numberoffiles-=2;
    copy = (DATA*)malloc((numberoffiles) *(sizeof(DATA)));
    for(int i=0;i<numberoffiles;i++)
    {
        copydata(&(copy[i]),files[i]);
    }
    if(numberoffiles>0)
    {
        free(files);
    }
    files=copy;
    fclose(fp);
    VipeMenus();
    CreateMenus(1);
    CreateFunctions(numberoffiles);
    Menus[0].numberoffunctionids=numberoffiles;
    Menus[0].toptext=stringtodata("Please select the file");
    Menus[0].callablefunctionids=(int*)malloc(numberoffiles *(sizeof(int)));
    for(int i=0;i<numberoffiles;i++)
    {
        Menus[0].callablefunctionids[i]=i;
    }
    for(int i=0;i<numberoffiles;i++)
    {
        copydata(&Functions[i].name,files[i]);
    }
    result=CallMenu(Menus[0],-1);
    for(int i=0;i<files[result.calledid].length;i++)
    {
        filename[i]=files[result.calledid].data[i];
    }
    for(int i=0;i<numberoffiles;i++)
    {
        datavipe(&files[i]);
    }
    free(files);
    VipeMenus();
}

int main()
{
    LIBARY Konyvtar;
    LIBARY shearched;
    Mode selected;
    Konyvtar=libaryinit();
    MenuResult result;
    int callerid;
    int newcallerid;


    MenuInit();
    LoadFromDB(&Konyvtar);
    EstablishUI(Konyvtar,0);
    result.calledid=0;
    result.type=IsMenu;
    callerid=0;
    while(quit!=1)
    {
        if(result.calledid==0)
        {
            result=CallMenu(Menus[result.calledid],-1);
            newcallerid=0;
        }
        else
        {
            newcallerid=result.calledid;
            result=CallMenu(Menus[result.calledid],callerid);
        }
        switch(result.type)
        {
        case IsMenu:
            callerid=newcallerid;
            break;
        case IsFunction:
            CallFunction(result.calledid,&Konyvtar);
            result.calledid=0;
            result.type=IsMenu;
            callerid=-1;
            break;
        }
    }
    /*
    //SetConsoleTitle("Konyvtar 0.2.1");
    readdatabase(&Konyvtar);
    //shearched=shearch(Konyvtar,Topic,stringtodata("ph"));
    printdatabase(Konyvtar);
    shearched=libarydelete(Konyvtar,0);
    printdatabase(shearched);
    //writedatabase(Konyvtar);*/
    return 0;
}
