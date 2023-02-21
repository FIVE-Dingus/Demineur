// Projet-demineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Ligne 10 + 1
#define Colonne 10 + 1



typedef struct Case
{
    int number; //chiffre présent dans la case 0 par défaut, -1 pour une bombe ou nb bombe autour 
    int statut; //statut de la case 0 si pas découvert, 1 si découvert et -1 pour le drapeau

}Case;

void viderBuffer()
{
	int c = 0;
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}



void play() {
    viderBuffer();
    int ligne = " ";
    printf("bonsoir michel tu veut jouer quel ligne ?");
    scanf_s ("%d", ligne);
    if (ligne <= Ligne - 1 && ligne > 0) {
        int colonne = " ";
        printf("Maintenant tu veut jouer quelles colonne");
        scanf_s("%d", colonne);
    }
    else {
        return play();
    };
};


int main()
{   // create grid
   
    Case odefault = { 0,0 };

    int nbBombe = round(((Ligne-1) * (Colonne-1))/6);
    printf("%d\n", nbBombe);

    int tableau[Ligne][Colonne];
    int i = 0;
    int y = 0;


    while (i < Ligne)
    {
        y = 0;
        while (y < Colonne)
        {
            if (i == 0 && y == 0)
            {
                printf("     ");
            }
            else if (y == Colonne - 1 && i == 0)
            {
                printf("%d", y);
                printf("\n");
            }
            else if (i > 9 && y == 0)
            {
                printf("%d  ", i);
            }
            else if (y > 9 && i == 0)
            {
                printf("%d ", y);
            }
            else if (i == 0)
            {
                printf("%d  ", y);
            }
            else if (y == 0)
            {
                printf("%d   ", i);
            }
            else
            {
                tableau[i][y] = odefault.number;
                printf(" ? ");
            };
            y++;
        };
        printf("\n");
        i++;
    }
    printf("\n");
    play();

    return 0;
};



// debut découvre tout ceux de number 0 et le premier ayant un nombre supérieur à 1

//apres découvre le number ou si bombe == perdu

//nb drapeau == nb bombe possibilité retirer drapeau

//quand créa bombe ajout +1 au number des 8 cases autour

// scanf pour savoir si poser drapeau/ découvrir une case
// scanf pour savoir la position




// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
