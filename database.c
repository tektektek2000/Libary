#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

char tolower(char a)
{
    if(a<91 && a>64)
    {
        a+=32;
    }
    return a;
}

DATA stringtodata(char *str)
{
    DATA dat;
    int i=0;

    while(str[i]!='\0')
    {
        i++;
    }
    i++;
    dat.length = i;
    dat.data = (char*)malloc(dat.length *(sizeof(char)));
    for(i=0;i<dat.length;i++)
    {
        dat.data[i]=str[i];
    }
    return dat;
}

DATA datainit()
{
    DATA original;
    original.length=1;
    original.data = (char*) malloc(1 * sizeof(char));
    original.data[0]='\0';
    return original;
}

void expanddata(DATA (*original),char newc)
{
    char *newstr;


    (*original).length++;
    newstr = (char*) malloc((*original).length * sizeof(char));
    for(int i=0;i<(*original).length-2;i++)
    {
        newstr[i]=(*original).data[i];
    }
    newstr[(*original).length-2]=newc;
    newstr[(*original).length-1]='\0';
    free((*original).data);
    (*original).data=newstr;
}

void copydata(DATA *copy,DATA original)
{
    (*copy).data = (char*) malloc(original.length * sizeof(char));
    for(int i=0;i<original.length;i++)
    {
        (*copy).data[i]=original.data[i];
    }
    (*copy).length=original.length;
}

void datavipe(DATA *original)
{
    free((*original).data);
    (*original).length=0;
}

DATA mergedata(DATA A,DATA B,char bufferc)
{
    DATA C;

    C.length=A.length+B.length;
    C.data = (char*)malloc(C.length *(sizeof(char)));
    for(int i=0;i<A.length-1;i++)
    {
        C.data[i]=A.data[i];
    }
    C.data[A.length-1]=bufferc;
    for(int i=0;i<B.length;i++)
    {
        C.data[i+A.length]=B.data[i];
    }
    return C;
}

DATA readline()
{
    DATA line=datainit();
    char c;
    int previouslinecanceller=0;

    while (1)
    {
        c = getc(stdin);
        if(c=='\n')
        {
            if(previouslinecanceller!=0)
            {
                break;
            }
        }
        else
        {
            expanddata(&line,c);
        }
        previouslinecanceller++;
    }

    return line;
}

DATA freadline(FILE *fp)
{
    DATA line=datainit();
    char c;
    int previouslinecanceller=0;

    while (1)
    {
        c = getc(fp);
        if(c=='\n')
        {
            if(previouslinecanceller!=0)
            {
                break;
            }
        }
        else
        {
            expanddata(&line,c);
        }
        previouslinecanceller++;
    }

    return line;
}

DATA cutdata(DATA A,int sid,int eid)
{
    DATA B=datainit();

    B.length=eid-sid+1;
    if(eid==A.length)
    {
        B.length--;
    }
    B.data = (char*) malloc(B.length * sizeof(char));
    for(int i=0;i<B.length;i++)
    {
        B.data[i]=A.data[i+sid];
    }
    B.data[B.length-1]='\0';
    return B;
}


