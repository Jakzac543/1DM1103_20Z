#include "studenci.h"
#include <stdio.h>
#include <string.h>

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