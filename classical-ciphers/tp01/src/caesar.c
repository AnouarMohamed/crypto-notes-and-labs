#include "caesar.h"

#include <stdio.h>
#include <string.h>

const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";

int position(char x)
{
    size_t i;

    for (i = 0; i < 26; i++) {
        if (ALPHABET[i] == x) {
            return (int)i;
        }
    }
    return -1;
}

char decalage(char x, int n)
{
    int pos = position(x);
    int nouvelle_position;

    if (pos == -1) {
        return x;
    }

    /* Keep modulo result in [0, 25] even for negative n */
    nouvelle_position = ((pos + n) % 26 + 26) % 26;
    return ALPHABET[nouvelle_position];
}

void codage(const char *texte, int n, char *resultat, size_t resultat_size)
{
    size_t i;
    size_t len;

    if (texte == NULL || resultat == NULL || resultat_size == 0) {
        if (resultat != NULL && resultat_size > 0) {
            resultat[0] = '\0';
        }
        return;
    }

    len = strlen(texte);
    if (len >= resultat_size) {
        len = resultat_size - 1;
    }

    for (i = 0; i < len; i++) {
        if (position(texte[i]) != -1) {
            resultat[i] = decalage(texte[i], n);
        } else {
            resultat[i] = texte[i];
        }
    }
    resultat[i] = '\0';
}

int nombre_occurrences(const char *texte, char x)
{
    int compteur = 0;

    if (texte == NULL) {
        return 0;
    }

    while (*texte != '\0') {
        if (*texte == x) {
            compteur++;
        }
        texte++;
    }
    return compteur;
}

char plus_frequent(const char *texte)
{
    int max_count = 0;
    char lettre_max = '\0';
    size_t i;

    for (i = 0; i < 26; i++) {
        int nb = nombre_occurrences(texte, ALPHABET[i]);
        if (nb > max_count) {
            max_count = nb;
            lettre_max = ALPHABET[i];
        }
    }
    return lettre_max;
}

void decryptage(const char *code, char *resultat, size_t resultat_size)
{
    char lettre = plus_frequent(code);
    int n = position(lettre) - position('e');

    codage(code, -n, resultat, resultat_size);
}
