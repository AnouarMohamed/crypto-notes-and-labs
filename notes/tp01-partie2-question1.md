# TP N°1 — Partie 2, Question 1

## Énoncé

Expliquer pourquoi il suffit de connaître le codage d’un seul caractère pour retrouver le décalage utilisé dans le chiffrement de César et ainsi décoder tout le message.

## Réponse

Dans le chiffrement de César, **toutes les lettres sont décalées du même nombre** \(n\) de positions dans l’alphabet.

Formellement, pour toute lettre \(x\) :

\[
C(x) = (position(x) + n) \bmod 26
\]

Si l’on connaît **une seule** paire (lettre claire \(p\), lettre chiffrée \(c\)), on retrouve immédiatement le décalage :

\[
n = (position(c) - position(p)) \bmod 26
\]

Parce que \(n\) est **unique et constant** pour tout le message, ce même \(n\) sert à déchiffrer **chaque** caractère :

\[
P(c) = (position(c) - n) \bmod 26
\]

### Illustration

Si l’on sait que `'e'` a été chiffré en `'h'` :

- \(n = position('h') - position('e') = 7 - 4 = 3\)
- tout le texte se déchiffre alors avec un décalage de \(-3\)

C’est aussi le principe de l’analyse de fréquences en français : on suppose que la lettre la plus fréquente du chiffré correspond au `'e'` du clair, ce qui donne exactement cette paire \((p, c)\) et donc \(n\).
