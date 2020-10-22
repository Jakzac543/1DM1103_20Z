#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    float x;
    float a;
    x = 0;
    if (argc > 1)
    {
        for (int i=0; i<argc; i++)
        {
            a = atof(argv[i]);
            x = x + a;
        }
        printf("Suma: %f\n", x);
    }
    else printf ("Nie podano ani jednej liczby.\n");
    
    
    
}