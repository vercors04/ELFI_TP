#!/bin/bash

gcc \
    ../Utilitaire/alloctab.c               \
    ../Utilitaire/freetab.c                \
    ../Utilitaire/allocvec.c               \
    ../Utilitaire/freevec.c                \
    \
    ../1_Maillage/lecfima.c                \
    \
    ../2b_ElementaireB/impcalel.c          \
    ../2b_ElementaireB/cal1Elem.c          \
    ../2b_ElementaireB/intElem.c           \
    ../2b_ElementaireB/fct_def_pb.c        \
    ../2b_ElementaireB/w.c                 \
    ../2b_ElementaireB/ww.c                \
    ../2b_ElementaireB/adwdw.c             \
    ../2a_ElementaireA/fct_elementairesa.c \
    ../2b_ElementaireB/intAret.c           \
    \
    ../3_Assemblage/assemblage.c           \
    ../3_Assemblage/*.o                    \
    \
    ../4_Construction_SL/dSMDaSMO.c        \
    ../4_Construction_SL/*.o               \
    \
    ../5_Resol_Post-Trait/main5Test.c      \
    ../5_Resol_Post-Trait/dSMOaPR.c        \
    ../5_Resol_Post-Trait/CalSol.c         \
    ../5_Resol_Post-Trait/ResolSyst.c      \
    ../5_Resol_Post-Trait/solex.c          \
    ../5_Resol_Post-Trait/dsmoapr.o        \
    ../5_Resol_Post-Trait/impmpr.o         \
    ../5_Resol_Post-Trait/ltlpr.o          \
    ../5_Resol_Post-Trait/rsprl.o          \
    ../5_Resol_Post-Trait/rspru.o          \
    ../5_Resol_Post-Trait/affsol.o         \
    \
    -Wall -Wextra \
    -o main5Test.exe \
    -lm \
    -lgfortran \
