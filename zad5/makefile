DEPS=main.o studenci.o dziekanat.o

main: $(DEPS)
	cc $(DEPS) -o $@ -Wall --pedantic

%.o:%.c
	cc -c $^ -o $@

clean:
	rm -f main
	rm -f *.o

test: main
	./main Studenci.txt
test_najlepszy_przedmiot: main 
	./main Studenci.txt najlepszy_przedmiot
test_najlepszy_student: main
	./main Studenci.txt najlepszy_student
test_wypisz: main
	./main Studenci.txt wypisz
test_najgorszy_przedmiot: main
	./main Studenci.txt najgorszy_przedmiot