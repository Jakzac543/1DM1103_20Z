#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _student {
    char imie[25];
    char nazwisko[50];
    char nr_albumu[10];
    char kod_przed[10];
    char nazwa_przed[255];
    float ocena;
    int ects;
} student, *pstudent;

int wczytaj(student dane[100], char *fnazwa) {
    FILE * fin = fopen(fnazwa, "r");
    int cnt, i;
    char bufor[1024];
    char *w;

    fgets(bufor, 1023, fin);
    sscanf(bufor, "%d", &cnt);
 
    for (i=0; i<cnt; i++) {
        fgets(bufor, 1023, fin);
        w = strtok(bufor, "|");
        strncpy(dane[i].imie, w, 24);

        w = strtok(NULL, "|");
        strncpy(dane[i].nazwisko, w, 49);
        
        w = strtok(NULL, "|");
        strncpy(dane[i].nr_albumu, w, 9);

        w = strtok(NULL, "|");
        strncpy(dane[i].kod_przed, w, 9);

        w = strtok(NULL, "|");
        strncpy(dane[i].nazwa_przed, w, 254);

        w = strtok(NULL, "|");
        dane[i].ocena = atof(w);

        w = strtok(NULL, "|");
        dane[i].ects = atoi(w);
    }

    fclose(fin);
    return cnt;
}
// void wypisz(student dane[100], int n) {
//     int i;
//     for (i=0; i<n;i++) {
//         printf("{ Student: %s - %s %s, z przedmiotu: [%s] %s za ECTS: %d otrzymał %.1f\n",
//             dane[i].nr_albumu, dane[i].imie, dane[i].nazwisko,
//             dane[i].kod_przed, dane[i].nazwa_przed,
//             dane[i].ects, dane[i].ocena
//         );
//     }
// }



int znajdz(char *szukany_nr, char kody_przed[100][10], int n) {
    int i;
    for (i=0; i<n; i++) {
        if (strcmp(szukany_nr, kody_przed[i]) == 0)
            return i;
    }
    return -1;
}


int znajdz_przedmioty(char kody_przed[100][10], student dane[100], int n) {
    int ile_znalazlem = 0;
    int i;
    for (i=0; i <n; i++) {
        if (znajdz(dane[i].kod_przed, kody_przed, ile_znalazlem ) == -1) {
            strncpy(kody_przed[ile_znalazlem], dane[i].kod_przed, 9);
            ile_znalazlem++;
        }
    }
    
    return ile_znalazlem;
}

void najlepszy_przedmiot(student dane[100], int ile_rekordow)
{
    char kody_przed[100][10];
    char nazwa_przed[100][255];
    int ile_przed;
    float sumy_wazonych_ocen[100];
    int sumy_ects[100];
    int i;
    int pozycja;
    int najlepsza_pozycja;
    float najlepsza = 0;

    ile_przed = znajdz_przedmioty(kody_przed, dane, ile_rekordow);

    for(i=0; i<ile_rekordow; i++)
    {
        pozycja = znajdz(dane[i].kod_przed, kody_przed, ile_przed);
        strcpy(nazwa_przed[pozycja],dane[i].nazwa_przed);
        sumy_wazonych_ocen[pozycja] += dane[i].ocena * dane[i].ects;
        sumy_ects[pozycja] += dane[i].ects;
    }

    for (i=0; i < ile_przed; i++) {
        if (najlepsza < sumy_wazonych_ocen[i] / sumy_ects[i]) {
            najlepsza = sumy_wazonych_ocen[i] / sumy_ects[i];
            najlepsza_pozycja = i;
        }
    }

    printf("Najlepsza średnia: ");
    printf("%s - %s: %f \n",
         kody_przed[najlepsza_pozycja], nazwa_przed[najlepsza_pozycja],
        sumy_wazonych_ocen[najlepsza_pozycja] /sumy_ects[najlepsza_pozycja]);
}

void najgorszy_przedmiot(student dane[100], int ile_rekordow)
{
    char kody_przed[100][10];
    char nazwa_przed[100][255];
    int ile_przed;
    float sumy_wazonych_ocen[100];
    int sumy_ects[100];
    int i;
    int pozycja;
    int najlepsza_pozycja;
    float najlepsza = 6;

    ile_przed = znajdz_przedmioty(kody_przed, dane, ile_rekordow);

    for(i=0; i<ile_rekordow; i++)
    {
        pozycja = znajdz(dane[i].kod_przed, kody_przed, ile_przed);
        strcpy(nazwa_przed[pozycja],dane[i].nazwa_przed);
        sumy_wazonych_ocen[pozycja] += dane[i].ocena * dane[i].ects;
        sumy_ects[pozycja] += dane[i].ects;
    }

    for (i=0; i < ile_przed; i++) {
        if (najlepsza > sumy_wazonych_ocen[i] / sumy_ects[i]) {
            najlepsza = sumy_wazonych_ocen[i] / sumy_ects[i];
            najlepsza_pozycja = i;
        }
    }

    printf("Najgorsza średnia: ");
    printf("%s - %s: %f \n",
         kody_przed[najlepsza_pozycja], nazwa_przed[najlepsza_pozycja],
        sumy_wazonych_ocen[najlepsza_pozycja] /sumy_ects[najlepsza_pozycja]);
}

int main(int argc, char **argv)
{
    student dane[100];
    int ile;
    ile = wczytaj(dane, argv[1]);
   najlepszy_przedmiot(dane, ile);
   najgorszy_przedmiot(dane, ile);

    return 0;
}