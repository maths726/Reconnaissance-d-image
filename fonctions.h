typedef unsigned char  PIXEL;
// Definition du type IMAGEUCHAR pour des images 8 bits d’octets
typedef struct {
int nl,nc;
PIXEL** val;
} IMAGEUCHAR;
// Definition du type IMAGEUCHAR pour des images 32 bits d’entiers
typedef struct {
int nl,nc;
int** val;
} IMAGEINT;

//Comparaison avec les pixels voisins
int compVois(IMAGEINT im,int i,int j,int decalageI,int decalageJ);
// Allocation de l’espace memoire pour les int
int** alloueMemoireImageInt(int nl, int nc);
// Allocation de l’espace memoire pour les pixels
PIXEL** alloueMemoireImageChar(int nl, int nc);
// Creation d’une image de d’unsigned char avec allocation dynamique de l’espace des pixels
IMAGEUCHAR creationImageUChar(int nl, int nc) ;
// Reset l’image avec liberation de l’espace memoire des pixels, mise a 0 des nombres de lignes et de colonnes
void resetImageUChar(IMAGEUCHAR* pim);
// Creation avec allocation d’une image de Int avec allocation dynamique de l’espace des entiers
IMAGEINT creationImageInt(int nl, int nc) ;
// Reset l’image avec liberation de l’espace memoire des entiers, mise a 0 des nombres de lignes et de colonnes
void resetImageInt(IMAGEINT* pim);
// Lecture d’une image dans un fichier
int lectureImagePgmBinaire(char* fic,IMAGEUCHAR * im) ;
// Distance d 2 entre le modele et l’image au pixel de coordonees is, js
int distance( IMAGEUCHAR im, IMAGEUCHAR patch, int is,int js);
// Calcul de la distance au modele pour tous les points de l’image.
IMAGEINT templateMatching(IMAGEUCHAR im, IMAGEUCHAR modele) ;
// Determination des minima locaux
IMAGEUCHAR minLocal(IMAGEINT im) ;
// Seuillage des valeurs positives inferieures a un seuil
IMAGEUCHAR seuilImageUChar(IMAGEUCHAR im, int seuil) ;
// Compter le nombre de valeurs non nulles
int valImageNonNulle(IMAGEUCHAR im) ;
// Si besoin, Ecriture d’une image dans un fichier
int ecritureImagePgmBinaire(char* fic, IMAGEUCHAR im) ;
