gcc ../3_Assemblage/assemblage.c ../3_Assemblage/*.o \
    ../2b_ElementaireB/impcalel.c ../3_Assemblage/main3.c \
    ../Utilitaire/alloctab.c ../Utilitaire/freetab.c \
    ../2b_ElementaireB/cal1Elem.c ../Utilitaire/allocvec.c \
    ../Utilitaire/freevec.c ../1_Maillage/lecfima.c \
    ../2b_ElementaireB/intElem.c ../2b_ElementaireB/fct_def_pb.c \
    ../2b_ElementaireB/w.c ../2b_ElementaireB/ww.c ../2b_ElementaireB/adwdw.c \
    ../2a_ElementaireA/fct_elementairesa.c ../2b_ElementaireB/intAret.c\
    -o main3.exe \
    -lm \
    -lgfortran \
    -L ../3_Assemblage \
    -g

