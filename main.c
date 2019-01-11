#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

int main () {

    //Déclarations
    char filenameImage[32];
    char filenameModele[32];
    char sdebug[2];
    int debug=0; //Si debug vaut 1, le debug mode est activé
    int resultatLecture;
    int resultat;
    int seuil;
    IMAGEUCHAR im;
    IMAGEUCHAR modele;
    IMAGEINT dist;
    IMAGEUCHAR imApresTraitement1;
    IMAGEUCHAR imApresTraitement2;

    //Renseignements demandés à l'utilisateur
    printf("\nRenseignez le nom du fichier modèle :\n");
    scanf("%s",filenameModele);
    printf("\nRenseignez le nom du fichier image :\n");
    scanf("%s",filenameImage);
    printf("\nRenseignez le seuil :\n");
    scanf("%d",&seuil);
    printf("\nSouhaitez-vous activer le debug Mode ? Y/N \n");
    scanf("%s",sdebug);
    if (!(strcmp("Y",sdebug))) {
        debug=1;
    }
    getchar();
    getchar();
    //Lecture de l'image
    resultatLecture=lectureImagePgmBinaire(filenameImage,&im);
    getchar();
    getchar();
    switch (resultatLecture) {
      case 1:
          printf("ERREUR Mauvais Magic Number");
          exit(EXIT_FAILURE);
          break;
      case 3:
          printf("ERREUR IntensitéMax supérieure à 255");
          exit(EXIT_FAILURE);
          break;
      case 4:
          printf("ERREUR Lecture Pixel Impossible");
          exit(EXIT_FAILURE);
          break;
      case 0:
          break;
      default:
          printf("Mauvaise valeur de retour");
          break;
    }

    //Lecture du modèle
    resultatLecture=lectureImagePgmBinaire(filenameModele,&modele);
    switch (resultatLecture) {
      case 1:
          printf("ERREUR Mauvais Magic Number");
          exit(EXIT_FAILURE);
          break;
      case 3:
          printf("ERREUR IntensitéMax supérieure à 255");
          exit(EXIT_FAILURE);
          break;
      case 4:
          printf("ERREUR Lecture Pixel Impossible");
          exit(EXIT_FAILURE);
          break;
      case 0:
          break;
      default:
          printf("Mauvaise valeur de retour");
          break;
    }
    ecritureImagePgmBinaire("debug3.pgm",modele);
    ecritureImagePgmBinaire("debug4.pgm",im);
    printf("TA MERE LA GROSSE PUTE");
    getchar();
    //Processing
    dist=templateMatching(im,modele);
    resetImageUChar(&im);
    int i;
    for (i=0;i<modele.nl;i++) {
    modele.val[0][i]=0;
  }
    printf("%d %d %p",modele.nl,modele.nc,im.val);
    getchar();
    //resetImageUChar(&modele);
    getchar();
    getchar();
    imApresTraitement1=minLocal(dist);
    resetImageInt(&dist);
    getchar();
    getchar();
    if (debug) {
        ecritureImagePgmBinaire("debug1.pgm",imApresTraitement1);
    }
    imApresTraitement2=seuilImageUChar(imApresTraitement1,seuil);
    resetImageUChar(&imApresTraitement1);
    if (debug) {
        ecritureImagePgmBinaire("debug2.pgm",imApresTraitement2);
    }
    getchar();
    getchar();
    resultat=valImageNonNulle(imApresTraitement2);
    //resetImageUChar(&imApresTraitement2);
    printf("\nDans cette image on retrouve %d fois le modèle ! \n\n",resultat);
    if (debug) {
      printf("Les resultats du debug sont contenues dans \"debug1.pgm\" et \"debug2.pgm\" :) \n");
    }

    return 0;
}
