# TP N°1 : Cryptographie (C)

Implémentation en **C** du chiffrement de César et du chiffre de Vigenère  
(Université Mundiapolis — Module Cryptographie 2026-2027).

## Structure

```
tp01/
├── include/
│   ├── caesar.h
│   └── vigenere.h
├── src/
│   ├── caesar.c      # position, decalage, codage, decryptage, …
│   ├── vigenere.c    # repeter_cle, codage/decodage Vigenère
│   └── main.c        # démonstration
├── tests/
│   ├── test_caesar.c
│   └── test_vigenere.c
├── Makefile
└── README.md
```

Théorie Partie 2 Q1 : [`../../notes/tp01-partie2-question1.md`](../../notes/tp01-partie2-question1.md)

## Compilation / exécution

```bash
cd classical-ciphers/tp01
make          # compile demo + lance les tests
make demo && ./build/tp01_demo
make test
make clean
```

## Fonctions (César)

| Fonction | Rôle |
|----------|------|
| `position(x)` | indice dans `abcdefghijklmnopqrstuvwxyz`, sinon `-1` |
| `decalage(x, n)` | décale `x` de `n` (modulo 26) |
| `codage(texte, n, out, size)` | chiffre / déchiffre (négatif) |
| `nombre_occurrences` / `plus_frequent` | analyse de fréquences |
| `decryptage` | déchiffrement auto (lettre max ≈ `'e'`) |

## Fonctions (Vigenère)

| Fonction | Rôle |
|----------|------|
| `repeter_cle` | étend / coupe la clé |
| `codage_vigenere` | chiffrement |
| `decodage_vigenere` | déchiffrement |

Les espaces et caractères spéciaux sont conservés et **ne consomment pas** de lettre de clé.
