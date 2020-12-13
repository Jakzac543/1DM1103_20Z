#include "baza.h"

Student * ostatni_student(Student *glowa) {
    Student *el = glowa;
    if (el != NULL) {
        while (el->nast != NULL)
            el = el->nast;

        return el;
    } else
        return NULL;
}

Ocena * ostatnia_ocena(Ocena *glowa) {
    Ocena *el = glowa;
    if (el != NULL) {
        while (el->nast != NULL)
            el = el->nast;

        return el;
    } else
        return NULL;
}

Przedmiot * ostatni_przedmiot(Przedmiot *glowa) {
    Przedmiot *el = glowa;
    if (el != NULL) {
        while (el->nast != NULL)
            el = el->nast;

        return el;
    } else
        return NULL;
}

Student * wczytaj_studentow(FILE *fin) {
    char bufor[255];
    int n, i;
    char *s;
    Student *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);
    Student *c;

    for (i=0; i<n; i++) {
        Student *stud = (Student*) malloc(sizeof(Student));
        stud->nast = NULL;
        stud->poprz = NULL;

        if (glowa == NULL)
            glowa = stud;
        else {
            c = ostatni_student(glowa);
            c->nast = stud;
            stud->poprz = c;
        }

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
    Przedmiot *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);
    Przedmiot *c;

    for (i=0; i<n; i++) {
        Przedmiot *przed = (Przedmiot*) malloc(sizeof(Przedmiot));
        przed->nast = NULL;
        przed->poprz = NULL;

        if (glowa == NULL)
            glowa = przed;
        else {
            c = ostatni_przedmiot(glowa);
            c->nast = przed;
            przed->poprz = c;
        }

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
    Ocena *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);
    Ocena *c;

    for (i=0; i<n; i++) {
        Ocena *ocen = (Ocena*) malloc(sizeof(Ocena));
        ocen->nast = NULL;
        ocen->poprz = NULL;

        if (glowa == NULL)
            glowa = ocen;
        else {
            c = ostatnia_ocena(glowa);
            c->nast = ocen;
            ocen->poprz = c;
        }

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        ocen->kod_przedmiotu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(ocen->kod_przedmiotu, s);

        s = strtok(NULL, ";");
        ocen->nr_albumu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(ocen->nr_albumu, s);

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
        fprintf(fout, "%s;%s;%.1f;%s\n", ocen->kod_przedmiotu, ocen->nr_albumu, ocen->ocena, ocen->komentarz);
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

 void listuj_oceny(SBaza *baza){
        Ocena * ocen = baza->lista_ocen;
        while (ocen != NULL) {
            printf("%s %s %.1f %s\n",ocen->kod_przedmiotu, ocen->nr_albumu,ocen->ocena, ocen->komentarz);
            ocen = ocen->nast;
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

Student * usun_stud(Student *glowa, Student *el) {
    Student *c = glowa;
    if (glowa == el) {
        glowa = glowa->nast;
    } else {
        while (c != NULL) {
            if (c == el) {
                c->poprz->nast = c->nast;
                if (c->nast != NULL)
                    c->nast->poprz = c->poprz;

                break;
            }

            c = c->nast;
        }
    }
    c->nast = NULL;
    c->poprz = NULL;
    return glowa;
}

Student * najwiekszy(Student *el) {
    Student * max = NULL;
    while (el != NULL) {
        if (max == NULL) {
            max = el;
        } else {
            if ( strcmp(el->nazwisko, max->nazwisko) > 0 ) 
                max = el;
        }
        el = el->nast;
    }
    return max;
}

Student * najmniejszy_stud(Student *el) {
    Student * min = NULL;
    while (el != NULL) {
        if (min == NULL) {
            min = el;
        } else {
            if ( strcmp(el->nazwisko, min->nazwisko) < 0 ) 
                min = el;
        }
        el = el->nast;
    }
    return min;
}

Student * sortuj_przez_wybieranie_za(Student *glowa) {
    Student * nglowa = NULL;
    Student * m;
    Student * o; 

    while (glowa != NULL) {
        m = najwiekszy(glowa);
        glowa = usun_stud(glowa, m);
        
        o = ostatni_student(nglowa);
        if (o == NULL) {
            nglowa = m;
        } else {
            o->nast = m;
            m->poprz = o;
        }
    }

    return nglowa;
}

Student * sortuj_przez_wybieranie_az(Student *glowa) {
    Student * nglowa = NULL;
    Student * m;
    Student * o; 

    while (glowa != NULL) {
        m = najmniejszy_stud(glowa);
        glowa = usun_stud(glowa, m);
        
        o = ostatni_student(nglowa);
        if (o == NULL) {
            nglowa = m;
        } else {
            o->nast = m;
            m->poprz = o;
        }
    }
    return nglowa;
}

Przedmiot * usun_przed(Przedmiot *glowa, Przedmiot *el) {
    Przedmiot *c = glowa;
    if (glowa == el) {
        glowa = glowa->nast;
    } else {
        while (c != NULL) {
            if (c == el) {
                c->poprz->nast = c->nast;
                if (c->nast != NULL)
                    c->nast->poprz = c->poprz;

                break;
            }

            c = c->nast;
        }
    }
    c->nast = NULL;
    c->poprz = NULL;
    return glowa;
}

Przedmiot * najmniejszy_przed(Przedmiot *el) {
    Przedmiot * min = NULL;
    while (el != NULL) {
        if (min == NULL) {
            min = el;
        } else {
            if ( strcmp(el->numer, min->numer) < 0 ) 
                min = el;
        }
        el = el->nast;
    }
    return min;
}

Przedmiot * najmniejszy_przed_nazwa(Przedmiot *el) {
    Przedmiot * min = NULL;
    while (el != NULL) {
        if (min == NULL) {
            min = el;
        } else {
            if ( strcmp(el->nazwa, min->nazwa) < 0 ) 
                min = el;
        }
        el = el->nast;
    }
    return min;
}
Przedmiot * sortuj_przez_wybieranie_kod(Przedmiot *glowa) {
    Przedmiot * nglowa = NULL;
    Przedmiot * m;
    Przedmiot * o; 

    while (glowa != NULL) {
        m = najmniejszy_przed(glowa);
        glowa = usun_przed(glowa, m);
        
        o = ostatni_przedmiot(nglowa);
        if (o == NULL) {
            nglowa = m;
        } else {
            o->nast = m;
            m->poprz = o;
        }
    }
    return nglowa;
}

Przedmiot * sortuj_przez_wybieranie_nazwa(Przedmiot *glowa) {
    Przedmiot * nglowa = NULL;
    Przedmiot * m;
    Przedmiot * o; 

    while (glowa != NULL) {
        m = najmniejszy_przed_nazwa(glowa);
        glowa = usun_przed(glowa, m);
        
        o = ostatni_przedmiot(nglowa);
        if (o == NULL) {
            nglowa = m;
        } else {
            o->nast = m;
            m->poprz = o;
        }
    }
    return nglowa;
}

Ocena * filtruj_przedmioty(Ocena *ocen, char *kod) {

    Ocena * nglowa = NULL;
    int n=0;
    int m=0;

    printf("Oceny przedmiotu o kodzie %s:", kod);
    while (ocen != NULL) {
        if (nglowa == NULL) 
        {
            nglowa = ocen;
            if (strcmp(ocen->kod_przedmiotu, kod) == 0) 
            {
                 if(ocen->ocena !=0)
                {
                    printf(" %.1f", ocen->ocena);
                    m++;
                }
                n++;
            } 
        }
        else 
            if (strcmp(ocen->kod_przedmiotu, kod) == 0) 
            {
                if(ocen->ocena !=0)
                {
                    printf(" %.1f", ocen->ocena);
                    m++;
                }
                n++;
            }  
        ocen = ocen->nast;
    }
    if (n==0 || m==0) printf(" BRAK");
    printf("\n");
        if (n==0) printf("Nie znaleziono przedmiotu o takim kodzie.\n");
    return nglowa;
}

Ocena * filtruj_studentow(Ocena *ocen, char *nr) {

    Ocena * nglowa = NULL;
    int n=0;
    int m=0;

    printf("Oceny studenta o numerze albumu %s:", nr);
    while (ocen != NULL) {
        if (nglowa == NULL) 
        {
            nglowa = ocen;
            if (strcmp(ocen->nr_albumu, nr) == 0) 
            {
                 if(ocen->ocena !=0)
                {
                    printf(" %.1f", ocen->ocena);
                    m++;
                }
                n++;
            } 
        }
        else 
            if (strcmp(ocen->nr_albumu, nr) == 0) 
            {
                if(ocen->ocena !=0)
                {
                    printf(" %.1f", ocen->ocena);
                    m++;
                }
                n++;
            }  
        ocen = ocen->nast;
    }
    if (n==0 || m==0) printf(" BRAK");
    printf("\n");
        if (n==0) printf("Nie znaleziono studenta o takim numerze albumu.\n");
    return nglowa;
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
