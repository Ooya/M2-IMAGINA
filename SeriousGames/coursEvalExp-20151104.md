> Jusqu'ici on a vu
>
> - jeu
>    - jeu vidéo
>        - Gameplay *1~5min*
>        - level design *~30min >=*

# Evaluation et expérimentation

## Introduction

***Les statistiques*** offrent un ensemble d eprocédures et de méthodes mathématiques pour **organiser**, **résumer** et **interpréter** de l'**information**.

***La population*** est l'ensemble de tous les individus qui font l'objet de l'étude.

***Une variable*** est une propriété/caractéristique propre à la population.

***Une donnée*** est la valeur mesurée d'une variable sur un individu.

***Un paramètre*** est une valeur numérique attachée à la population. Généralement, cette valeur est dérivée des données de la population.

**_Une statistique_** est une valeur numérique attachée à un échantillon. Généralement, cette valeur est dérivée des données de l'échantillon.

## Section statistique descriptive et statistique inférentielle

- **_Les statistiques descriptives_** offrent un ensemble de procédure pour résumer, organiser, simplifier les données
- Exemple de paramètres / sttatistiques étudiés : moyenne, écart type, mode, médiane, min, max, intervalle de confiance
- Statistique inférentielle nous offre un ensemble de procédures qui permettent d'étudier des échantillons et de généraliser les résultats obtenus à la population
- Erreur d'échantillonnage :
    - C'est la différence qui va exister entre la statistique d'un échantillon et le paramètre de la population
    - Cette différence est inhérente et naturelle pour un processus d'échantillonnage.


    Population -> Echantillonage -> Echantillon -> Resultats -> Population -> ...

### Utilisation des stats dans une étude expérimentale

Schéma général d'utilisation des statistiques dans une étude expérimentale

1. Etape 1 : fixer la population et établir l'objectif de l'étude
    1. Avoir des échantillons de la population
    2. Récolter des données
2. Etape 2 : statistique descriptive
    1. Calculer les statistiques descriptives (moyenne, variance ...)
3. Etape 3 : Statistique inférentielle
    1. Nous devons répondre à la question suivante avec un certain degré de confiance
        - la différence des statistiques des échantillons est causée par : l'erreur d'échantillonnage, ou par le traitement.

## Les différents types d'études expérimentales

### Etudier une variable individuellement

### Etudier les relations entre des variables

- Etudier la corrélation entre deux variables
    - mesurer deux variables par individu
    - calculer l'indice de corrélation entre ces deux variables
    - attention : la corrélation de signifie pas causalité
    - pour déduire la causalité : méthode expérimentale

### Présentation de la méthode expérimentale

- L'objectif est de démontrer une relation de cause à effet entre deux variables
- Le changmenet de valeur d'une variable va causer/produire des changements sur une autre variable
- Exemple : force et accélération en physique
- Deux propriétés importantes des méthodes expérimentales :
    - manipulation : pouvoir manipuler une variable en observant une autre
    - exemple : manipuler la force à appliquer sur un objet avec un ressort
    - le contrôle : nous devons assurer que tous les paramètres externes pouvant influencer les données sont contrôlés durant l'expérimentation afin de minimiser leurs effets

### Présentation de la méthode non expérimentale

- Deux sous catégories
    - étude sur des groupes non-équivalents (homme vs femme; tranche d'âge)
    - Pré - Post traitement
- Ici les conditions expérimentales rendent le contrôle plus difficile
- D'autre paramètres peuvent être à l'origine des effets mesurés
- Par exemple : la différence inhérente entre les groupes; le temps qui s'écoule entre les mesures
- Nous alons utiliser pour ces méthodes les mêmes outils et la même terminologie que pour les méthodes expérimentales

## Les variables

**_Variable discrète_** valeurs distinctes et séparées sans valeurs intermédiaires

**_Variable continue_** il y a une infinité de valeurs entre deux variables

**_Les échelles de mesure_** : **nominale** (ensemble simple de valeurs distinces), **ordinale** (ensemble ordonné de valeurs), **intervalle** (ensemble ordonné avec une distance entre les valeurs), **ratio** (une échelle intervalle où le zéro signifie l'absence de la quantité mesurée).

## Mesures de la tendance centreale et la variabilité

- La moyenne
- La médiane
- La variabilité
    - la variabilité mesure la dispersion autour de la moyenne
- Degré de liberté

## Normalisation des mesures avec Z-score

### Résumer les mesures

Nous savons résumer un ensemble de mesures par un couple : tendance centrale et variabilité. Pour une population le couple (u,o) et pour un échantillon le couple (M,s) résument les informations connues sur la population et l'échantillon

### Ecriture standard

Notre objectif maintenant est de trouver une écriture standard pour pouvoir comparer différentes distributions de mesures. Cette écriture est le z-score et se calcule comme suit :

- pour une population : $z_{i} = \frac{X_{i}-\mu}{\sigma}$
- pour un échantillon : $z_{i} = \frac{X_{i}-M}{S}$

On peut voir que le _z score_ représente la déviation de la moyenne mesurée en utilisant la déviation standard comme unité de longueur. Z-score peut être positif ou négatif. En transformant toutes les mesures avec leurs z-score, nous obtenons une distribution standardisée qui est centrée autour de 0 et la valeur $\pm$1 correspond à $\pm\sigma$

### Avantages du z-score

Nous pouvons faire des comparaisons entre les distributions standardisées. Nous pouvons faire des transformations de scores en conservant certaines propriétés (comme la fréquence et l'ordre entre les fréquences).

Etudiant # | Note
:---------:|:---:
    1      |  3
    2      |  5
    3      |  5
    4      |  7
    5      |  1
    6      |  1
    7      |  6
    8      |  6
    9      |  7
    10     |  9

- Quels sont les z-scores de la population
- Nous allons prendre l'échantillon des étudiants avec des numéros pairs
- Quels sont les z-scores pour cet échantillon

_Population_

Moyenne : 5

Déviation = $\sqrt{variance}$

Variance = $\frac{SS}{N}$

SS est la somme des différences à la moyenne au carré.

$SS = 4+0+0+4+16+16+1+1+4+16 = 62$

Variance = $\frac{62}{10} = 6,2$

$\sigma = \sqrt{6,2} \approx 2,5$

| Etudiant # | Note | Z-score |
|:----------:|:----:|:-------:|
|     1      |  3   |  -0,8   |
|     2      |  5   |    0    |
|     3      |  5   |    0    |
|     4      |  7   |   0,8   |
|     5      |  1   |  -1,6   |
|     6      |  1   |  -1,6   |
|     7      |  6   |   0,4   |
|     8      |  6   |   0,4   |
|     9      |  7   |   0,8   |
|     10     |  9   |   1,8   |

_Echantillon_

| Etudiant # | $d_{i}$ | $d^{2}$ |
|:----------:|:-------:|:-------:|
|     2      |  -0,6   |  0,36   |
|     4      |   1,4   |  1,94   |
|     6      |  -4,6   |  21,16  |
|     8      |   0,4   |  0,16   |
|     10     |   3,4   |  11,56  |

> Checker wikipédia est recommandé lol

## Distribution des moyennes des échantillons

### Erreur d'échantillonnage

- L'erreur d'échantillonnage est une erreur intrinsèque
- C'est la différence entre la statistique de l'échantillon et le paramètre de la population
- Cette erreur suit une loi !
- C'est le théorème central limite qui le prouve
- Les moyennes $M_{i}$ des échantillons de taille $n$ suivent une loi normale de moyenne $\mu$ et d'écart type $\frac{\sigma}{\sqrt{n}}$

## Test de Student

Nous savons calculer le z-score. Nous savons calculer l'erreur standard $\sigma_{M}=\frac{\sigma}{\sqrt{n}}$ pour un échantillon. _Problème :_ la formule de $\sigma_{M}$ utilise $\sigma$ ladéviation standard de la population, comment l'obtenir ? _Solution :_ nous allons simplement estimer $\sigma$ en utilisant la variance de l'échantillon $s^{2}=\frac{SS}{ddl}$. Erreur standard estimée devient donc : $S_{M}=\frac{s}{\sqrt{n}}$.

### Formule du t-score

La formule du t-score utilise le même principe que pour un z-score en remplaçant $\sigma{M}$ par son estimateur $s_{M}$.

$$t_{M}=\frac{M-\mu}{s_{M}}$$

- $\mu$ est la moyenne pour la population
- $M$ est la moyenne pour l'échantillon
- $s_{M} est l'erreur standard estimée pour l'échantillon

### Hypothèse H0

H0 : L'hypothèse 0 est formulée : En moyenne, pour la population, la différence entre les mesures vaut 0.

Le t-score pour $D$ est :
$$t_{D}=\frac{M_{D}-\mu_{D}}{s_{M_{D}}}$$

### Prendre une décision

- L'étape suivante est de comparer la valeur de $t_{D}$ avec la table de la loi de student
- Attention, il faut lire la bonne valeur dans la table :
    - le bon $\alpha$
    - le bon degré de liverté
- Si $t_{D}$ est supérieur à la valeur de la table, alors on peut rejeter H0 avec un risque d'erroeur de $\alpha$
- Sinon, la différence n'est pas statistiquement significative; elle peut être causée simplement par le hasard.

## Mesures répétées

### Exemple

| A  | B  | D  | $(D-M_{D})^{2}$ |
|:--:|:--:|:--:|:---------------:|
| 6  | 9  | -3 |        0        |
| 8  | 9  | -1 |        4        |
| 7  | 10 | -3 |        0        |
| 7  | 11 | -4 |        1        |
| 8  | 11 | -3 |        0        |
| 6  | 9  | -3 |        0        |
| 5  | 11 | -6 |        9        |
| 10 | 11 | -1 |        4        |
| 8  | 11 | -3 |        0        |

Moyenne $M_{D}$ = -3

$s^{2} = 2,25$

$s_{M_{D}} = 0,5$

$t=\frac{M_{D}}{s_{M_{D}}} = \frac{-3}{0,5} = -6$

Région critique pour un ddl = 8 et $\alpha$ = 0,001 = 3,355 |t| = 6 > 3,355. Donc on rejette H0 !

La différence est significative il y a donc un effet qui n'est pas simplement du au hasard (avec un risque d'erreur de 0,01).
