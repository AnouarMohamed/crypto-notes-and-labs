# =====================================================================
# UNIVERSITÉ MUNDIAPOLIS - TP N°1 : CRYPTOGRAPHIE (CÉSAR & VIGENÈRE)
# Module : Cryptographie | Année Universitaire : 2026-2027
# Enseignant : A. AGRIMA
# =====================================================================

alphabet = "abcdefghijklmnopqrstuvwxyz"

# ---------------------------------------------------------------------
# EXERCICE 1 : CODE DE CÉSAR
# ---------------------------------------------------------------------

# Partie 1 - Question 1 : Fonction position()
def position(x):
    for i in range(len(alphabet)):
        if alphabet[i] == x:
            return i
    return -1

print("Position de 'a' :", position('a'))
print("Position de 'd' :", position('d'))
print("Position de 'é' :", position('é'))


# Partie 1 - Question 2 : Fonction decalage()
def decalage(x, n):
    pos = position(x)
    if pos == -1:
        return x
    nouvelle_position = (pos + n) % 26
    return alphabet[nouvelle_position]

print("Décalage ('d', 3) :", decalage('d', 3))
print("Décalage ('z', 3) :", decalage('z', 3))
print("Décalage ('g', -3) :", decalage('g', -3))
print("Décalage ('c', -3) :", decalage('c', -3))


# Partie 1 - Question 3 : Fonction codage()
def codage(texte, n):
    resultat = ""
    for lettre in texte:
        if position(lettre) != -1:
            resultat = resultat + decalage(lettre, n)
        else:
            resultat = resultat + lettre
    return resultat

texte_cesar = "le chiffre de cesar est tres facile a comprendre !"
code_cesar = codage(texte_cesar, 3)
print("Texte chiffré (César) :", code_cesar)


# Partie 2 - Question 1 : Explication théorique
# Le chiffrement de César utilise un décalage constant n (de 0 à 25) pour
# toutes les lettres : C = (P + n) % 26. Connaître le codage C d'un seul
# caractère clair P permet de résoudre l'équation à une seule inconnue :
# n = (C - P) % 26, et donc de déchiffrer tout le message avec codage(code, -n).


# Partie 2 - Question 2 : Fonction nombre_occurrences()
def nombre_occurrences(texte, x):
    compteur = 0
    for caractere in texte:
        if caractere == x:
            compteur = compteur + 1
    return compteur

print("Occurrences de 'o' dans 'bonjour' :", nombre_occurrences("bonjour", 'o'))


# Partie 2 - Question 3 : Fonction plus_frequent()
def plus_frequent(texte):
    max_occ = 0
    lettre_max = ""
    for lettre in alphabet:
        nb = nombre_occurrences(texte, lettre)
        if nb > max_occ:
            max_occ = nb
            lettre_max = lettre
    return lettre_max

print("Lettre la plus fréquente dans le code :", plus_frequent(code_cesar))


# Partie 2 - Question 4 : Décryptage automatique
def decryptage(code):
    lettre = plus_frequent(code)
    n = (position(lettre) - position('e')) % 26
    return codage(code, -n)

print("Texte décrypté (César) :", decryptage(code_cesar))


# ---------------------------------------------------------------------
# EXERCICE 2 : CHIFFRE DE VIGENÈRE
# ---------------------------------------------------------------------

# Question 1 : Répéter la clé
def repeter_cle(cle, longueur_texte):
    cle_repetee = ""
    while len(cle_repetee) < longueur_texte:
        cle_repetee = cle_repetee + cle
    return cle_repetee[:longueur_texte]

print("Clé répétée ('cle', 10) :", repeter_cle("cle", 10))


# Question 2 : Transformer une lettre en décalage
# On réutilise directement la fonction position(x) de l'Exercice 1.


# Question 3 : Chiffrer le texte
def chiffrer_vigenere(texte, cle):
    resultat = ""
    cle_repetee = repeter_cle(cle, len(texte))
    for i in range(len(texte)):
        lettre = texte[i]
        if position(lettre) != -1:
            n = position(cle_repetee[i])
            resultat = resultat + decalage(lettre, n)
        else:
            resultat = resultat + lettre
    return resultat


# Question 4 : Fonction de décryptage du chiffrement de Vigenère
def dechiffrer_vigenere(code, cle):
    resultat = ""
    cle_repetee = repeter_cle(cle, len(code))
    for i in range(len(code)):
        lettre = code[i]
        if position(lettre) != -1:
            n = position(cle_repetee[i])
            resultat = resultat + decalage(lettre, -n)
        else:
            resultat = resultat + lettre
    return resultat

texte_vigenere = "bonjour tout le monde ! 2026"
cle_vigenere = "secret"
code_vigenere = chiffrer_vigenere(texte_vigenere, cle_vigenere)

print("Texte chiffré (Vigenère) :", code_vigenere)
print("Texte déchiffré (Vigenère) :", dechiffrer_vigenere(code_vigenere, cle_vigenere))
