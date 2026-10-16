#ifndef CAESAR_H
#define CAESAR_H

#include <stddef.h>

extern const char ALPHABET[];

/* Q1: index of x in alphabet, or -1 if absent */
int position(char x);

/* Q2: shift letter x by n positions (modulo 26) */
char decalage(char x, int n);

/* Q3: Caesar encrypt/decrypt; only a-z are modified */
void codage(const char *texte, int n, char *resultat, size_t resultat_size);

/* Partie 2 Q2 */
int nombre_occurrences(const char *texte, char x);

/* Partie 2 Q3: most frequent a-z letter in texte */
char plus_frequent(const char *texte);

/* Partie 2 Q4: auto-decrypt assuming most frequent letter = 'e' */
void decryptage(const char *code, char *resultat, size_t resultat_size);

#endif /* CAESAR_H */
