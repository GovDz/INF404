
calculette: calculette.o analyse_lexicale.o lecture_caracteres.o analyse_syntaxique.o ast_construction.o ast_parcours.o
	gcc -g -Wall -o calculette calculette.o analyse_lexicale.o lecture_caracteres.o analyse_syntaxique.o ast_construction.o ast_parcours.o

analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c analyse_lexicale.c

lecture_caracteres.o: lecture_caracteres.h lecture_caracteres.c
	gcc -g -Wall -c lecture_caracteres.c

test_lexeme.o: analyse_lexicale.h
	gcc -g -Wall -c test_lexeme.c

analyse_syntaxique.o: analyse_syntaxique.c analyse_syntaxique.h analyse_lexicale.h type_ast.h ast_construction.h ast_parcours.h
	gcc -g -Wall -c analyse_syntaxique.c

ast_construction.o: ast_construction.c type_ast.h
	gcc -g -Wall -c ast_construction.c

ast_parcours.o: ast_parcours.c type_ast.h
	gcc -g -Wall -c ast_parcours.c

calculette.o: calculette.c analyse_syntaxique.h
	gcc -g -Wall -c calculette.c

clean:
	rm -f  test_lexeme calculette *.o


