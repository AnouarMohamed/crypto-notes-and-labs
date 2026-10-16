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

static void expect_char(const char *name, char got, char expected)
{
    if (got != expected) {
        printf("FAIL %s: got '%c', expected '%c'\n", name, got, expected);
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
    char tmp[512];
    int n;

    printf("--- position() ---\n");
    expect_int("position('a')", position('a'), 0);
    expect_int("position('d')", position('d'), 3);
    expect_int("position('z')", position('z'), 25);
    expect_int("position('e')", position('e'), 4);
    /* Accented letters are outside a-z (lab example: position('é') -> -1) */
    expect_int("position('#')", position('#'), -1);
    expect_int("position('A')", position('A'), -1);
    expect_int("position('5')", position('5'), -1);
    expect_int("position(' ')", position(' '), -1);

    printf("\n--- decalage() ---\n");
    expect_char("decalage('d', 3)", decalage('d', 3), 'g');
    expect_char("decalage('z', 3)", decalage('z', 3), 'c');
    expect_char("decalage('g', -3)", decalage('g', -3), 'd');
    expect_char("decalage('c', -3)", decalage('c', -3), 'z');
    expect_char("decalage('m', 0)", decalage('m', 0), 'm');
    expect_char("decalage('a', 26)", decalage('a', 26), 'a');
    expect_char("decalage('a', 29)", decalage('a', 29), 'd');

    printf("\n--- codage() ---\n");
    codage("abc", 1, buf, sizeof(buf));
    expect_str("codage(\"abc\", 1)", buf, "bcd");

    codage("xyz", 3, buf, sizeof(buf));
    expect_str("codage(\"xyz\", 3)", buf, "abc");

    codage("bonjour le monde", 3, buf, sizeof(buf));
    expect_str("codage spaces", buf, "erqmrxu oh prqgh");

    codage("hello!", 1, buf, sizeof(buf));
    expect_str("codage punctuation", buf, "ifmmp!");

    codage("test123", 2, buf, sizeof(buf));
    expect_str("codage digits", buf, "vguv123");

    codage("attaque", 5, buf, sizeof(buf));
    codage(buf, -5, tmp, sizeof(tmp));
    expect_str("codage roundtrip -5", tmp, "attaque");

    codage("", 7, buf, sizeof(buf));
    expect_str("codage empty", buf, "");

    codage("cryptographie !", 0, buf, sizeof(buf));
    expect_str("codage shift 0", buf, "cryptographie !");

    for (n = 0; n < 26; n++) {
        const char *msg = "le secret est bien garde.";
        char name[64];

        codage(msg, n, buf, sizeof(buf));
        codage(buf, -n, tmp, sizeof(tmp));
        snprintf(name, sizeof(name), "roundtrip shift %d", n);
        expect_str(name, tmp, msg);
    }

    printf("\n--- nombre_occurrences() / plus_frequent() ---\n");
    expect_int("occurrences o in bonjour", nombre_occurrences("bonjour", 'o'), 2);
    expect_int("occurrences z absent", nombre_occurrences("bonjour", 'z'), 0);
    expect_int("occurrences empty", nombre_occurrences("", 'a'), 0);
    expect_char("plus_frequent aaabb", plus_frequent("aaabb"), 'a');
    expect_char("plus_frequent tie abab", plus_frequent("abab"), 'a');

    printf("\n--- decryptage() ---\n");
    {
        const char *plain =
            "le chiffrement de cesar est un des plus anciens codes connus "
            "en cryptographie classique et il repose sur un simple decalage";
        int shifts[] = {3, 7, 13, 19};
        size_t i;

        for (i = 0; i < sizeof(shifts) / sizeof(shifts[0]); i++) {
            char name[64];

            codage(plain, shifts[i], buf, sizeof(buf));
            decryptage(buf, tmp, sizeof(tmp));
            snprintf(name, sizeof(name), "decryptage shift %d", shifts[i]);
            expect_str(name, tmp, plain);
        }
    }

    {
        const char *plain = "eeeeeeeeee aaa bbb";

        codage(plain, 3, buf, sizeof(buf));
        expect_char("most frequent after +3 is h", plus_frequent(buf), 'h');
        decryptage(buf, tmp, sizeof(tmp));
        expect_str("decryptage eeee...", tmp, plain);
    }

    printf("\n=== %s: %d failure(s) ===\n",
           failures == 0 ? "PASS" : "FAIL", failures);
    return failures == 0 ? 0 : 1;
}
