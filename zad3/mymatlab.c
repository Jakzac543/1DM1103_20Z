#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct Macierz {
    int r;
    int c;
    float tab[200][200];
};

void wczytaj(FILE * fin, struct Macierz *m) 
{
    int i,j;
    fscanf(fin, "%d", &m->r);
    fscanf(fin, "%d", &m->c);

    for (i=0; i < m->r; i++) {
        for (j=0; j < m->c; j++) {
            fscanf(fin, "%f", &m->tab[i][j]);
        }
    }
}

void wypiszplik(FILE *fin, struct Macierz m) {
    int i, j;
    fprintf(fin, "%d ", m.r);
    fprintf(fin, "\n");
    fprintf(fin, "%d ", m.c);
    fprintf(fin, "\n");
    for (i = 0; i < m.r; i++) 
    {   
        for (j=0; j < m.c; j++) 
        {
            fprintf(fin, "%4.1f ", m.tab[i][j]);
        }           
        fprintf(fin, "\n");
    }
}

void wypisz(struct Macierz m) {
    int i, j;
    
    for (i = 0; i < m.r; i++) 
    {    
        printf("[");
        for (j=0; j < m.c; j++) 
        {
            printf("%4.1f ", m.tab[i][j]);
        }
                    
        printf("]");
        printf("\n");
    }
}


float norm(struct Macierz m) {
    float s = 0;
    int i,j;

    for (i = 0; i < m.r; i++) {
        for (j=0; j < m.c; j++) {
            s += m.tab[i][j] * m.tab[i][j];
        }
    }
    return sqrt(s);
}

struct Macierz dodaj(struct Macierz m, struct Macierz m2)
{
    int i,j;
    struct Macierz suma;
    if (m.r != m2.r || m.c != m2.c) 
        {
        printf("Nie można przeprowadzić dodawania na podanych macierzach (zmień rozmiary macierzy!)\n");
        exit(0);
       }
    else
        for (i=0; i<m.r;i++)
            for(j=0;j<m.c;j++)
            {
                suma.tab[i][j] = m.tab[i][j] + m2.tab[i][j];
            }
            suma.r = i;
            suma.c = j;
    return suma; 
}

struct Macierz odejmij(struct Macierz m, struct Macierz m2)
{
    int i,j;
    struct Macierz roznica;
    if (m.r != m2.r || m.c != m2.c) 
        {
        printf("Nie można przeprowadzić odejmowania na podanych macierzach (zmień rozmiary macierzy!)\n");
        exit(0);
       }
    else
        for (i=0; i<m.r;i++)
            for(j=0;j<m.c;j++)
            {
                roznica.tab[i][j] = m.tab[i][j] - m2.tab[i][j];
            }
            roznica.r = i;
            roznica.c = j;
    return roznica; 
}

struct Macierz mnoz(struct Macierz m, struct Macierz m2)
{
    if(m.c != m2.r)
    {    printf("Nie można przeprowadzić mnożenia dla podanych macierzy (zmień rozmiar macierzy!)\n");
        exit(0);
    }
    struct Macierz iloczyn;
    int i,j,k;
    for(i=0; i<m.r; i++)
    {
        for(j=0; j<m2.c; j++)
        {
            for(k=0; k<m2.c; k++)
            {
                iloczyn.tab[i][j] += m.tab[i][k]*m2.tab[k][j];
            }
        }
    }
    iloczyn.r=m.r;
    iloczyn.c=m2.c;
    return iloczyn;
}

struct Macierz mnozska(struct Macierz m, float a)
{
    int i,j;
    struct Macierz iloczyn;

        for (i=0; i<m.r;i++)
            for(j=0;j<m.c;j++)
            {
                iloczyn.tab[i][j] = m.tab[i][j] * a;
            }
            iloczyn.r = i;
            iloczyn.c = j;
    return iloczyn; 



return iloczyn;
}


int main(int argc, char *argv[])
{
    struct Macierz mac;
    
    FILE * fin ;
    fin = fopen(argv[2], "r");
    wczytaj(fin, &mac);
    

    if (strcmp (argv[1], "sum") == 0)
    {
        struct Macierz mac2;
        FILE * fin2;
        fin2 = fopen(argv[3], "r");
        wczytaj(fin2, &mac2);
        if (argv[4] && strcmp (argv[4], "do_b.txt") == 0)
        {
            FILE * fout;
            fout = fopen(argv[4], "w+");
            wypiszplik(fout, dodaj(mac,mac2));
            exit(0);
        }
        printf("Suma macierzy %s i %s: \n", argv[2], argv[3]);
        wypisz(dodaj(mac,mac2));
        fclose(fin2);
        exit(0);
    }
   
       if (strcmp (argv[1], "subtract") == 0)
    {
        struct Macierz mac2;
        FILE * fin2;
        fin2 = fopen(argv[3], "r");
        wczytaj(fin2, &mac2);
          if (argv[4] && strcmp (argv[4], "do_b.txt") == 0)
        {
            FILE * fout;
            fout = fopen(argv[4], "w+");
            wypiszplik(fout, odejmij(mac,mac2));
            exit(0);
        }
        printf("Różnica macierzy %s i %s: \n", argv[2], argv[3]);
        wypisz(odejmij(mac,mac2));
        fclose(fin2);
        exit(0);
    }

           if (strcmp (argv[1], "prod") == 0)
    {
        struct Macierz mac2;
        FILE * fin2;
        fin2 = fopen(argv[3], "r");
        wczytaj(fin2, &mac2);
          if (argv[4] && strcmp (argv[4], "do_b.txt") == 0)
        {
            FILE * fout;
            fout = fopen(argv[4], "w+");
            wypiszplik(fout, mnoz(mac,mac2));
            exit(0);
        }
        printf("Iloczyn macierzy %s i %s: \n", argv[2], argv[3]);
        wypisz(mnoz(mac,mac2));
        fclose(fin2);
        exit(0);
    }

     if (strcmp (argv[1], "multiply") == 0)
     {  
         if (argv[4] && strcmp (argv[4], "do_b.txt") == 0)
        {
            FILE * fout;
            fout = fopen(argv[4], "w+");
            wypiszplik(fout, mnozska(mac, atof(argv[3])));
            exit(0);
        }
        printf("Iloczyn skalarny macierzy %s i liczby %f: \n", argv[2], atof(argv[3]));
         wypisz(mnozska(mac, atof(argv[3])));
         exit(0);
     }

    if (strcmp (argv[1], "norm") == 0)
     {
           if (argv[3] && strcmp (argv[3], "do_b.txt") == 0)
        {
            FILE * fout;
            fout = fopen(argv[3], "w+");
            fprintf(fout, "%f", norm(mac));
            exit(0);
        }
       printf("Norma macierzy %s = %f\n", argv[2], norm(mac));
       exit(0);
     }
        
       else 
        printf("Podałeś niewłaściwą komendę!\n");
    
    

fclose(fin);
    return 0;
}

