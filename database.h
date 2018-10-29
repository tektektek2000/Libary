#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef enum Mode {Author = 0, Title = 1, RealaseYear = 2, Topic = 3} Mode;

typedef struct DATA{
int length;
char *data;
}DATA;



DATA stringtodata(char *str);
DATA datainit();
void expanddata(DATA (*original),char newc);
void copydata(DATA *copy,DATA original);
void datavipe(DATA *original);
DATA mergedata(DATA A,DATA B,char bufferc);
DATA readline();
DATA freadline(FILE *fp);
DATA cutdata(DATA A,int sid,int eid);

#endif // DATABASE_H_INCLUDED
