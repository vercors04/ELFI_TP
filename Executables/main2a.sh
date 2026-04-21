#!/bin/bash

gcc \
    ../Utilitaire/alloctab.c               \
    ../Utilitaire/allocvec.c               \
    ../Utilitaire/freetab.c                \
    ../Utilitaire/freevec.c                \
    ../Utilitaire/print.c                  \
    \
    ../2a_ElementaireA/fct_elementairesa.c \
    ../2a_ElementaireA/main2a.c            \
    \
    -o main2a.exe