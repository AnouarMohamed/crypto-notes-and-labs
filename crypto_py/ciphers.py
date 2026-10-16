from collections import Counter
from itertools import cycle

A = "abcdefghijklmnopqrstuvwxyz"

# ---------- Caesar ----------
def position(x): return A.find(x)                       # -1 if not a-z
def decalage(x, n): return A[(A.find(x) + n) % 26] if x in A else x
def codage(t, n): return "".join(decalage(c, n) for c in t)   # n<0 = decrypt
def nombre_occurrences(t, x): return t.count(x)

def plus_frequent(t):
    c = Counter(ch for ch in t if ch in A)
    return max(A, key=lambda l: c[l]) if c else ""      # tie -> first in a-z

def decryptage(t):                                      # assume most frequent = 'e'
    l = plus_frequent(t)
    return codage(t, position("e") - position(l)) if l else t

# ---------- Vigenere ----------
def repeter_cle(cle, n): return (cle * n)[:n]

def vigenere(t, cle, s=1):                              # s=1 encrypt, s=-1 decrypt
    if not cle or any(k not in A for k in cle):
        raise ValueError("key must be non-empty and only a-z")
    k = cycle(cle)                                      # only letters use the key
    return "".join(decalage(c, s * position(next(k))) if c in A else c for c in t)

def codage_vigenere(t, cle): return vigenere(t, cle)
def decodage_vigenere(t, cle): return vigenere(t, cle, -1)

if __name__ == "__main__":
    m = "bonjour le monde !"
    c = codage(m, 3)
    print("Cesar     :", m, "->", c, "->", codage(c, -3))
    long = "le chiffrement de cesar est un des plus anciens codes connus"
    print("Auto-decr.:", decryptage(codage(long, 7)))
    m, k = "attaque a l'aube !", "secret"
    c = codage_vigenere(m, k)
    print("Vigenere  :", m, "->", c, "->", decodage_vigenere(c, k))
