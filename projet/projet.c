#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "projet.h"

// GESTION DES SALLES ET ETAGES

// Défini les paramètre de la structure créer les salles
void initialiserSalle(Murs *salle, int hauteur, int largeur, char PosPortes[], int taillePosPortes)
{
    salle->largeur = largeur;
    salle->hauteur = hauteur;

    // Initialise la salle avec des espaces vides
    for (int i = 0; i < salle->largeur; i++)
    {
        for (int j = 0; j < salle->hauteur; j++)
        {
            salle->grille[i][j] = ' '; // Espace vide
        }
    }

    // Placer les murs autour du contour
    for (int i = 0; i < salle->largeur; i++)
    {
        salle->grille[i][0] = '#';                  // Mur de gauche
        salle->grille[i][salle->hauteur - 1] = '#'; // Mur de droite
    }
    for (int j = 0; j < salle->hauteur; j++)
    {
        salle->grille[0][j] = '#';                  // Mur du haut
        salle->grille[salle->largeur - 1][j] = '#'; // Mur du bas
    }

    // Placer les portes au centre de chaque côté
    int demiLargeur = salle->largeur / 2;
    int demiHauteur = salle->hauteur / 2;

    for (int k = 0; k < taillePosPortes; k++)
    {
        switch (PosPortes[k])
        {
        case 'N':
            salle->grille[0][demiHauteur] = 'O'; // porte du haut
            break;
        case 'E':
            salle->grille[demiLargeur][salle->hauteur - 1] = 'O'; // porte de droite
            break;
        case 'S':
            salle->grille[salle->largeur - 1][demiHauteur] = 'O'; // porte du bas
            break;
        case 'O':
            salle->grille[demiLargeur][0] = 'O'; // porte de gauche
            break;
        default:
            printf("\nERREUR!: élément non reconnu\n"); // Stop la fonction si un mauvais caractère se trouve dans la liste
            return;
            break;
        }
    }
}
// Similaire à initialiserSalle excepté que les valeur de base sont déja à l'intérieur de la fonction (portes, hauteur et largeur)
void initialiserEtage(Murs *etage)
{
    etage->largeur = 50;
    etage->hauteur = 50;

    // Initialiser l'étage avec des espaces vides
    for (int i = 0; i < etage->largeur; i++)
    {
        for (int j = 0; j < etage->hauteur; j++)
        {
            etage->grille[i][j] = ' '; // Espace vide
        }
    }

    // Placer les murs autour du contour
    for (int i = 0; i < etage->largeur; i++)
    {
        etage->grille[i][0] = '#';                  // Mur de droite
        etage->grille[i][etage->hauteur - 1] = '#'; // Mur de gauche
    }
    for (int j = 0; j < etage->hauteur; j++)
    {
        etage->grille[0][j] = '#';                  // Mur du haut
        etage->grille[etage->largeur - 1][j] = '#'; // Mur du bas
    }

    // Placer une porte en haut
    int porteX = etage->largeur / 2;
    int porteY = 0;
    etage->grille[porteY][porteX] = 'E'; // Emplacement de la porte d'entrée

    // Placer une porte en bas
    porteY = etage->hauteur - 1;
    etage->grille[porteY][porteX] = 'S'; // Emplacement de la porte de sortie
}
// Placer une salle dans le donjon
void placeSalle(Murs *etage, Murs *salle, int X, int Y)
{
    // Choisir les coordonnées de la salle dans l'étage

    etage->x = X;
    etage->y = Y;

    // Initiasliser la salle dans l'étage en s'aidant des coordonnées
    for (int i = 0; i < salle->largeur; i++)
    {
        for (int j = 0; j < salle->hauteur; j++)
        {
            etage->grille[Y + i][X + j] = salle->grille[i][j];
        }
    }
}
// Modifie le placement d'une salle dans l'étage en incrémentant X et Y avec les valeur d'entrée
void deplaceSalle(Murs *etage, Murs *salle, int nX, int nY)
{
    supprSalle(etage, salle);
    salle->x += nX;
    salle->y += nY;
    placeSalle(etage, salle, salle->x, salle->y);
}
// remplace la partie de l'étage ou se trouvait la salle par des cases vides
void supprSalle(Murs *etage, Murs *salle)
{
    // Choisir les coordonnées de la salle dans l'étage

    int X = etage->x;
    int Y = etage->y;

    // Copier la grille de la salle dans l'étage aux coordonnées choisies
    for (int i = 0; i < salle->largeur; i++)
    {
        for (int j = 0; j < salle->hauteur; j++)
        {
            etage->grille[X + i][Y + j] = ' ';
        }
    }
}

// GESTION DES COULOIRS

// crée un chemin d'astérisque dans le donjon grâce à une chaîne de caractère indiquant les directions à prendre. Le programme à pour point de départ une porte du donjon
void creerChemin(Murs *etage, int X, int Y, char path[], int taillePath)
{
    int Xn = X;
    X = Y;
    Y = Xn;

    // vérifie que le programme commence bien sur une porte, sinon le programme s'arrête et met un message d'erreur
    // le for parcours chaque parties de la chaîne de caractère
    for (int k = 0; k < taillePath; k++)
    {
        // Ici le programme va analiser la case qu'elle doit suivre,
        // si elle est valide l'astérisque est placé là et les coordonnées de bases change pour
        // passer à la nouvelle valeur de la chaîne. Où si l'astérisque se dirige vers un murs ou une porte, le programme s'arrête
        switch (path[k])
        {
        case 'O':
            if (Y > 0 && etage->grille[X][Y - 1] == ' ' || etage->grille[X][Y - 1] == '*')
            {
                etage->grille[X][Y - 1] = '*';
                Y--;
            }
            else if (Y > 0 && (etage->grille[X][Y - 1] == 'O' || etage->grille[X][Y - 1] == 'F' || etage->grille[X][Y - 1] == 'S' || etage->grille[X][Y - 1] == 'E'))
            {
                printf("\nLe couloir a atteint une porte, le programme s'est donc arrêté");
                return;
            }
            else
            {
                printf("\nERREUR!: Une direction a heurté quelque chose ");
                return;
            }
            break;
        case 'S':
            if (X < etage->largeur - 1 && etage->grille[X + 1][Y] == ' ' || etage->grille[X + 1][Y] == '*')
            {
                etage->grille[X + 1][Y] = '*';
                X++;
            }
            else if (X < etage->largeur - 1 && (etage->grille[X + 1][Y] == 'O' || etage->grille[X + 1][Y] == 'F' || etage->grille[X + 1][Y] == 'S' || etage->grille[X + 1][Y] == 'E'))
            {
                printf("\nLe couloir a atteint une porte, le programme s'est donc arrêté");
                return;
            }
            else
            {
                printf("\nERREUR!: Une direction a heurté quelque chose ");
                return;
            }
            break;
        case 'E':
            if (Y < etage->hauteur - 1 && etage->grille[X][Y + 1] == ' ' || etage->grille[X][Y + 1] == '*')
            {
                etage->grille[X][Y + 1] = '*';
                Y++;
            }
            else if (Y < etage->hauteur - 1 && (etage->grille[X][Y + 1] == 'O' || etage->grille[X][Y + 1] == 'F' || etage->grille[X][Y + 1] == 'S' || etage->grille[X][Y + 1] == 'E'))
            {
                printf("\nLe couloir a atteint une porte, le programme s'est donc arrêté");
                return;
            }
            else
            {
                printf("\nERREUR!: Une direction a heurté quelque chose ");
                return;
            }
            break;
        case 'N':
            if (X > 0 && etage->grille[X - 1][Y] == ' ' || etage->grille[X - 1][Y] == '*')
            {
                etage->grille[X - 1][Y] = '*';
                X--;
            }
            else if (X > 0 && (etage->grille[X - 1][Y] == 'O' || etage->grille[X - 1][Y] == 'F' || etage->grille[X - 1][Y] == 'S' || etage->grille[X - 1][Y] == 'E'))
            {
                printf("\nLe couloir a atteint une porte, le programme s'est donc arrêté");
                return;
            }
            else
            {
                printf("\nERREUR!: Une direction a heurté quelque chose ");
                return;
            }
            break;
        default:
            printf("\nERREUR!: élément non reconnu\n");
            break;
        }
    }
}
// Ce programme va placer un # autour de chaque * à condition que les cases autour soit vident
void placerCouloirs(Murs *etage)
{
    for (int i = 0; i < etage->largeur; i++)
    {
        for (int j = 0; j < etage->hauteur; j++)
        {
            if (etage->grille[i][j] == '*')
            {
                // Vérifier les cases voisines et placer '#' si elles sont vides
                // horizontales et vertcales
                if (etage->grille[i - 1][j] == ' ')
                {
                    etage->grille[i - 1][j] = '#';
                }
                if (etage->grille[i + 1][j] == ' ')
                {
                    etage->grille[i + 1][j] = '#';
                }
                if (etage->grille[i][j - 1] == ' ')
                {
                    etage->grille[i][j - 1] = '#';
                }
                if (etage->grille[i][j + 1] == ' ')
                {
                    etage->grille[i][j + 1] = '#';
                }
                // diagonales
                if (etage->grille[i + 1][j + 1] == ' ')
                {
                    etage->grille[i + 1][j + 1] = '#';
                }
                if (etage->grille[i + 1][j - 1] == ' ')
                {
                    etage->grille[i + 1][j - 1] = '#';
                }
                if (etage->grille[i - 1][j + 1] == ' ')
                {
                    etage->grille[i - 1][j + 1] = '#';
                }
                if (etage->grille[i - 1][j - 1] == ' ')
                {
                    etage->grille[i - 1][j - 1] = '#';
                }
            }
        }
    }
}
// cet fonction va supprimer chaque * ne laissant ainsi que les couloirs
void supprChemin(Murs *etage)
{
    for (int i = 0; i < etage->largeur; i++)
    {
        for (int j = 0; j < etage->hauteur; j++)
        {
            if (etage->grille[i][j] == '*')
            {
                etage->grille[i][j] = ' ';
            }
        }
    }
}

// DETECTION D'ELEMENT
// Ce programme va parcourir l'étage pour print les coordonnés de chaque portes s'y trouvant.
// Cette fonction sert d'outils de rensignement pour pouvoir utiliser plus facilement d'autres fonctions
void detectDoor(Murs *salle)
{
    for (int i = 0; i < salle->largeur; i++)
    {
        for (int j = 0; j < salle->hauteur; j++)
        {
            if (salle->grille[i][j] == 'O')
            {
                printf("O : X = %d ; Y = %d", j, i);
                printf("\n");
            }
            if (salle->grille[i][j] == 'F')
            {
                printf("F : X = %d ; Y = %d", j, i);
                printf("\n");
            };
            if (salle->grille[i][j] == 'E')
            {
                printf("E : X = %d ; Y = %d", j, i);
                printf("\n");
            };
            if (salle->grille[i][j] == 'S')
            {
                printf("S : X = %d ; Y = %d", j, i);
                printf("\n");
            };
        };
    }
}

// MODIFIER ET AJOUTER DES ELEMENTS

// Détecte une porte et l'ouvre si elle est fermer ou la ferme si elle est ouverte
void closeopenDoor(Murs *salle, int X, int Y)
{
    if (salle->grille[X][Y] = 'O')
    {
        salle->grille[X][Y] = 'F';
        printf("\nporte fermée\n");
    }
    else if (salle->grille[X][Y] = 'F')
    {
        salle->grille[X][Y] = 'O';
        printf("\nporte ouverte\n");
    }
    else
    {
        printf("\nERREUR!: Il n'y a aucune porte à cette endroit !\n");
    }
}

// Permet de placer un élement dans une salle si avec les coordonnées, tel un monstre, un coffre, une dépouille,ect...
void placerElement(Murs *salle, int X, int Y, char element)
{
    if (salle->grille[X][Y] == ' ')
    {
        salle->grille[X][Y] = element;
    }
    else
    {
        printf("\n Cette case est déja prise");
    }
};
// Place de manière aléatoire des élements dans une salle en indiquant le nombre d'élement
void placerElementRand(Murs *salle, int nb, char element)
{
    for (int i = 0; i < nb; i++)
    {
        int posX, posY;
        do
        {
            posX = rand() % (salle->largeur - 2) + 1; // permet de placer à l'intérieur des murs
            posY = rand() % (salle->hauteur - 2) + 1;
        } while (salle->grille[posX][posY] != ' '); // Vérifie que l'emplacement est vide

        salle->grille[posX][posY] = element; // Emplacement de l'élèment
    }
}
// place un champion dans une salle. Il prend trois cases et se situe toujours au milieu d'une salle (c'est un boss)
void placerChampion(Murs *salle)
{
    int X = salle->largeur / 2;
    int Y = salle->hauteur / 2;

    salle->grille[X][Y] = 'W';
    salle->grille[X][Y - 1] = 'U';
    salle->grille[X][Y + 1] = 'U';
};

// AFFICHER ET SAUVEGARDER

// affiche le donjon dans le terminal
void afficherMurs(const Murs *salle)
{
    for (int i = 0; i < salle->largeur; i++)
    {
        for (int j = 0; j < salle->hauteur; j++)
        {
            printf("%c ", salle->grille[i][j]);
        }
        printf("\n");
    }
}
// affiche le donjon dans le fichier txt
void sauvegarderMurs(const Murs *salle, FILE *fichier)
{
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    for (int i = 0; i < salle->largeur; i++)
    {
        for (int j = 0; j < salle->hauteur; j++)
        {
            fputc(salle->grille[i][j], fichier); // implement l'élèment de la grille dans le fichier
        }
        fputc('\n', fichier); // Passer à la ligne suivante dans le fichier
    }

    fclose(fichier); // Fermer le fichier
}
