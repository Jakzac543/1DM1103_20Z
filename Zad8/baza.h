#ifndef _BAZA_H
#define _BAZA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Student {
    char * imie;
    char * nazwisko;
    char * nr_albumu;
    char * email;

    struct _Student *poprz;    
    struct _Student *nast;
} Student;

 typedef struct _Przedmiot {
    char * numer;
    char * nazwa;
    char * semestr;

    struct _Przedmiot *poprz;
    struct _Przedmiot *nast;
 } Przedmiot;

 typedef struct _Ocena {
    char * nr_albumu;
    char * kod_przedmiotu;
    float ocena;
    char * komentarz;

    struct _Ocena *poprz;
    struct _Ocena *nast;
 } Ocena;

typedef struct _SBaza {
    Student *lista_studentow; /* Głowa listy! */
    Przedmiot *lista_przedmiotow;
    Ocena *lista_ocen;
} SBaza;

SBaza * wczytaj_baze(char *nazwa_pliku);
SBaza * zapisz_baze(char *nazwa_pliku, SBaza * baza);
void zwolnij(SBaza *baza);

SBaza * dodaj_studenta(SBaza *baza, char *im, char *na, char *nr, char *em);
void listuj_studentow(SBaza *baza);
int ile_studentow(SBaza *baza);
Student * sortuj_przez_wybieranie_za(Student *glowa);
Student * sortuj_przez_wybieranie_az(Student *glowa);
Ocena * filtruj_studentow(Ocena *ocen, char *nr);



Przedmiot * wczytaj_przedmioty(FILE * fin);
SBaza * dodaj_przedmiot(SBaza *baza, char *nr, char *na, char *se);
void listuj_przedmioty(SBaza *baza);
int ile_przedmiotow(SBaza *baza);
Przedmiot * sortuj_przez_wybieranie_kod(Przedmiot *glowa);
Przedmiot * sortuj_przez_wybieranie_nazwa(Przedmiot *glowa);
Ocena * filtruj_przedmioty(Ocena *ocen, char *kod);

//SBaza * wystaw_ocene(SBaza *baza, char *kod,char *nr, float oc, char *kom);
int ile_ocen(SBaza *baza);
Ocena * wczytaj_oceny(FILE * fin);
void listuj_oceny(SBaza *baza);
SBaza * dodaj_stud_do_przed(SBaza * baza, char *kod, char *nr);


#endif