#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    float x;
    char a;
    x = 2;
    if (argc > 1)
    {
        for (int i=0; i<argc; i++)
        {
            a = *argv[i];
            x = x + a - '0';  // odejmuję wartość ASCII liczby 0, żeby przekształcić typ char na float
        }
        printf("Suma: %f\n", x);
    }
    else printf ("Nie podano ani jednej liczby.\n");
    
    
    
}