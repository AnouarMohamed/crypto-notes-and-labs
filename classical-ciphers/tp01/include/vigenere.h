#ifndef VIGENERE_H
#define VIGENERE_H

#include <stddef.h>

/* Q1: repeat/truncate key to match longueur_texte; returns 0 on success */
int repeter_cle(const char *cle, size_t longueur_texte, char *out, size_t out_size);

/* Q3: Vigenère encrypt (spaces/special chars unchanged, do not consume key) */
int codage_vigenere(const char *texte, const char *cle,
                    char *resultat, size_t resultat_size);

/* Decrypt Vigenère with the same key */
int decodage_vigenere(const char *texte, const char *cle,
                      char *resultat, size_t resultat_size);

#endif /* VIGENERE_H */
