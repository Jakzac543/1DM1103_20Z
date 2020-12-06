#include "baza.h"

Student * wczytaj_studentow(FILE *fin) {
    char bufor[255];
    int n, i;
    char *s;
    Student *last_student = NULL;
    Student *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Student *stud = (Student*) malloc(sizeof(Student));
        stud->nast = NULL;

        if (last_student == NULL)
            glowa = stud;
        else
            last_student->nast = stud;
        last_student = stud;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        stud->imie = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->imie, s);

        s = strtok(NULL, ";");
        stud->nazwisko = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nazwisko, s);

        s = strtok(NULL, ";");
        stud->nr_albumu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nr_albumu, s);

        s = strtok(NULL, "\n");
        stud->email = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->email, s);
    }

    return glowa;
}

Przedmiot * wczytaj_przedmioty(FILE * fin)
{
    char bufor[255];
    int n, i;
    char *s;
    Przedmiot *last_course = NULL;
    Przedmiot *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Przedmiot *przed = (Przedmiot*) malloc(sizeof(Przedmiot));
        przed->nast = NULL;

        if (last_course == NULL)
            glowa = przed;
        else
            last_course->nast = przed;
        last_course = przed;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        przed->numer = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(przed->numer, s);

        s = strtok(NULL, ";");
        przed->nazwa = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(przed->nazwa, s);

        s = strtok(NULL, "\n");
        przed->semestr = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(przed->semestr, s);
    }

    return glowa;
}

Ocena * wczytaj_oceny(FILE * fin)
{
    char bufor[255];
    int n, i;
    char *s;
    Ocena *last_grade = NULL;
    Ocena *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Ocena *ocen = (Ocena*) malloc(sizeof(Ocena));
        ocen->nast = NULL;

        if (last_grade == NULL)
            glowa = ocen;
        else
            last_grade->nast = ocen;
        last_grade = ocen;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        ocen->nr_albumu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(ocen->nr_albumu, s);

        s = strtok(NULL, ";");
        ocen->kod_przedmiotu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(ocen->kod_przedmiotu, s);

        s = strtok(NULL, ";");
        ocen->ocena = atoi(s);
    
        s = strtok(NULL, "\n");
        ocen->komentarz = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(ocen->komentarz, s);    
    }

    return glowa;
}
SBaza * wczytaj_baze(char *nazwa_pliku) {
    FILE *fin = fopen(nazwa_pliku, "r");
    if (fin == NULL) {
        printf("BŁĄD! Nie moge otworzyc pliku: %s.\n", nazwa_pliku);
        exit(-1);
    }

    SBaza *baza = (SBaza*) malloc( sizeof(SBaza));
    baza->lista_studentow = wczytaj_studentow(fin);
    baza->lista_przedmiotow = wczytaj_przedmioty(fin);
    baza ->lista_ocen = wczytaj_oceny(fin);
    fclose(fin);
    return baza;
}

SBaza * zapisz_baze(char *nazwa_pliku, SBaza * baza) 
{
    FILE *fout = fopen(nazwa_pliku, "w+");
    Student * stud = baza->lista_studentow;
    Przedmiot * przed = baza->lista_przedmiotow;
    Ocena * ocen = baza->lista_ocen;

    fprintf(fout, "%d\n", ile_studentow(baza));
    for(int i=0; i<ile_studentow(baza); i++)
    {
        fprintf(fout, "%s;%s;%s;%s\n", stud->imie, stud->nazwisko, stud->nr_albumu, stud->email);
        stud = stud->nast;
    }   

    fprintf(fout, "%d\n", ile_przedmiotow(baza));
    for(int i=0; i<ile_przedmiotow(baza); i++)
    {
        fprintf(fout, "%s;%s;%s\n", przed->numer, przed->nazwa, przed->semestr);
        przed = przed->nast;
    }  

        fprintf(fout, "%d\n", ile_ocen(baza));
    for(int i=0; i<ile_ocen(baza); i++)    
    {
        fprintf(fout, "%s;%s;%.1f;%s\n", ocen->nr_albumu, ocen->kod_przedmiotu, ocen->ocena, ocen->komentarz);
        ocen = ocen->nast;
    }
    fclose(fout);

    return baza;
}

int ile_studentow(SBaza *baza) {
    int n = 0;
    Student * stud = baza->lista_studentow;
    while (stud != NULL) {
        n++;
        stud = stud->nast;
    }
    return n;
}

int ile_przedmiotow(SBaza *baza) {
    int n = 0;
    Przedmiot * przed = baza->lista_przedmiotow;
    while (przed != NULL) {
        n++;
        przed = przed->nast;
    }
    return n;
}

int ile_ocen(SBaza *baza) {
    int n = 0;
    Ocena * ocen = baza->lista_ocen;
    while (ocen != NULL) {
        n++;
        ocen = ocen->nast;
    }
    return n;
}

void listuj_studentow(SBaza *baza) {
    Student * stud = baza->lista_studentow;
    while (stud != NULL) {
        printf("%s %s %s %s\n", stud->imie, stud->nazwisko, stud->nr_albumu, stud->email);
        stud = stud->nast;
    }
}

void listuj_przedmioty(SBaza *baza){
        Przedmiot * przed = baza->lista_przedmiotow;
        while (przed != NULL) {
            printf("%s %s %s\n", przed->numer, przed->nazwa, przed->semestr);
            przed = przed->nast;
    }
 }

 SBaza * dodaj_studenta(SBaza *baza, char *im, char *na, char *nr, char *em){
    Student *stud = (Student*) malloc(sizeof(Student));
  	Student *nowy;
  	stud->nast = NULL;
  	stud->imie = (char*) malloc(sizeof(char) * (strlen(im) + 1));
    strcpy(stud->imie, im);
    stud->nazwisko = (char*) malloc(sizeof(char) * (strlen(na) + 1));
    strcpy(stud->nazwisko, na);
    stud->nr_albumu = (char*) malloc(sizeof(char) * (strlen(nr) + 1));
    strcpy(stud->nr_albumu, nr);
    stud->email = (char*) malloc(sizeof(char) * (strlen(em) + 1));
    strcpy(stud->email, em);
    nowy=baza->lista_studentow;
 
    if(ile_studentow(baza) == 0)
    {
      baza->lista_studentow = stud;
    }
    else
    {
      for(int i=1; i<ile_studentow(baza); i++)
      {
        nowy = nowy->nast;
      }
      nowy->nast = stud;
    }   
    return baza;
}

SBaza * dodaj_przedmiot(SBaza *baza, char *nr, char *na, char *se){
    Przedmiot *przed = (Przedmiot*) malloc(sizeof(Przedmiot));
    Przedmiot *nowy;
  	przed->nast = NULL;
  	przed->numer = (char*) malloc(sizeof(char) * (strlen(nr) + 1));
    strcpy(przed->numer, nr);
    przed->nazwa = (char*) malloc(sizeof(char) * (strlen(na) + 1));
    strcpy(przed->nazwa, na);
    przed->semestr = (char*) malloc(sizeof(char) * (strlen(se) + 1));
    strcpy(przed->semestr, se);
    nowy = baza->lista_przedmiotow;
 
    if(ile_przedmiotow(baza) == 0)
    {
      baza->lista_przedmiotow = przed;
    }
    else
    {
      for(int i=1; i<ile_przedmiotow(baza); i++)
      {
        nowy = nowy->nast;
      }
      nowy->nast = przed;
    }   
    return baza;
}

//  SBaza * wystaw_ocene(SBaza *baza, char *kod,char *nr, float oc, char *kom){
//     Ocena *ocen = (Ocena*) malloc(sizeof(Ocena));
//     Ocena *nowy;
//   	ocen->nast = NULL;
//   	ocen->kod_przedmiotu = (char*) malloc(sizeof(char) * (strlen(kod) + 1));
//     strcpy(ocen->kod_przedmiotu, nr);
//     ocen->nr_albumu = (char*) malloc(sizeof(char) * (strlen(nr) + 1));
//     strcpy(ocen->nr_albumu, nr);
//     ocen->ocena = oc;
//     ocen->komentarz = (char*) malloc(sizeof(char) * (strlen(kom) + 1));
//     strcpy(ocen->komentarz, nr);
//     nowy = baza->lista_ocen;
 
//     if(ile_ocen(baza) == 0)
//     {
//       baza->lista_ocen = ocen;
//     }
//     else
//     {
//       for(int i=1; i<ile_ocen(baza); i++)
//       {
//         nowy = nowy->nast;
//       }
//       nowy->nast = ocen;
//     }   
//     return baza;
//  }

SBaza * dodaj_stud_do_przed(SBaza * baza, char *kod, char *nr)
{
	Ocena *ocen = (Ocena*) malloc(sizeof(Ocena));
  	Ocena *nowa;
  	ocen->nast = NULL;

  	ocen->kod_przedmiotu = (char*) malloc(sizeof(char) * (strlen(kod) + 1));
    strcpy(ocen->kod_przedmiotu, kod);
    ocen->nr_albumu = (char*) malloc(sizeof(char) * (strlen(nr) + 1));
    strcpy(ocen->nr_albumu, nr);
    ocen->ocena = 0;
    ocen->komentarz = (char*) malloc(sizeof(char));
    strcpy(ocen->komentarz, " ");
    nowa = baza->lista_ocen;
    
    if(ile_ocen(baza) == 0)
    {
      baza->lista_ocen = ocen;
    }
    else
    {
      for(int i=1; i<ile_ocen(baza); i++)
      {
        nowa = nowa->nast;
      }
      nowa->nast = ocen;
    }
    return NULL;
}

void zwolnij_student(Student *s) {
    free(s->imie);
    free(s->nazwisko);
    free(s->nr_albumu);
    free(s->email);
    free(s);
}

void zwolnij_przedmiot(Przedmiot *p)
{
    free(p->numer);
    free(p->nazwa);
    free(p->semestr);
    free(p);
}

void zwolnij_ocene(Ocena *o)
{
    free(o->kod_przedmiotu);
    free(o->nr_albumu);
    free(o->komentarz);
    free(o);
}

void zwolnij_liste_studentow(Student *s) {
    Student *n;
    while (s != NULL) {
        n = s->nast;
        zwolnij_student(s);
        s = n;
    }
}

void zwolnij_liste_przedmiotow(Przedmiot *p)
{
    Przedmiot *n;
    while (p != NULL) {
        n = p->nast;
        zwolnij_przedmiot(p);
        p = n;
    }
}

void zwolnij_liste_ocen(Ocena *o)
{
    Ocena *n;
    while (o != NULL) {
        n = o->nast;
        zwolnij_ocene(o);
        o = n;
    }
}

void zwolnij(SBaza *baza) {
    zwolnij_liste_studentow(baza->lista_studentow);
    zwolnij_liste_przedmiotow(baza->lista_przedmiotow);
    zwolnij_liste_ocen(baza->lista_ocen);
    free(baza);
}
