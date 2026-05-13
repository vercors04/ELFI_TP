# Projet Librairie Éléments Finis (ELFI)

Mini librairie Elements finis réalisée dans le cadre du master 1 CSM à
l'université de Rennes.

## Architecture du Projet

**La documentation de chaque fonction** se trouve dans le header associé à
cette dernière (chaque dossier contient un header declarant les fonctions
qui s'y trouvent).

A chaque TP est associé un fichier main qui met en oeuvre les fonctions
réalisées.

La compilation et l'execution  doit se faire dans le dossier "Executables/".
Il suffit de lancer le fichier .sh associé puis le .exe qui en découle.

Le projet est en réalisation sur 5 phases.

### Phase 1 : Pré-traitement Géométrique

TP1 : Construction de la triangulation

- Discrétisation du domaine $\Omega$ en triangles ($P_1$) ou quadrangles ($Q_1$).
- Attribution des références pour les conditions aux limtes.

Fonctions produites :

- maillage : Créé - à partir des bornes définissant le domaine, du nombre de points
sur les cotés, du type des éléments à construire et des 5 numéros de
référence - un fichier de maillage
- lecfima : Lit un fichier de maillage et remplis les variables associées dans le
programme
- etiqAr :

### Phase 2

TP2a : Procédures utilitaires pour les calculs élémentaires

Les fichiers qui ont été produits dans le cadre de ce TP se trouvent dans le
dossier "2a_ElementaireA/".

TP2b : Calculs élémentaires

Les fichiers qui ont été produits dans le cadre de ce TP se trouvent dans le
dossier "2b_ElementaireB/".

### Phase 3

TP3 : Assemblage
Construction du système linéaire.

### Phase 4

TP4 : Système Linéaire & Projet
Prise en compte des conditions aux limites de Dirichlet.

### Phase 5

TP5 : mise en pratique
Résolution et Post-Traitement
Analyse des résultats et rédaction d'un rapport

#### Calcul des fonctions

Calcul de $F_{\Omega}$ :

## Liste des fichiers dont nous ne sommes pas les auteurs initiaux

- alloctab.c
- freetab.c
- impcalel.c
- ww.c
- assmat.f (Fortran)
- affsmd.f (Fortran)
- cdesse.f (Fortran)
- tri.f    (Fortran)
- affsmo.f (Fortran)
- forfun.h (Fortran)
- affsol.f (Fortran)
- dsmoapr.o
- impmpr.f (Fortran)
- ltlpr.f  (Fortran)
- rsprl.f  (Fortran)
- rspru.f  (Fortran)
- solex.c

## Structure du projet

```text
├── 1_Maillage
│   ├── etiqAr.c
│   ├── lecfima.c
│   ├── maillage.c
│   ├── maillage.h
│   ├── main1.c
│   └── modeSaisie2.c
├── 2a_ElementaireA
│   ├── elementairesa.h
│   ├── fct_elementairesa.c
│   └── main2a.c
├── 2b_ElementaireB
│   ├── adwdw.c
│   ├── cal1Elem.c
│   ├── elementairesb.h
│   ├── fct_def_pb.c
│   ├── impcalel.c
│   ├── intAret.c
│   ├── intElem.c
│   ├── main2b.c
│   ├── w.c
│   └── ww.c
├── 3_Assemblage
│   ├── affsmd.f
│   ├── affsmd.o
│   ├── assemblage.c
│   ├── assemblage.h
│   ├── assmat.f
│   ├── assmat.o
│   ├── main3.c
│   └── READMEtp3
├── 4_Construction_SL
│   ├── affsmo.f
│   ├── affsmo.o
│   ├── cdesse.f
│   ├── cdesse.o
│   ├── construction_SL.h
│   ├── dSMDaSMO.c
│   ├── main4.c
│   ├── tri.f
│   └── tri.o
├── 5_Resol_Post-Trait
│   ├── affsol.f
│   ├── affsol.o
│   ├── CalSol.c
│   ├── dSMOaPR.c
│   ├── dsmoapr.h
│   ├── dsmoapr.o
│   ├── impmpr.f
│   ├── impmpr.o
│   ├── ltlpr.f
│   ├── ltlpr.o
│   ├── main5Test.c
│   ├── ResolSyst.c
│   ├── rsprl.f
│   ├── rsprl.o
│   ├── rspru.f
│   ├── rspru.o
│   └── solex.c
├── Donnees_1
│   ├── car1x1q_4
│   ├── car1x1t_1
│   ├── car1x1t_4
│   ├── car3x3t_3
│   ├── ficInput.txt
│   ├── ficOutput.txt
│   └── verif_lecfima.txt
├── Donnees_2
│   ├── NUMREF.Test
│   ├── Tests.1x1
│   └── Tests.3x3
├── Donnees_3
│   ├── tp3_RESU1
│   ├── tp3_RESU1_NeumannHomogene
│   ├── tp3_RESU3
│   └── tp3_RESU3_NeumannHomogene
├── Donnees_4
│   ├── tp4_RESU1
│   └── tp4_RESU3
├── Donnees_5
│   ├── Maillages
│   │   ├── d1q1_16
│   │   ├── d1q1_2
│   │   ├── d1q1_32
│   │   ├── d1q1_4
│   │   ├── d1q1_64
│   │   ├── d1q1_8
│   │   ├── d1t1_16
│   │   ├── d1t1_2
│   │   ├── d1t1_32
│   │   ├── d1t1_4
│   │   ├── d1t1_64
│   │   ├── d1t1_8
│   │   ├── d2q1_16
│   │   ├── d2q1_2
│   │   ├── d2q1_32
│   │   ├── d2q1_4
│   │   ├── d2q1_64
│   │   ├── d2q1_8
│   │   ├── d2t1_16
│   │   ├── d2t1_2
│   │   ├── d2t1_32
│   │   ├── d2t1_4
│   │   ├── d2t1_64
│   │   ├── d2t1_8
│   │   └── README
│   └── tp5_RESU_d1t1_2_complet
├── Executables
│   ├── main1.exe
│   ├── main1.sh
│   ├── main2a.exe
│   ├── main2a.sh
│   ├── main2b.exe
│   ├── main2b.sh
│   ├── main3.exe
│   ├── main3.sh
│   ├── main4.sh
│   ├── main5Test.sh
│   ├── mainAff.sh
│   ├── mainErreur.exe
│   ├── mainErreur.sh
│   ├── main.exe
│   ├── plot.exe
│   ├── plot.sh
│   └── testProfil.exe
├── Resultats
│   ├── Graphes
│   │   ├── 111.png
│   │   ├── 112.png
│   │   ├── 121.png
│   │   ├── 122.png
│   │   ├── 131.png
│   │   ├── 132.png
│   │   ├── 211.png
│   │   ├── 212.png
│   │   ├── 221.png
│   │   ├── 222.png
│   │   ├── 231.png
│   │   └── 232.png
│   ├── fort.111
│   ├── fort.112
│   ├── fort.121
│   ├── fort.122
│   ├── fort.131
│   ├── fort.132
│   ├── fort.211
│   ├── fort.212
│   ├── fort.221
│   ├── fort.222
│   ├── fort.231
│   ├── fort.232
│   └── plot.c
├── Utilitaire
│   ├── alloctab.c
│   ├── allocvec.c
│   ├── freetab.c
│   ├── freevec.c
│   ├── print.c
│   └── utilitaires.h
├── Compte_Rendu_Amyne_Xavier.pdf
├── forfun.h
├── mainAff.c
├── mainErreur.c
└── README.md
```
