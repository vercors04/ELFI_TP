# TP1 : Générateur de Maillage Structuré

Ce TP implémente un générateur de maillage structuré (Triangles P1 ou Quadrangles Q1) sur un domaine rectangulaire $\Omega = [a,b] \times [c,d]$.

##  Fonctionnalités

* **Domaine :** Discrétisation structurée d'un rectangle défini par les bornes $a, b, c, d$.
* **Subdivision :** Le domaine est découpé en $(n_1 - 1) \times (n_2 - 1)$ rectangles élémentaires.
* **Types d'éléments ($t$) :**
    * **Type 1 (Quadrangles) :** Éléments rectangulaires (Q1).
    * **Type 2 (Triangles) :** Découpage des quadrangles par leur diagonale (P1).
* **Entrées/Sorties :**
    * Lecture de configuration (fichier ou interactif).
    * Génération d'un fichier de maillage formaté pour solveur MEF.

##  Conventions et Topologie

### Structure du Fichier de Maillage 

Le fichier de sortie respecte le format suivant, nécessaire pour la lecture par le solveur :

* **En-tête :** Nombre de nœuds suivi de leurs coordonnées.
* **Paramètres :** Une ligne contenant `m t p q` (nombre d'éléments, type, points/élément, arêtes/élément).
* **Connectivité :** Liste des éléments avec leurs sommets ($s_i$) et les références des arêtes ($r_i$).

### Topologie des Éléments

La numérotation locale des nœuds et des arêtes suit l'élément de référence.

#### Pour les Triangles (Type 2)
L'ordre des sommets impose la correspondance suivante pour les arêtes :

* **Arête 1 :** Diagonale
* **Arête 2 :** Côté Vertical
* **Arête 3 :** Côté Horizontal

#### Pour les Quadrangles (Type 1)
La correspondance est la suivante :

1.  **Arête 1 :** Droite ($x=b$ local)
2.  **Arête 2 :** Haut ($y=d$ local)
3.  **Arête 3 :** Gauche ($x=a$ local)
4.  **Arête 4 :** Bas ($y=c$ local)

### Numéros de Référence (Conditions aux Limites)
Les étiquettes (numéros de référence) utilisées pour identifier les conditions aux limites suivent ce schéma :

```text
                        3 (Haut / y=d)
                     ------------------
                    |                  |
   4 (Gauche / x=a) |   0 (Intérieur)  | 2 (Droite / x=b)
                    |                  |
                     ------------------
                        1 (Bas / y=c)