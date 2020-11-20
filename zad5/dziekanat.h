#ifndef DZIEKANAT_H
#define DZIEKANAT_H

#include "studenci.h"

 int ile;

int znajdz_przedmioty(char kody_przed[100][10], student dane[100], int n);
void najlepszy_przedmiot(student dane[100], int ile_rekordow);
void najgorszy_przedmiot(student dane[100], int ile_rekordow);


#endif