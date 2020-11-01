#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wczytaj (FILE *fin, float (*tablica)[100], int wiersze, int kolumny)
{
 float liczba;
    for(int i=0; i<wiersze; i++)
     {
         for (int j=0; j<kolumny; j++)
         {
             fscanf(fin, "%f", &liczba);
             tablica[i][j] = liczba;
         }
     }
}

void wypisz (FILE *fin, float (*tablica)[100], int wiersze, int kolumny)
{
    
     for(int i=0; i<wiersze; i++)
        {
            printf("[");
            for (int j=0; j<kolumny; j++)
            {
                printf("%f ", tablica[i][j]);
            }
             printf("]");
            printf("\n");
        }
        printf("\n");
        
}

void mnozenie (float (*wynik)[100], float (*tablica1)[100], float (*tablica2)[100], int wiersze, int wiersze2, int kolumny, int kolumny2)
{
    int i, j, m, n;
     for(i=0; i<wiersze; i++)
            {
                for (j=0; j<kolumny; j++)
                {
                    
                    for (m=0; m<wiersze2; m++)
                    {
                        for (n=0; n<kolumny2; n++)
                            { 
                                wynik[i][j] = wynik[i][j] + tablica1[i][m]*tablica2[m][n];
                            } 
                    }
                }
                
            }
}

void wypisz_wynik(float (*tablica)[100], int wiersze)
{
    printf("(%d) ", wiersze);
        printf("[");
      for(int i=0; i<wiersze; i++)
        { 
         printf("%f ", tablica[i][0]);
        }
         printf("] \n");
}


int main(int argc, char *argv[])
{
    FILE *fin;
    float wynik[100][100];
    float macierz[100][100];
    float wektor[100][100];
    int wiersze, kolumny, wiersze2, kolumny2;
    
    fin = fopen( argv[1], "r");
    fscanf(fin, "%d", &wiersze);                    //MACIERZ
    fscanf(fin, "%d", &kolumny);
    wczytaj(fin, macierz, wiersze, kolumny);
    printf("Podana macierz A o wymiarach %dx%d: \n", wiersze, kolumny);
    wypisz(fin, macierz, wiersze, kolumny);
    
    fin = fopen( argv[2], "r");
    fscanf(fin, "%d", &wiersze2);                   //WEKTOR
    fscanf(fin, "%d", &kolumny2);
    wczytaj(fin, wektor, wiersze2, kolumny2);
    printf("Podany wektor X o wymiarach %dx%d: \n", wiersze2, kolumny2);
    wypisz(fin, wektor, wiersze2, kolumny2);
        if(kolumny != wiersze2) 
        {
        printf("Nie można przeprowadzić mnożenia macierzy A przez wektor X! \n");
        exit(0);
        }
   
   printf("Wynik mnożenia: \n");
    mnozenie(wynik, macierz, wektor, wiersze, wiersze2, kolumny, kolumny2);
    wypisz_wynik(wynik, wiersze); 
    
    return 0;
}