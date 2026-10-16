from ciphers import *

# Caesar
assert [position(c) for c in "adz#A5 "] == [0, 3, 25, -1, -1, -1, -1]
assert decalage("d", 3) == "g" and decalage("z", 3) == "c" and decalage("c", -3) == "z"
assert decalage("a", 26) == "a" and decalage("a", 29) == "d" and decalage("a", 2**31) == "y"
assert codage("xyz", 3) == "abc" and codage("bonjour le monde", 3) == "erqmrxu oh prqgh"
assert codage("test123!", 2) == "vguv123!" and codage("", 7) == ""
assert all(codage(codage("le secret.", n), -n) == "le secret." for n in range(26))
assert nombre_occurrences("bonjour", "o") == 2 and nombre_occurrences("", "a") == 0
assert plus_frequent("aaabb") == "a" and plus_frequent("abab") == "a" and plus_frequent("123") == ""
p = "le chiffrement de cesar est un des plus anciens codes connus en cryptographie classique"
assert all(decryptage(codage(p, n)) == p for n in (3, 7, 13, 19))
assert decryptage("123 !!!") == "123 !!!" and decryptage("") == ""

# Vigenere
assert repeter_cle("abc", 3) == "abc" and repeter_cle("ab", 5) == "ababa"
assert repeter_cle("secret", 3) == "sec" and repeter_cle("k", 4) == "kkkk"
assert codage_vigenere("attackatdawn", "lemon") == "lxfopvefrnhr"
assert decodage_vigenere("lxfopvefrnhr", "lemon") == "attackatdawn"
for t, k in [("bonjour le monde", "abc"), ("attaque a l'aube ! 2026", "secret"),
             ("hello", "key"), ("a", "z"), ("zzzzzzzz", "abc"), ("", "cle")]:
    assert decodage_vigenere(codage_vigenere(t, k), k) == t
assert codage_vigenere("ab cd", "xy").replace(" ", "") == codage_vigenere("abcd", "xy")  # spaces skip key
assert codage_vigenere("message secret", "d") == codage("message secret", 3)             # 1-letter key = Caesar
assert len(codage_vigenere("a" * 10000, "key")) == 10000                                 # no length limit
for bad in ("", "SECRET", "se3ret"):
    try: codage_vigenere("abc", bad); raise SystemExit("bad key accepted: " + bad)
    except ValueError: pass

print("ALL TESTS PASSED")
