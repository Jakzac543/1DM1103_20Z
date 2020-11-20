#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dziekanat.h"
#include "studenci.h"

int main(int argc, char ** argv) {
    
    ile = wczytaj(dane, argv[1]);
   
   if (!argv[2]) 
   {
    printf("Nie podałeś oczekiwanego polecenia.\nMożliwe polecenia to: \"test_najlepszy_student\", \"test_najlepszy_przedmiot\", \"test_najgorszy_przedmiot\" i \"wypisz\".\n");
        exit(0); 
   }

   if (strcmp(argv[2],"wypisz")==0) 
   {
       wypisz(dane, ile);
       exit(0);
   }
   
   if (strcmp(argv[2],"najlepszy_przedmiot")==0) 
   {
        najlepszy_przedmiot(dane, ile);
        exit(0);
   }
   if (strcmp(argv[2],"najgorszy_przedmiot")==0)
   { 
        najgorszy_przedmiot(dane, ile);
        exit(0);
   }
   
   if (strcmp(argv[2],"najlepszy_student")==0) 
   {
       najlepszy_student(dane, ile);
       exit(0);
   }
    else 
    printf("Nie podałeś oczekiwanego polecenia.\nMożliwe polecenia to: \"test_najlepszy_student\", \"test_najlepszy_przedmiot\", \"test_najgorszy_przedmiot\" i \"test_wypisz\".\n");
    
    return 0;
}