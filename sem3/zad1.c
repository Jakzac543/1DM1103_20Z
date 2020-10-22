#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    float a;
    a = atof (argv[1]);
    printf("Wartosc %f do kwadratu to %f. \n", a, a*a);
    
    return 0;

}