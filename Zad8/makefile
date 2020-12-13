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
	./mydb baza.csv add_student Kamil Ślimak 213788 bajo@jajo.pl

test-dodaj-przed: all
	./mydb baza.csv add_course 1DE2102 "Metody numeryczne" 2020Z

test-dodaj-stud-przed: all
	./mydb baza.csv student_to_course 123456 1DE1203

test-sortuj-stud-malejaco: all
	./mydb baza.csv sort_students_descending

test-sortuj-stud-rosnaco: all
	./mydb baza.csv sort_studends_ascending

test-sortuj-przed-kod: all
	./mydb baza.csv sort_courses_code

test-sortuj-przed-nazwa: all
	./mydb baza.csv sort_courses_name

test-oceny-przed: all
	./mydb baza.csv list_courses_grades 1DA1245

test-oceny-stud: all
	./mydb baza.csv list_students_grades 12345

#test-ocen: all
#	./mydb baza.csv set_grade 1DE1203 123456 3.5 "Bardzo ładny projekt." 