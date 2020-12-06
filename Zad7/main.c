#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baza.h"

int main(int argc, char ** argv) {
    SBaza *baza;
    baza = wczytaj_baze(argv[1]);

    if (strcmp("list_students", argv[2]) == 0) 
    {
        listuj_studentow(baza);
    } 
    else if (strcmp("add_student", argv[2]) == 0) 
    {
         dodaj_studenta(baza, argv[3], argv[4], argv[5], argv[6]);
    } 
    else if (strcmp("count_students", argv[2]) == 0)
     {
        printf("Liczba studentów: %d\n", ile_studentow(baza));
    } 
    else if (strcmp("list_courses", argv[2]) == 0) 
    {
        listuj_przedmioty(baza);
    } 
    else if (strcmp("add_course", argv[2]) == 0) 
    {
        dodaj_przedmiot(baza, argv[3], argv[4], argv[5]);
    } 
    // else if (strcmp("set_grade", argv[2]) == 0) 
    // {
    //     wystaw_ocene(baza, argv[3], argv[4], atoi(argv[5]), argv[6]);
    // }
    else if (strcmp("student_to_course", argv[2]) == 0) 
    {
        dodaj_stud_do_przed(baza, argv[3], argv[4]);
    }
    zapisz_baze(argv[1], baza);

    zwolnij(baza);
    return 0;
}