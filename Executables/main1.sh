#!/bin/bash

gcc \
    ../Utilitaire/alloctab.c     \
    ../Utilitaire/freetab.c      \
    ../Utilitaire/allocvec.c     \
    ../Utilitaire/freevec.c      \
    \
    ../1_Maillage/lecfima.c      \
    ../1_Maillage/maillage.c     \
    ../1_Maillage/etiqAr.c       \
    ../1_Maillage/modeSaisie2.c  \
    ../1_Maillage/main1.c        \
    \
    -o main1.exe