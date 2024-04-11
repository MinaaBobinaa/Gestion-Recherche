# Travail pratique 3

## Identification

- **Nom : Naas**
- **Prénoms : Yasmine**
- **Code permanent : NAAY87620206**

---

## Description du programme:
Le programme est un système de gestion et de recherche de recettes conçu pour être
utilisé via une interface en ligne de commande. Il est destiné à charger et à 
interroger une base de données de recettes stockée dans un fichier. Chaque ligne
du fichier représente une recette unique, accompagnée de ses catégories associées, 
qui sont indiquées entre crochets juste après le nom de la recette.
L'utilisateur peut saisir des commandes de recherche à travers le clavier. 
Le programme traite ces commandes pour retrouver et afficher les recettes qui 
correspondent aux critères spécifiés.

Deux types de recherches sont disponibles :
- La recherche par catégorie, qui nécessite uniquement le nom d'une catégorie.
Le programme affichera toutes les recettes qui appartiennent à cette catégorie.
- La recherche par catégorie et mot-clé, où l'utilisateur spécifie une catégorie
et un mot-clé. Le programme affiche les recettes qui appartiennent à la catégorie
spécifiée et dont le nom contient le mot-clé.

## Clone et création dépôt:

Vous devez tout d'abord cloner ce dépôt dans un repertoire en suivant les 
commandes suivantes:

```bash
$ git clone https://gitlab.info.uqam.ca/naas.yasmine/inf3135-hiver2024-tp3.git
```

Pour excecuter les tests unitaires (CUnits) vous devez entrer cette commande:

```bash
$ sudo apt install libcunit1 libcunit1-doc libcunit1-dev
```
## Compilation et Exécution:

Pour compiler le programme, utilisez la commande suivante dans le terminal :

```bash
$ gcc -Wall -Wextra -std=c99 -o recherche main.c liste_chainee.c stats.c
```
sinon vous pouvez utilisez la commande:

```bash
$ make build
```
---

Après compilation, exécutez 'recherche' sans ou avec les arguments qui suivent:

```bash
$ ./recherche liste.txt
```
La commande ci-dessous enregistrera les statistiques de la liste dans un fichier stats.txt:
```bash
$ ./recherche liste.txt -S stats.txt
```

Notez que vous devez avoir un fichier `liste.txt` sous la forme suivante:

```
Paella [espagnol] [riz] [fruits de mer]
Tacos au poulet [mexicain] [poulet]
Gâteau au chocolat [dessert] [chocolat]
Soupe de citrouille [soupe] [vegetarien] [automne]
Salade César [salade] [poulet]
Burger végétalien [vegetarien] [fast-food]
Carpaccio de bœuf [boeuf] [italien]
Crème brûlée [dessert] [français]
Falafel [vegetarien] [moyen-orient]
Gumbo [soupe] [creole]
Hamburger classique [boeuf] [fast-food]
Pad thaï [poulet] [thai]
Pizza margherita [italien] [vegetarien]
Ravioli aux champignons [pâte] [italien] [vegetarien]
```

## Comportement du programme:

A l'excecution du programme (nous allons utiliser la liste ci-dessus pour cet
exemple) on aura comme output:

```bash
Entrez votre critère de recherche (ou 'q' pour quitter) :
```
Voici quelques exemples pour la recherche:

```bash
Entrez votre critère de recherche (ou 'q' pour quitter) : poulet
Pad thaï 
Salade César 
Tacos au poulet 

Entrez votre critère de recherche (ou 'q' pour quitter) : VEGETARIEN
Burger végétalien 
Falafel 
Pizza margherita 
Ravioli aux champignons 
Soupe de citrouille 

Entrez votre critère de recherche (ou 'q' pour quitter) : dessert choco
Gâteau au chocolat 

```
Ci-dessous nous avons d'autres exemples lorsqu'on ne trouve pas de resultats ou
si on a pas respecter le type de recherche:

```bash
Entrez votre critère de recherche (ou 'q' pour quitter) : bbq
Catégorie inexistante

Entrez votre critère de recherche (ou 'q' pour quitter) : poulet spaghetti
Aucun résultat trouvé.

Entrez votre critère de recherche (ou 'q' pour quitter) : poulet tacos dessert
Recherche invalide.

```
Vous pouvez quitter le programme en ecrivant 'q'.

---

Si vous avez executé le programme avec `-S stats.txt`, vous pouvez consulter
le fichier de statistiques en ecrivant la commande suivante:

```bash
$ cat stats.txt
```
Votre fichier affichera différentes statistiques en fonction du déroulement
du jeu.

```text
Le nombre de lignes dans le fichier d'entrée: 14
Le nombre de mots sans doublons: 55
Le nombre de mots avec doublons: 76
La lettre la plus fréquente (sans considérer les doublons): e
Le nombre de catégories : 19
Le nombre de recettes: 14
La catégorie qui a le plus grand nombre de recettes: vegetarien
La recette la plus longue est : Ravioli aux champignons 
```

## Makefile:
Le Makefile fourni est conçu pour faciliter la compilation, les tests et le nettoyage du
programme recherche. Voici un aperçu de son fonctionnement et de ses commandes
principales:

### Commande Principale:
- `make`: Executera `clean` `build` et `cunits` afin de nettoyer, compiler et executer les tests.

### Commande de Build
- `make build`: Compile le projet en créant l'exécutable du programme `recherche`

### Commande de test CUnit
- `make cunits`: Compile et exécute les tests CUnit pour le projet,
puis génère des rapports de couverture de code avec 'gcov'.

### Commande de Nettoyage
- `make clean`: Supprime tous les fichiers générés par le processus de build et
de test, y compris l'exécutable, les fichiers de couverture 
de code et les fichiers de statistiques.

### Commande HTML
- `make html` est utilisée pour convertir le fichier README.md en une version HTML, facilitant ainsi sa lecture dans un navigateur web. Cette opération est effectuée à l'aide de pandoc.


### Commande Phony
- `.PHONY`: Déclare les cibles qui ne correspondent pas à des fichiers réels comme étant 'phony',
évitant ainsi des conflits avec des fichiers de même nom et garantissant que les 
commandes sont toujours exécutées.
