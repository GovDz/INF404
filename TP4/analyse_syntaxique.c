#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "analyse_syntaxique.h"
#include "type_ast.h"
#include "ast_construction.h"
#include "ast_parcours.h"
#include "analyse_lexicale.h"

TypeOperateur Operateur(Nature_Lexeme nature);

void rec_eag(Ast *A1) {
    seq_terme(A1);
}

void seq_terme(Ast *A2) {
    Ast A1;
    terme(&A1);
    suite_seq_terme(A1, A2);
}

void suite_seq_terme(Ast A1, Ast *A2) {
    Ast A3, A4;
    TypeOperateur op;

    if (op1(&op)) {
        terme(&A3);
        A4 = creer_operation(op, A1, A3);
        suite_seq_terme(A4, A2);
    } else {
        *A2 = A1;
    }
}

void terme(Ast *A1) {
    seq_facteur(A1);
}

void seq_facteur(Ast *A2) {
    Ast A1;
    facteur(&A1);
    suite_seq_facteur(A1, A2);
}

void suite_seq_facteur(Ast A1, Ast *A2) {
    Ast A3, A4;
    TypeOperateur op;

    if (op2(&op)) {
        facteur(&A3);
        A4 = creer_operation(op, A1, A3);
        suite_seq_facteur(A4, A2);
    } else {
        *A2 = A1;
    }
}

void facteur(Ast *A1) {
    switch (lexeme_courant().nature) {
        case ENTIER:
            *A1 = creer_valeur(lexeme_courant().valeur);
            avancer();
            break;
        case PARO:
            avancer();
            rec_eag(A1);
            if (lexeme_courant().nature == PARF) {
                avancer();
            } else {
                handle_error("parenthese fermante attendue");
            }
            break;
        default:
            handle_error("entier ou parenthese ouvrante attendu");
    }
}

int op1(TypeOperateur *Op) {
    switch (lexeme_courant().nature) {
        case PLUS:
        case MOINS:
            *Op = Operateur(lexeme_courant().nature);
            avancer();
            return 1;
        default:
            return 0;
    }
}

int op2(TypeOperateur *Op) {
    switch (lexeme_courant().nature) {
        case MUL:
        case DIV:
            *Op = Operateur(lexeme_courant().nature);
            avancer();
            return 1;
        default:
            return 0;
    }
}

TypeOperateur Operateur(Nature_Lexeme nature) {
    switch (nature) {
        case PLUS:
            return N_PLUS;
        case MOINS:
            return N_MOINS;
        case MUL:
            return N_MUL;
        case DIV:
            return N_DIV;
        default:
            handle_error("Erreur operateur");
    }
}
int analyser(char *nomFichier, Ast *A) {
    demarrer(nomFichier);
    rec_eag(A);

    if (lexeme_courant().nature == FIN_SEQUENCE) {
        printf("\nSyntaxe correcte\n");
        afficherA(*A);
        printf("\n");
        return 1;
    } else {
        handle_error("Erreur lors de l'analyse syntaxique");
        return 0;
    }
}

void handle_error(const char *message) {
    printf("Erreur : %s\n", message);
    exit(1);
}
