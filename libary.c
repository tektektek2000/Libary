#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"
#include "libary.h"

BOOK bookinit()
{
    BOOK original;
    original.author = datainit();
    original.title = datainit();
    original.ryear = datainit();
    original.topic = datainit();
    return original;
}

LIBARY libaryinit()
{
    LIBARY original;
    original.numberofbooks=0;
    return original;
}

void copybook(BOOK *copy, BOOK original)
{
    copydata(&((*copy).author),original.author);
    copydata(&((*copy).title),original.title);
    copydata(&((*copy).ryear),original.ryear);
    copydata(&((*copy).topic),original.topic);
    (*copy).id=original.id;
}

void bookvipe(BOOK *original)
{
    datavipe(&((*original).author));
    datavipe(&((*original).title));
    datavipe(&((*original).ryear));
    datavipe(&((*original).topic));
}

void libaryvipe(LIBARY *original)
{
    for(int i=0;i<(*original).numberofbooks;i++)
    {
        bookvipe(&((*original).Books[i]));
    }
}

void expandlibary(LIBARY *original,BOOK newb)
{
    BOOK *newlib;


    (*original).numberofbooks++;
    newlib = (BOOK*) malloc((*original).numberofbooks * sizeof(BOOK));
    for(int i=0;i<(*original).numberofbooks-1;i++)
    {
        copybook(&(newlib[i]),(*original).Books[i]);
    }
    copybook(&newlib[((*original).numberofbooks-1)],newb);
    newlib[((*original).numberofbooks-1)].id=(*original).numberofbooks-1;
    free((*original).Books);
    (*original).Books=newlib;
}

void readdatabase(LIBARY *original,char *filename)
{
    LIBARY Input;
    FILE* fp;
    char c;
    int i;
    DATA olvas;

    if((*original).numberofbooks>0)
    {
        libaryvipe(&(*original));
        (*original) = libaryinit();
    }
    if ((fp = fopen(filename, "r")) == NULL)
    { /* Open source file. */
        perror("fopen source-file");
    }
    i=0;
    Input = libaryinit();
    olvas=datainit();
    while (1)
    {
        if(feof(fp))
        {
            break;
        }
        c = getc(fp);
        if(c != '\n' && c!='\t')
        {
            expanddata(&olvas,c);
        }
        else
        {
            if(c=='\t')
            {
                //Do your conversions and other stuff here

                switch(i)
                {
                case 0:
                    expandlibary(&Input,bookinit());
                    copydata(&(Input.Books[Input.numberofbooks-1].author),olvas);
                    break;
                case 1:
                    copydata(&(Input.Books[Input.numberofbooks-1].title),olvas);
                    break;
                case 2:
                    copydata(&(Input.Books[Input.numberofbooks-1].ryear),olvas);
                    break;
                case 3:
                    printf("lol?");
                    break;
                }
                datavipe(&olvas);
                olvas=datainit();
                i++;
            }
            if(c=='\n')
            {
                //Do your conversions and other stuff here
                copydata(&(Input.Books[Input.numberofbooks-1].topic),olvas);
                datavipe(&olvas);
                olvas=datainit();
                i=0;
            }
        }
    }
    fclose(fp);
    (*original).Books = (BOOK*) malloc(Input.numberofbooks * sizeof(BOOK));
    for(int j=0;j<Input.numberofbooks;j++)
    {
        copybook(&((*original).Books[j]),Input.Books[j]);
    }
    (*original).numberofbooks=Input.numberofbooks;
    libaryvipe(&(Input));
}

void writedatabase(LIBARY Output,char *filename)
{
    FILE* fp;
    if ((fp = fopen(filename, "wt")) == NULL)
    { /* Open source file. */
        perror("fopen source-file");
    }
    for(int i=0;i<Output.numberofbooks;i++)
    {
        fprintf(fp,"%s\t%s\t%s\t%s\n",Output.Books[i].author.data,Output.Books[i].title.data,Output.Books[i].ryear.data,Output.Books[i].topic.data);
    }
    fclose(fp);
}

void printdatabase(LIBARY Output)
{
    for(int i=0;i<Output.numberofbooks;i++)
    {
        printf("%s\t%s\t%s\t%s\n",Output.Books[i].author.data,Output.Books[i].title.data,Output.Books[i].ryear.data,Output.Books[i].topic.data);
    }
}

unsigned short comparedata(DATA A,DATA B)
{
    unsigned short fakebool;

    if(A.length<B.length)
    {
        return 0;
    }
    fakebool=1;
    for(int i=0;i<B.length-1;i++)
    {
        if(tolower(A.data[i]) != tolower(B.data[i]))
        {
            fakebool=0;
            break;
        }
    }
    return fakebool;
}

LIBARY shearch(LIBARY db,Mode selected,DATA phrase)
{
    int *ids;
    int number=0;
    LIBARY results=libaryinit();

    ids = (int*) malloc(1 * sizeof(int));
    ids[0]=-1;
    for(int i=0;i<db.numberofbooks;i++)
    {
        switch(selected)
        {
            case Author:
                if(comparedata(db.Books[i].author,phrase)==1)
                {
                    if(ids[0]==-1)
                    {
                        ids[0]=i;
                        number=1;
                    }
                    else
                    {
                        number++;
                        ids = (int*) realloc(ids, number * sizeof(int));
                        ids[number-1]=i;
                    }
                }
                break;
            case Title:
                if(comparedata(db.Books[i].title,phrase)==1)
                {
                    if(ids[0]==-1)
                    {
                        ids[0]=i;
                        number=1;
                    }
                    else
                    {
                        number++;
                        ids = (int*) realloc(ids, number * sizeof(int));
                        ids[number-1]=i;
                    }
                }
                break;
            case RealaseYear:
                if(comparedata(db.Books[i].ryear,phrase)==1)
                {
                    if(ids[0]==-1)
                    {
                        ids[0]=i;
                        number=1;
                    }
                    else
                    {
                        number++;
                        ids = (int*) realloc(ids, number * sizeof(int));
                        ids[number-1]=i;
                    }
                }
                break;
            case Topic:
                if(comparedata(db.Books[i].topic,phrase)==1)
                {
                    if(ids[0]==-1)
                    {
                        ids[0]=i;
                        number=1;
                    }
                    else
                    {
                        number++;
                        ids = (int*) realloc(ids, number * sizeof(int));
                        ids[number-1]=i;
                    }
                }
                break;
        }
    }
    results.numberofbooks=number;
    results.Books = (BOOK*) malloc(results.numberofbooks * sizeof(BOOK));
    for(int i=0;i<results.numberofbooks;i++)
    {
        copybook(&(results.Books[i]),db.Books[ids[i]]);
    }
    return results;
}

void libarydelete(LIBARY *original,int id)
{
    BOOK *newlib;

    (*original).numberofbooks--;
    newlib = (BOOK*) malloc((*original).numberofbooks * sizeof(BOOK));
    for(int i=0;i<id;i++)
    {
        copybook(&(newlib[i]),(*original).Books[i]);
    }
    for(int i=id;i<(*original).numberofbooks;i++)
    {
        copybook(&(newlib[i]),(*original).Books[i+1]);
    }
    free((*original).Books);
    (*original).Books=newlib;
}

void createdatabase(LIBARY *original)
{
    (*original).numberofbooks=0;
}

DATA BookToData(BOOK A)
{
    DATA Result;

    Result=mergedata(A.author,A.title,'|');
    Result=mergedata(Result,A.ryear,'|');
    Result=mergedata(Result,A.topic,'|');
    return Result;
}

void libarycopy(LIBARY *copy,LIBARY original)
{
    if((*copy).numberofbooks>0)
    {
        libaryvipe(copy);
    }
    (*copy)=libaryinit();
    for(int i=0;i<original.numberofbooks;i++)
    {
        expandlibary(copy,original.Books[i]);
    }
}
