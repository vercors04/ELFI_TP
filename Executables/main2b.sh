#!/bin/bash

gcc \
    ../Utilitaire/alloctab.c               \
    ../Utilitaire/allocvec.c               \
    ../Utilitaire/freetab.c                \
    ../Utilitaire/freevec.c                \
    \
    ../1_Maillage/lecfima.c                \
    \
    ../2a_ElementaireA/fct_elementairesa.c \
    \
    ../2b_ElementaireB/adwdw.c             \
    ../2b_ElementaireB/cal1Elem.c          \
    ../2b_ElementaireB/fct_def_pb.c        \
    ../2b_ElementaireB/impcalel.c          \
    ../2b_ElementaireB/intAret.c           \
    ../2b_ElementaireB/intElem.c           \
    ../2b_ElementaireB/w.c                 \
    ../2b_ElementaireB/ww.c                \
    ../2b_ElementaireB/main2b.c            \
    \
    -o main2b.exe \
    -lm