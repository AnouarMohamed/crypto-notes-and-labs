#include "caesar.h"
#include "vigenere.h"

#include <stdio.h>

int main(void)
{
    char chiffre[256];
    char clair[256];

    /* --- César --- */
    const char *msg_cesar = "bonjour le monde !";
    int n = 3;

    codage(msg_cesar, n, chiffre, sizeof(chiffre));
    codage(chiffre, -n, clair, sizeof(clair));

    printf("=== Cesar ===\n");
    printf("Message   : %s\n", msg_cesar);
    printf("Decalage  : %d\n", n);
    printf("Chiffre   : %s\n", chiffre);
    printf("Dechiffre : %s\n", clair);

    {
        const char *long_msg =
            "le chiffrement de cesar est un des plus anciens codes connus "
            "en cryptographie classique";
        char auto_out[512];

        codage(long_msg, 7, chiffre, sizeof(chiffre));
        decryptage(chiffre, auto_out, sizeof(auto_out));
        printf("Auto-decrypt : %s\n", auto_out);
    }

    /* --- Vigenere --- */
    {
        const char *msg_vig = "attaque a l'aube !";
        const char *cle = "secret";

        codage_vigenere(msg_vig, cle, chiffre, sizeof(chiffre));
        decodage_vigenere(chiffre, cle, clair, sizeof(clair));

        printf("\n=== Vigenere ===\n");
        printf("Message   : %s\n", msg_vig);
        printf("Cle       : %s\n", cle);
        printf("Chiffre   : %s\n", chiffre);
        printf("Dechiffre : %s\n", clair);
    }

    return 0;
}
