#include "vigenere.h"
#include "caesar.h"

#include <string.h>

int repeter_cle(const char *cle, size_t longueur_texte, char *out, size_t out_size)
{
    size_t cle_len;
    size_t i;

    if (cle == NULL || out == NULL || out_size == 0) {
        return -1;
    }

    cle_len = strlen(cle);
    if (cle_len == 0) {
        return -1;
    }

    if (longueur_texte >= out_size) {
        return -1;
    }

    for (i = 0; i < longueur_texte; i++) {
        out[i] = cle[i % cle_len];
    }
    out[longueur_texte] = '\0';
    return 0;
}

static size_t compter_lettres(const char *texte)
{
    size_t n = 0;

    while (*texte != '\0') {
        if (position(*texte) != -1) {
            n++;
        }
        texte++;
    }
    return n;
}

static int vigenere_transform(const char *texte, const char *cle, int sens,
                              char *resultat, size_t resultat_size)
{
    size_t i;
    size_t len;
    size_t nb_lettres;
    size_t index_cle = 0;
    char cle_etendue[4096];

    if (texte == NULL || cle == NULL || resultat == NULL || resultat_size == 0) {
        return -1;
    }
    if (cle[0] == '\0') {
        return -1;
    }

    len = strlen(texte);
    if (len >= resultat_size) {
        return -1;
    }

    nb_lettres = compter_lettres(texte);
    if (repeter_cle(cle, nb_lettres, cle_etendue, sizeof(cle_etendue)) != 0) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        if (position(texte[i]) != -1) {
            int n = position(cle_etendue[index_cle]);
            resultat[i] = decalage(texte[i], sens * n);
            index_cle++;
        } else {
            resultat[i] = texte[i];
        }
    }
    resultat[len] = '\0';
    return 0;
}

int codage_vigenere(const char *texte, const char *cle,
                    char *resultat, size_t resultat_size)
{
    return vigenere_transform(texte, cle, 1, resultat, resultat_size);
}

int decodage_vigenere(const char *texte, const char *cle,
                      char *resultat, size_t resultat_size)
{
    return vigenere_transform(texte, cle, -1, resultat, resultat_size);
}
