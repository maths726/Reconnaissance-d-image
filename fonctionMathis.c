#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"


void resetImageUChar(IMAGEUCHAR* pim){ /*Libération de l'espace*/
  int i;
  printf("JUJUL1");
  getchar();
  for (i=0;i<(pim->nl);i++) {
    free(pim->val[i]);
    printf("\nJUJUL%d",i);
  }
  printf("JUJUL_ULTIMATE");
  getchar();
  free(pim->val);
  printf("JUJUL2");
  getchar();
  pim->val=NULL;
  pim->nc = 0; /*Mise à zero des nombres de lignes et colonnes*/
  pim->nl = 0;
}

void resetImageInt(IMAGEINT* pim){/*Libération de l'espace*/
  int i;
  for (i=0;i<(pim->nl);i++) free(pim->val[i]);
  free(pim->val);
  pim->nc = 0; /*Mise à zero des nombres de lignes et colonnes*/
  pim->nl = 0;
}
/*
int lectureImagePgmBinaire(char* fic,IMAGEUCHAR * im){
  FILE *f;
  char s[512];
  int max;
  f = fopen(fic, "rt");
  fscanf(f,"%s",s);
  if (strcmp(s,"P5") !=0){
    return 1;
  }
  fgets(sizeof(char),f);
  fscanf(f,"%d %d",&(im->nc),&(im->nl));
  fscanf(f,"%d", &max);
  if (max > 255){
    return 3;
  }
  int i;
  long pos = fgetpos(f);
  fclose(f);
  f = fopen(fic, "rb");
  fsetpos(f,pos);
  for (i=0 ; i < im->nl * im->nc ; i++){
    if (fread(im->val+i, sizeof(PIXEL),1,f) != 1) return 4;
  }
  fclose(f);
  return 0;
}
*/
int distance( IMAGEUCHAR im, IMAGEUCHAR patch, int is,int js){
  int i = 0,j=0;
  int d = 0;
  int I,T;
  for (i=0;i< patch.nl;i++) {
    for (j=0; j< patch.nc;j++){
      I = im.val[(is - (patch.nl)/2 + i + patch.nl)%patch.nl][(js - (patch.nc)/2 + j + patch.nc)%patch.nc];
      T = patch.val[i][j];
      d += (I-T)*(I-T);
    }
  }
  d = d/(patch.nl * patch.nc);
  printf("%d\n",d);
  return d;
}


int valImageNonNulle(IMAGEUCHAR im) {
  int i,j,p = 0;
  for (i=0;i< im.nl ;i++){
    for (j=0;j< im.nc ;j++){
      if (im.val[i][j] !=0) p++;
    }
  }
  return p ;
}

int ecritureImagePgmBinaire(char* fic, IMAGEUCHAR im) {
  FILE *f;
  int i;
  int j;
  f = fopen(fic,"wb");
  fprintf(f,"P5\n");
  fprintf(f,"%d %d\n", im.nc, im.nl);
  fprintf(f,"255\n");
  for (i=0;i<im.nl;i++) {
      for (j=0;j<im.nc;j++) {
          fwrite (&(im.val[i][j]), sizeof(unsigned char), 1, f);
      }
  }
  //fwrite (im.val, sizeof(unsigned char), (im.nl) * (im.nc), f);
  fclose (f);
  return 0;
}
