# Projet Librairie Éléments Finis (ELFI)

Mini librairie Elements finis réalisée dans le cadre du master 1 CSM.

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

## Structure du projet

```text
└── ELFI_TP
    ├── README.md
    ├── Executables
    │   ├── main2a.sh
    │   ├── main1.sh
    │   └── main2b.sh
    ├── Donnees_3
    │   ├── tp3_RESU3
    │   ├── tp3_RESU1
    │   ├── tp3_RESU3_NeumannHomogene
    │   └── tp3_RESU1_NeumannHomogene
    ├── 2a_ElementaireA
    │   ├── fct_elementairesa.c
    │   ├── elementairesa.h
    │   └── main2a.c
    ├── 2b_ElementaireB
    │   ├── elementairesb.h
    │   ├── intAret.c
    │   ├── cal1Elem.c
    │   ├── intElem.c
    │   ├── adwdw.c
    │   ├── main2b.c
    │   ├── fct_def_pb.c
    │   ├── impcalel.c
    │   ├── ww.c
    │   └── w.c
    │
    ├── 3_Assemblage
    │   ├── forfun.h
    │   ├── assmat.f
    │   ├── READMEtp3
    │   └── affsmd.f
    ├── 1_Maillage
    │   ├── lecfima.c
    │   ├── main1.c
    │   ├── maillage.h
    │   ├── etiqAr.c
    │   ├── modeSaisie2.c
    │   └── maillage.c
    ├── Donnees_1
    │   ├── ficOutput.txt
    │   ├── car3x3t_3
    │   ├── car1x1q_4
    │   ├── verif_lecfima.txt
    │   ├── car1x1t_4
    │   ├── car1x1t_1
    │   └── ficInput.txt
    ├── .README.md.swp
    ├── Utilitaire
    │   ├── freetab.c
    │   ├── allocvec.c
    │   ├── utilitaires.h
    │   ├── print.c
    │   ├── alloctab.c
    │   └── freevec.c
    └── Donnees_2
       ├── NUMREF.Test
       ├── Tests.3x3
       └── Tests.1x1
```
