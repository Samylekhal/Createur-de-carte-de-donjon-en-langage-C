#ifndef __projet_h_
#define __projet_h_

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int x; // coordonnée pour placer les salles
    int y;
    int largeur;         // largeur de la salle
    int hauteur;         // hauteur de la salle
    char grille[50][50]; // Taille maximale de la salle
} Murs;

// créer respectivement une salle et un étage
void initialiserSalle(Murs *salle, int largeur, int hauteur, char PosPortes[], int taillePosPortes);
void initialiserEtage(Murs *etage);

// placer les salles dans l'étage
void placeSalle(Murs *etage, Murs *salle, int X, int Y);
// supprimer une salle dans un étage donné
void supprSalle(Murs *etage, Murs *salle);
// déplacer les salles dans l'étage
void deplaceSalle(Murs *etage, Murs *salle, int nX, int nY);

// gérer les couloirs
// créer le chemin
void creerChemin(Murs *etage, int X, int Y, char path[], int taillePath);
// créer le couloir à partir du couloir
void placerCouloirs(Murs *etage);
// ce débarasse du chemin une fois le couloir créé
void supprChemin(Murs *etage);

void detectDoor(Murs *salle);
void closeopenDoor(Murs *salle, int X, int Y);
void placerElement(Murs *salle, int X, int Y, char element);
void placerElementRand(Murs *salle, int nb, char element);
void placerChampion(Murs *salle);

// afficher et sauvegarder le donjon
void afficherMurs(const Murs *salle);
void sauvegarderMurs(const Murs *salle, FILE *fichier);

#endif
