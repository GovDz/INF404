
calculette: analyse_syntaxique.o analyse_lexicale.o lecture_caracteres.o  calculette.o
	gcc -g -Wall -o calculette analyse_lexicale.o analyse_syntaxique.o  lecture_caracteres.o  calculette.o


analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c analyse_lexicale.c

lecture_caracteres.o: lecture_caracteres.h lecture_caracteres.c
	gcc -g -Wall -c lecture_caracteres.c

calculette.o : analyse_syntaxique.h
	gcc -g -Wall -c calculette.c

clean:
	rm -f  calculette *.o


