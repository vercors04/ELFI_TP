
void dSMOaPR2(int NbLign,int* AdPrCoefLiO,  int* NumColO, float* MatriceO,
             int* Profil, float* MatProf){
  Profil[0] = 1;
  MatProf[0] = MatriceO[0]; // Premier Coefficient diagonal

  for (int i=2;i<=NbLign;i++) {
    MatProf[i-1] = MatriceO[i-1]; // i-eme Coefficient diagonal
    int NbCoefLi = AdPrCoefLiO[i-1] - AdPrCoefLiO[i-2];
    //int NbCoefLi = AdPrCoefLiO[i-2]-AdPrCoefLiO[i-1]; // Nombre de Coefficients
    int TailleLiP = 0;
    if (NbCoefLi > 0) {// Si il y a au moins 1 coefficient pour la ligne i
 
      for (int j=0; j<NbCoefLi; j++) {
        int IndiceCoefLowMat = AdPrCoefLiO[i-2]-1 + j;
        int IndiceCoefLowMatProf = Profil[i-2]-1 + NumColO[IndiceCoefLowMat] - NumColO[AdPrCoefLiO[i-2]-1];;

        (MatProf+NbLign)[IndiceCoefLowMatProf] = (MatriceO+NbLign)[IndiceCoefLowMat];
      }

      // Nombre d'elements d'une ligne Profil
      // Num de ligne - Num de colonne du premier coefficient de la ligne i
      TailleLiP = i - NumColO[AdPrCoefLiO[i-2]-1];
    }
 
    Profil[i-1] = Profil[i-2] + TailleLiP;
  }

}

int dSMOaLongPR2(int NbLign, int* AdPrCoefLiO, int* NumColO, float* MatriceO){
  // DEMANDER INTERET DE MatriceO

  int longueur = NbLign + 1; // Elements diagonaux + Element fictif 

  for (int i=1;i<NbLign;i++) {
    // Test si : AdPrCoefLiO(i)-AdPrCoefLiO(i+1) != 0
    // Car si = 0, Alors la ligne i n'a pas de coefficient non logiquement nul
    // Operation : NumLigneMatrice - NumColPremierCoefNonNul
    if (AdPrCoefLiO[i] - AdPrCoefLiO[i-1]) longueur += i+1 - NumColO[AdPrCoefLiO[i-1]-1];
  }
  return longueur;
}
