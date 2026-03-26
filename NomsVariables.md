# 1_Maillage

# 3_Assemblage

- **NbLign** : Nombre de lignes et de colonnes de la matrice A
- **NbCoef** : Nombre de coefficients mémorisés de la partie triangulaire
inférieure stricte de A
- **Matrice** : Tableau (de type réel, de longueur >= NbLign+NbCoef) contenant
les coefficients de la diagonale suivis des coeficients non logiquement nuls de
la partie triangulaire inférieure stricte de A
  - **DiagMat** : La première partie de la Matrice
  - **LowMat** : La deuxième partie de la Matrice
- **AdPrCoefLi** : Tableau (de type entier, de longueur >= NbLign) contenant,
pour chaque ligne de la partie triangulaire inférieure stricte de A, l'adresse
du premier coefficient non logiquement nul de cette ligne
- **AdSuccLi** : Tableau (de type entier, de longueur >= NbCoef) contenant pour
chaque coefficient de la partie triangulaire inférieure stricte de A, l'adresse
(position dans LowMat) du coefficient suivant sur la même ligne, ou 0 si le
coefficient est le dernier mémorisé sur la ligne
- **NumCol** : Tableau (de type entier, de longueur >= NbCoef) contenant, pour
chaque coefficient de la partie triangulaire inferieure stricte de A, le numéro
de colonne du coefficient
