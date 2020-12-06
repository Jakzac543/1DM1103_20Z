all:
	cc baza.c main.c -o mydb -Wall --pedantic

test: all
	./mydb baza.csv list_students

test-przedmioty: all
	./mydb baza.csv list_courses

test-ile: all
	./mydb baza.csv count_students

test-memory: all
	./mydb baza.csv count_students

test-dodaj-stud: all
	valgrind ./mydb baza.csv add_student Kamil Ślimak 444333 cotam@sie.ma 

test-dodaj-przed: all
	valgrind  ./mydb baza.csv add_course 1DE2103 "Metody numeryczne" 2020Z

test-dodaj-stud-przed: all
	valgrind ./mydb baza.csv student_to_course 123456 1DE1203

#test-ocen: all
#	./mydb baza.csv set_grade 1DE1203 123456 3.5 "Bardzo ładny projekt." 