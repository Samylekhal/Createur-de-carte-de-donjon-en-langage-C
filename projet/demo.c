#include <stdio.h>
#include <stdlib.h>
#include "projet.h"

void DJC()
{

    srand(time(NULL)); // Génère de l'aléatoire en fonction du temps

    // Ses varibles contiennent toutes les possibilités de placement possible
    char NESO[] = {'N', 'E', 'S', 'O'};
    char ESON[] = {'E', 'S', 'O', 'N'};
    char SONE[] = {'S', 'O', 'N', 'E'};
    char ONES[] = {'O', 'N', 'E', 'S'};
    char EONS[] = {'E', 'O', 'N', 'S'};
    char SNOE[] = {'S', 'N', 'O', 'E'};

    Murs etage;

    initialiserEtage(&etage);

    Murs salle;
    initialiserSalle(&salle, 21, 7, SONE, 3);
    placerElementRand(&salle, 3, 'M');
    placeSalle(&etage, &salle, 15, 1);
    Murs salle1;
    initialiserSalle(&salle1, 17, 9, NESO, 4);
    closeopenDoor(&salle1, 8, 8);
    closeopenDoor(&salle1, 4, 16);
    placerElement(&salle1, salle1.largeur / 2, salle1.hauteur / 2, 'A');
    placerElementRand(&salle1, 4, 'M');
    placeSalle(&etage, &salle1, 17, 12);
    Murs salle2;
    initialiserSalle(&salle2, 7, 14, NESO, 3);
    placerElement(&salle2, 1, 1, 'P');
    placerElement(&salle2, 3, 1, 'P');
    placerElement(&salle2, 5, 1, 'P');
    placerElement(&salle2, 7, 1, 'P');
    placerElement(&salle2, 9, 1, 'P');
    placerElement(&salle2, 11, 1, 'P');
    placerElement(&salle2, 1, 5, 'P');
    placerElement(&salle2, 3, 5, 'P');
    placerElement(&salle2, 5, 5, 'P');
    placerElement(&salle2, 7, 5, 'P');
    placerElement(&salle2, 9, 5, 'P');
    placerElement(&salle2, 11, 5, 'P');
    placerElement(&salle2, 2, 3, 'P');
    placerElement(&salle2, 4, 3, 'P');
    placerElement(&salle2, 6, 3, 'P');
    placerElement(&salle2, 8, 3, 'P');
    placerElement(&salle2, 10, 3, 'P');
    placerElement(&salle2, 12, 3, 'P');
    placeSalle(&etage, &salle2, 3, 9);
    Murs salle3;
    initialiserSalle(&salle3, 23, 7, NESO, 3);
    placerElementRand(&salle3, 7, 'M');
    placerElement(&salle3, 5, 11, 'P');
    placeSalle(&etage, &salle3, 17, 25);
    Murs salle4;
    initialiserSalle(&salle4, 3, 3, NESO, 1);
    placerElementRand(&salle4, 1, 'C');
    placeSalle(&etage, &salle4, 5, 23);
    Murs salle5;
    initialiserSalle(&salle5, 16, 5, SONE, 1);
    placerElementRand(&salle5, 5, 'D');
    placerElementRand(&salle5, 4, 'C');
    placeSalle(&etage, &salle5, 33, 8);
    Murs salle6;
    initialiserSalle(&salle6, 9, 5, SONE, 3);
    placeSalle(&etage, &salle6, 40, 33);
    Murs salle7;
    initialiserSalle(&salle7, 20, 8, SONE, 3);
    placerChampion(&salle7);
    placerElement(&salle7, 5, 5, 'M');
    placerElement(&salle7, 5, 15, 'M');
    placerElement(&salle7, 3, 5, 'M');
    placerElement(&salle7, 3, 15, 'M');
    closeopenDoor(&salle7, 4, 0);
    closeopenDoor(&salle7, 7, 10);
    placeSalle(&etage, &salle7, 15, 40);

    initialiserSalle(&salle4, 3, 3, ESON, 1);
    placerElementRand(&salle4, 1, 'C');
    placeSalle(&etage, &salle4, 12, 43);

    // deplaceSalle(&etage, &salle2, 10, 0);

    // gestion des portes

    // closeopenDoor(&etage, 11, 3);

    detectDoor(&etage);
    // création des chemins de couloirs

    char C[] = {'N', 'N', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'N'};
    int tailleC = sizeof(C);
    creerChemin(&etage, 25, 40, C, tailleC);

    char C1[] = {'S', 'E', 'S', 'E', 'S', 'E', 'S', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'};
    int tailleC1 = sizeof(C1);
    creerChemin(&etage, 28, 31, C1, tailleC1);

    creerChemin(&etage, 25, 47, C1, 1);

    char C2[] = {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'S', 'S', 'S', 'S', 'S', 'S'};
    int TC2 = sizeof(C2);
    creerChemin(&etage, 15, 4, C2, TC2);
    creerChemin(&etage, 17, 16, C2, TC2);

    char C3[] = {'S', 'S', 'S', 'S', 'E', 'E', 'E'};
    int TC3 = sizeof(C3);
    creerChemin(&etage, 25, 7, C3, 4);

    creerChemin(&etage, 25, 20, C3, TC3);

    char C4[] = {'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'};
    int TC4 = sizeof(C4);
    creerChemin(&etage, 41, 12, C4, TC4);

    char C5[] = {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'};
    int TC5 = sizeof(C5);
    creerChemin(&etage, 33, 16, C5, TC5);

    char C6[] = {'E', 'E', 'E', 'E', 'E', 'S', 'S', 'S', 'S'};
    int TC6 = sizeof(C6);
    creerChemin(&etage, 39, 28, C6, TC6);

    // création des couloir
    placerCouloirs(&etage);
    supprChemin(&etage);

    // créer des fichier d'enregistrement et les nommer
    FILE *fichier = fopen("Projet.txt", "w");
    // sauvegarder et afficher dans le txt
    sauvegarderMurs(&etage, fichier);
}

int main()
{
    DJC();
    return 0;
}
