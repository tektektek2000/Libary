#ifndef LIBARY_H_INCLUDED
#define LIBARY_H_INCLUDED
#include "database.h"

typedef struct BOOK{
DATA author;
DATA title;
DATA ryear;
DATA topic;
unsigned int id;
}BOOK;

typedef struct LIBARY{
BOOK *Books;
int numberofbooks;
}LIBARY;

BOOK bookinit();
LIBARY libaryinit();
void copybook(BOOK *copy, BOOK original);
void bookvipe(BOOK *original);
void libaryvipe(LIBARY *original);
void expandlibary(LIBARY *original,BOOK newb);
void readdatabase(LIBARY *original,char *filename);
void writedatabase(LIBARY Output,char *filename);
void printdatabase(LIBARY Output);
unsigned short comparedata(DATA A,DATA B);
LIBARY shearch(LIBARY db,Mode selected,DATA phrase);
void libarydelete(LIBARY *original,int id);
void createdatabase(LIBARY *original);
DATA BookToData(BOOK A);
void libarycopy(LIBARY *copy,LIBARY original);
DATA readline();

#endif // LIBARY_H_INCLUDED
