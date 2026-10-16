#include "vigenere.h"
#include "caesar.h"

#include <stdio.h>
#include <string.h>

static int failures = 0;

static void expect_int(const char *name, int got, int expected)
{
    if (got != expected) {
        printf("FAIL %s: got %d, expected %d\n", name, got, expected);
        failures++;
    } else {
        printf("OK   %s\n", name);
    }
}

static void expect_str(const char *name, const char *got, const char *expected)
{
    if (strcmp(got, expected) != 0) {
        printf("FAIL %s: got \"%s\", expected \"%s\"\n", name, got, expected);
        failures++;
    } else {
        printf("OK   %s\n", name);
    }
}

int main(void)
{
    char buf[512];
    char clair[512];
    char cle_out[128];

    printf("--- repeter_cle() ---\n");
    expect_int("repeter exact", repeter_cle("abc", 3, cle_out, sizeof(cle_out)), 0);
    expect_str("repeter exact result", cle_out, "abc");

    expect_int("repeter shorter", repeter_cle("ab", 5, cle_out, sizeof(cle_out)), 0);
    expect_str("repeter shorter result", cle_out, "ababa");

    expect_int("repeter longer", repeter_cle("secret", 3, cle_out, sizeof(cle_out)), 0);
    expect_str("repeter longer result", cle_out, "sec");

    expect_int("repeter single", repeter_cle("k", 4, cle_out, sizeof(cle_out)), 0);
    expect_str("repeter single result", cle_out, "kkkk");

    expect_int("repeter zero len", repeter_cle("secret", 0, cle_out, sizeof(cle_out)), 0);
    expect_str("repeter zero result", cle_out, "");

    expect_int("repeter empty key", repeter_cle("", 5, cle_out, sizeof(cle_out)), -1);

    printf("\n--- encrypt / decrypt ---\n");
    expect_int("classic encrypt",
               codage_vigenere("attackatdawn", "lemon", buf, sizeof(buf)), 0);
    expect_str("classic ciphertext", buf, "lxfopvefrnhr");

    expect_int("classic decrypt",
               decodage_vigenere("lxfopvefrnhr", "lemon", clair, sizeof(clair)), 0);
    expect_str("classic plaintext", clair, "attackatdawn");

    codage_vigenere("bonjour", "cle", buf, sizeof(buf));
    decodage_vigenere(buf, "cle", clair, sizeof(clair));
    expect_str("roundtrip bonjour", clair, "bonjour");

    {
        const char *plain = "bonjour le monde";

        codage_vigenere(plain, "abc", buf, sizeof(buf));
        expect_int("spaces preserved count",
                   (int)(strchr(buf, ' ') != NULL), 1);
        {
            int spaces_plain = 0;
            int spaces_cipher = 0;
            const char *p;

            for (p = plain; *p; p++) {
                if (*p == ' ') {
                    spaces_plain++;
                }
            }
            for (p = buf; *p; p++) {
                if (*p == ' ') {
                    spaces_cipher++;
                }
            }
            expect_int("same number of spaces", spaces_cipher, spaces_plain);
        }
        decodage_vigenere(buf, "abc", clair, sizeof(clair));
        expect_str("roundtrip with spaces", clair, plain);
    }

    {
        const char *plain = "attaque a l'aube ! 2026";

        codage_vigenere(plain, "secret", buf, sizeof(buf));
        expect_int("keeps apostrophe", (int)(strchr(buf, '\'') != NULL), 1);
        expect_int("keeps bang", (int)(strchr(buf, '!') != NULL), 1);
        expect_int("keeps digits", (int)(strstr(buf, "2026") != NULL), 1);
        decodage_vigenere(buf, "secret", clair, sizeof(clair));
        expect_str("roundtrip punctuation", clair, plain);
    }

    {
        char with_space[64];
        char without[64];
        char stripped[64];
        size_t j = 0;
        size_t i;

        codage_vigenere("ab cd", "xy", with_space, sizeof(with_space));
        codage_vigenere("abcd", "xy", without, sizeof(without));
        for (i = 0; with_space[i] != '\0'; i++) {
            if (with_space[i] != ' ') {
                stripped[j++] = with_space[i];
            }
        }
        stripped[j] = '\0';
        expect_str("spaces do not consume key", stripped, without);
    }

    {
        const char *samples_plain[] = {
            "hello",
            "cryptographie",
            "le chiffrement de vigenere",
            "a",
            "zzzzzzzz",
        };
        const char *samples_key[] = {
            "key",
            "mundiapolis",
            "fort",
            "z",
            "abc",
        };
        size_t i;

        for (i = 0; i < sizeof(samples_plain) / sizeof(samples_plain[0]); i++) {
            char name[64];

            codage_vigenere(samples_plain[i], samples_key[i], buf, sizeof(buf));
            decodage_vigenere(buf, samples_key[i], clair, sizeof(clair));
            snprintf(name, sizeof(name), "multi roundtrip %zu", i);
            expect_str(name, clair, samples_plain[i]);
        }
    }

    expect_int("empty encrypt", codage_vigenere("", "cle", buf, sizeof(buf)), 0);
    expect_str("empty encrypt result", buf, "");
    expect_int("empty decrypt", decodage_vigenere("", "cle", clair, sizeof(clair)), 0);
    expect_str("empty decrypt result", clair, "");

    {
        const char *plain = "message secret";
        char cesar_out[128];
        int n = position('d');

        codage_vigenere(plain, "d", buf, sizeof(buf));
        codage(plain, n, cesar_out, sizeof(cesar_out));
        expect_str("single-letter key = Caesar", buf, cesar_out);
        decodage_vigenere(buf, "d", clair, sizeof(clair));
        expect_str("single-letter key roundtrip", clair, plain);
    }

    printf("\n=== %s: %d failure(s) ===\n",
           failures == 0 ? "PASS" : "FAIL", failures);
    return failures == 0 ? 0 : 1;
}
