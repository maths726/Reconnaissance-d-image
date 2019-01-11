#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#include "fonctions.h"

//______________________________________________________
//     Fonctions du Projet 1A 2019
//
//______________________________________________________


// Allocation de l’espace memoire pour les pixels
PIXEL** alloueMemoireImageChar(int nl, int nc) {

    //Déclarations
    PIXEL** tabAdrLin=NULL;
    PIXEL** adrLin= NULL;

    //Allocation du tableau ligne
    tabAdrLin=calloc(nl,sizeof(PIXEL*));

    //Vérification
    if (tabAdrLin==NULL) {
      exit(EXIT_FAILURE);
    }

    //Allocation de chacun des tableau de ligne
    for (adrLin=tabAdrLin;adrLin<tabAdrLin+nl;adrLin++) {
        *adrLin=calloc(nc,sizeof(PIXEL));
        // Vérification
        if (*adrLin==NULL) {
          exit(EXIT_FAILURE);
        }
    }
    return tabAdrLin;
}


// Allocation de l’espace memoire pour les int
int** alloueMemoireImageInt(int nl, int nc) {

    //Déclarations
    int** tabAdrLin=NULL;
    int** adrLin=NULL;

    //Allocation du tableau ligne
    tabAdrLin=calloc(nl,sizeof(int*));

    //Vérification
    if (tabAdrLin==NULL) {
      exit(EXIT_FAILURE);
    }

    //Allocation de chacun des tableau de ligne
    for (adrLin=tabAdrLin;adrLin<tabAdrLin+nl;adrLin++) {
        *adrLin=calloc(nc,sizeof(int));
        // Vérification
        if (*adrLin==NULL) {
          exit(EXIT_FAILURE);
        }
    }

    return tabAdrLin;
}


// Creation d’une image de d’unsigned char avec allocation dynamique de l’espace des pixels
IMAGEUCHAR creationImageUChar(int nl, int nc) {

    //Déclarations
    PIXEL** val=NULL;
    IMAGEUCHAR image;

    //allocation
    val=alloueMemoireImageChar(nl,nc);

    image.nl=nl;
    image.nc=nc;
    image.val=val;

    return image;

}


// Creation avec allocation d’une image de Int avec allocation dynamique de l’espace des entiers
IMAGEINT creationImageInt(int nl, int nc) {

    //Déclarations
    int** val=NULL;
    IMAGEINT image;

    //allocation
    val=alloueMemoireImageInt(nl,nc);

    image.nl=nl;
    image.nc=nc;
    image.val=val;

    return image;
}


// Calcul de la distance au modele pour tous les points de l’image.
IMAGEINT templateMatching(IMAGEUCHAR im, IMAGEUCHAR modele) {

    //Déclarations
    IMAGEINT imdistance = creationImageInt(im.nl,im.nc);
    int i,j;

    //Parcours de l'image, calcul des distances, et écriture dans imdistance
    for (i=0;i<im.nl;i++) {
        for (j=0;j<im.nc;j++) {
            imdistance.val[i][j]=distance(im,modele,i,j);
        }
    }

    return imdistance;

}


// Lecture d’une image dans un fichier
int lectureImagePgmBinaire(char* fic,IMAGEUCHAR * im) {

    //Déclarations
    FILE *f;
    char magicNumber[3];
    char tmp[512];
    int nbLigne,nbColonne;
    int intensiteMax;
    int i,j;

    //Ouverture
    f=fopen(fic,"rb");

    //Traitement Magic Number
    fscanf(f,"%s",magicNumber);
    if (strcmp(magicNumber,"P5")) {
        return 1;
    }
    getchar();
    //Traitement commentaire
    fgets(tmp,512,f);
    fgets(tmp,512,f);
    getchar();
    //Traitement Taille et intensiteMax
    fscanf(f,"%d %d",&nbColonne,&nbLigne);
    fscanf(f,"%d", &intensiteMax);
    if (intensiteMax > 255) {
      return 3;
    }
    getchar();
    printf("PD");
    //Allocation tableau pour image
    *im=creationImageUChar(nbLigne,nbColonne);

    //Lecture Pixels
    for (i=0;i<nbLigne;i++) {
        for (j=0;j<nbColonne;j++) {
              fread(&((im->val)[i][j]), sizeof(PIXEL),1,f);
        }
    }
    getchar();

    //Fin
    fclose(f);
    return 0;
}


//Fonction pour faciliter la vie et trouver le minimum local plus simplement
int compVois(IMAGEINT im,int i,int j,int decalageI,int decalageJ) {
  return (im.val[i][j]<im.val[(i+decalageI+im.nl)%im.nl][(j+decalageJ+im.nc)%im.nc]);
}


// Determination des minima locaux
IMAGEUCHAR minLocal(IMAGEINT im) {

    //Déclarations
    IMAGEUCHAR newIm = creationImageUChar(im.nl,im.nc);
    int i,j;

    //Parcours de l'image, recherche de minimum locaux (On symétrise l'image)
    for (i=0;i<im.nl;i++) {
        for (j=0;j<im.nc;j++) {
            if ((compVois(im,i,j,1,0))&&(compVois(im,i,j,0,1))&&(compVois(im,i,j,-1,0))&&(compVois(im,i,j,0,-1))&&(compVois(im,i,j,1,1))&&(compVois(im,i,j,-1,-1))&&(compVois(im,i,j,1,-1))&&(compVois(im,i,j,-1,1))) {
                newIm.val[i][j]=(sqrt((double)(im.val[i][j])));
                printf("%hhu\n",(newIm.val[i][j]));
            }
            else {
                newIm.val[i][j]=UCHAR_MAX;
            }
        }
    }
    return newIm;
}


// Seuillage des valeurs positives inferieures a un seuil
IMAGEUCHAR seuilImageUChar(IMAGEUCHAR im, int seuil) {

    //Déclarations
    int i,j;

    //Traitement
    for (i=0;i<im.nl;i++) {
        for (j=0;j<im.nc;j++) {
            if (im.val[i][j]<seuil) {
                im.val[i][j]=255;
            }
            else {
                im.val[i][j]=0;
            }
        }
    }
    return im;
}
