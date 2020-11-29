#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct _Macierz {
    int r;
    int c;
    float **tab;
} Macierz;

Macierz * wczytaj(FILE * fin) 
{
    int i,j;
    Macierz *m;
    m = (Macierz*) malloc(sizeof(Macierz));
    fscanf(fin, "%d", &m->r);
    fscanf(fin, "%d", &m->c);

    m->tab = (float**) malloc (sizeof(float*) * m->r);
    for (i=0; i < m->r; i++) {
        m->tab[i] = (float*) malloc(sizeof(float) * m->c);
        for (j=0; j < m->c; j++) {
            fscanf(fin, "%f", &m->tab[i][j]);
        }
    }
    return m;
}

void zwolnij(Macierz *m)
{
   int i,j;
    for (i = 0; i < m->r; i++)
         free(m->tab[i]);
        for (j = 0; j < m->r; j++)
         free(&m->tab[i][j]);
    free(&m->r);
    free(&m->c);
    free(m);
}

void wypiszplik(char *nazwa,  Macierz *m) {
    FILE * fout;
    fout = fopen(nazwa, "w+");
    int i, j;
    fprintf(fout, "%d ", m->r);
    fprintf(fout, "\n");
    fprintf(fout, "%d ", m->c);
    fprintf(fout, "\n");
    for (i = 0; i < m->r; i++) 
    {   
        for (j=0; j < m->c; j++) 
        {
            fprintf(fout, "%4.1f ", m->tab[i][j]);
        }           
        fprintf(fout, "\n");
    }
}

void wypisz(Macierz *m) {
    int i, j;
    for (i = 0; i < m->r; i++) 
    {    
        printf("[");
        for (j=0; j < m->c; j++) 
        {
            printf("%4.1f ", m->tab[i][j]);
        }
                    
        printf("]");
        printf("\n");
    }
}


float norm(Macierz *m) {
    float s = 0;
    int i,j;

    for (i = 0; i < m->r; i++) {
        for (j=0; j < m->c; j++) {
            s += m->tab[i][j] * m->tab[i][j];
        }
    }
    return sqrt(s);
}

 Macierz * dodaj(Macierz *m,  Macierz *m2)
{
    int i,j;
     Macierz *suma;
     suma = (Macierz*) malloc(sizeof(Macierz));
    if (m->r != m2->r || m->c != m2->c) 
        {
        printf("Nie można przeprowadzić dodawania na podanych macierzach (zmień rozmiary macierzy!)\n");
        exit(0);
       }
  
        suma->tab = (float**) malloc(sizeof(float*) * m->r);
        for (i=0; i<m->r;i++)
        {
            suma->tab[i] = (float*) malloc(sizeof(float) * m->c);
            for(j=0;j<m->c;j++)
            {
                suma->tab[i][j] = m->tab[i][j] + m2->tab[i][j];
            }
        }
            suma->r = i;
            suma->c = j;
    return suma; 
}

 Macierz * odejmij(Macierz *m,  Macierz *m2)
{
    int i,j;
    Macierz *roznica;
    roznica = (Macierz*) malloc(sizeof(Macierz));
    if (m->r != m2->r || m->c != m2->c) 
        {
        printf("Nie można przeprowadzić odejmowania na podanych macierzach (zmień rozmiary macierzy!)\n");
        exit(0);
       }
    else
          roznica->tab = (float**) malloc(sizeof(float*) * m->r);
        for (i=0; i<m->r;i++)
        {
            roznica->tab[i] = (float*) malloc(sizeof(float) * m->c);
            for(j=0;j<m->c;j++)
            {
                roznica->tab[i][j] = m->tab[i][j] - m2->tab[i][j];
            }
        }
            roznica->r = i;
            roznica->c = j;
    return roznica; 
}

 Macierz * mnoz(Macierz *m,  Macierz *m2)
{
    if(m->c != m2->r)
    {    printf("Nie można przeprowadzić mnożenia dla podanych macierzy (zmień rozmiar macierzy!)\n");
        exit(0);
    }
     Macierz *iloczyn;
     iloczyn = (Macierz*) malloc(sizeof(Macierz));
    int i,j,k;
    iloczyn->tab = (float**) malloc(sizeof(float*) * m->r);
    for(i=0; i<m->r; i++)
    {
         iloczyn->tab[i] = (float*) malloc(sizeof(float) * m->c);
        for(j=0; j<m2->c; j++)
        {
            for(k=0; k<m2->c; k++)
            {
                iloczyn->tab[i][j] += m->tab[i][k]*m2->tab[k][j];
            }
        }
    }
    iloczyn->r=m->r;
    iloczyn->c=m2->c;
    return iloczyn;
}

 Macierz * mnozska( Macierz *m, float a)
{
    int i,j;
    Macierz *iloczyn;
    iloczyn = (Macierz*) malloc(sizeof(Macierz));
    iloczyn->tab = (float**) malloc(sizeof(float*) * m->r);
        for (i=0; i<m->r;i++)
        {
            iloczyn->tab[i] = (float*) malloc(sizeof(float) * m->c);
            for(j=0;j<m->c;j++)
            {
                iloczyn->tab[i][j] = m->tab[i][j] * a;
            }
        }
            iloczyn->r = i;
            iloczyn->c = j;
    
    return iloczyn; 
}


int main(int argc, char **argv)
{
    FILE * fin ;
    fin = fopen(argv[2], "r");
    Macierz *mac;
    mac = wczytaj(fin);
    
    if (strcmp (argv[1], "sum") == 0)
    {
        Macierz *mac2;
        FILE *fin2;
        fin2 = fopen(argv[3], "r");
        mac2 = wczytaj(fin2);
        if (argv[4] && strcmp (argv[4], "do_b.txt") == 0)
        {
            wypiszplik(argv[4], dodaj(mac,mac2));

            fclose(fin2);
            fclose(fin);
            zwolnij(dodaj(mac,mac2));               //nie wiem czemu przy zwalnianiu pamięci po wykonaniu programu pokazuje się segmentation fault :/
            zwolnij(mac);
            zwolnij(mac2);
            exit(0);
        }
        printf("Suma macierzy %s i %s: \n", argv[2], argv[3]);

        wypisz(dodaj(mac,mac2));
        fclose(fin2);
        fclose(fin);
        zwolnij(dodaj(mac,mac2));
        zwolnij(mac);
        zwolnij(mac2);
        exit(0);
    }
   
       if (strcmp (argv[1], "subtract") == 0)
    {
        Macierz *mac2;
        FILE * fin2;
        fin2 = fopen(argv[3], "r");
        mac2 = wczytaj(fin2);
          if (argv[4] && strcmp (argv[4], "do_b.txt") == 0)
        {
            wypiszplik(argv[4], odejmij(mac,mac2));
            fclose(fin2);
            fclose(fin);
            zwolnij(mac);
            zwolnij(mac2);
            exit(0);
        }
        printf("Różnica macierzy %s i %s: \n", argv[2], argv[3]);
        wypisz(odejmij(mac,mac2));
        fclose(fin2);
        fclose(fin);
        zwolnij(mac);
        zwolnij(mac2);
        exit(0);
    }

           if (strcmp (argv[1], "prod") == 0)
    {
        Macierz *mac2;
        FILE * fin2;
        fin2 = fopen(argv[3], "r");
        mac2 = wczytaj(fin2);
          if (argv[4] && strcmp (argv[4], "do_b.txt") == 0)
        {
            wypiszplik(argv[4], mnoz(mac,mac2));
            fclose(fin2);
            fclose(fin);
            zwolnij(mac);
            zwolnij(mac2);
            exit(0);
        }
        printf("Iloczyn macierzy %s i %s: \n", argv[2], argv[3]);
        wypisz(mnoz(mac,mac2));
        fclose(fin2);
        fclose(fin);
        zwolnij(mac);
        zwolnij(mac2);
        exit(0);
    }

     if (strcmp (argv[1], "multiply") == 0)
     {  
         if (argv[4] && strcmp (argv[4], "do_b.txt") == 0)
        {
            wypiszplik(argv[4], mnozska(mac, atof(argv[3])));
            fclose(fin);
            zwolnij(mac);
            exit(0);
        }
        printf("Iloczyn skalarny macierzy %s i liczby %f: \n", argv[2], atof(argv[3]));
         wypisz(mnozska(mac, atof(argv[3])));
        fclose(fin);
        zwolnij(mac);
         exit(0);
     }

    if (strcmp (argv[1], "norm") == 0)
     {
           if (argv[3] && strcmp (argv[3], "do_b.txt") == 0)
        {
            FILE * fout;
            fout = fopen(argv[3], "w+");
            fprintf(fout, "%f", norm(mac));
            fclose(fin);
            fclose(fout);
            zwolnij(mac);
            exit(0);
        }
       printf("Norma macierzy %s = %f\n", argv[2], norm(mac));
       fclose(fin);
       zwolnij(mac);
       exit(0);
     }
        
       else 
        printf("Podałeś niewłaściwą komendę!\n");
    

    fclose(fin);

    return 0;
}

