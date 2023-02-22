// Projet-demineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>

#define Ligne 10 
#define Colonne 10 



typedef struct Case
{
    int number; //chiffre présent dans la case 0 par défaut, -1 pour une bombe ou nb bombe autour 
    int statut; //statut de la case 0 si pas découvert, 1 si découvert et -1 pour le drapeau

}Case;

int getIndex1D(int i, int j)
{
    //permet de récupérer l'indice d'un tableau à 2 dimensions dans un tableau à 1 dimension

    // j = colone
    // i = ligne

    return i * Ligne + j;

};

void viderBuffer()
{
	int c = 0;
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}

int askNumberInput(int min, int max)
{
    while (1) {
        int input;
        int error = scanf_s("%d", &input);
        printf("%d", error);


    };
};


int play() {
    
    
    printf("bonsoir michel tu veut jouer quel ligne ? ");
    int ligne = askNumberInput(1, Ligne);
        printf("Maintenant tu veut jouer quelles colonne ? ");
        int colonne = askNumberInput(1, Colonne);
        return ligne,colonne;
};

void initGrid(Case tableauJeu[Ligne * Colonne])
{
    Case odefault = { 0,0 };

    for (int i = 0; i < Ligne; i++)
    {
        for (int y = 0; y < Colonne; y++)
        {
            tableauJeu[getIndex1D(i, y)] = odefault;
        };
    };
};

void display(Case tableauJeu[Ligne * Colonne])
{

    for (int i = 0; i < Ligne + 1; i++)
    {
        for (int y = 0; y < Colonne + 1; y++)
        {
            if (i == 0 && y == 0)
            {
                printf("     ");
            }
            else if (y == Colonne  && i == 0)
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
                printf(" %d ", tableauJeu[getIndex1D(i, y)]);
            };
        };
        printf("\n");
    }
    printf("\n");
};


void placeBombe (int nbBombe, Case tableauJeu[Ligne * Colonne])
{
    //int tableauPBombe[Ligne * Colonne];

    Case oBombe = { -1,0 };

    while (nbBombe > 0)
    {
        int random = rand() % ( Ligne * Colonne );
        if (tableauJeu[random].number != -1)
        {
            tableauJeu[random] = oBombe ;
            nbBombe = nbBombe - 1;
        };

    };
};


int main()
{
    int nbBombe = (int) round(((Ligne) * (Colonne)) / 6.0);
    int nbFlag = nbBombe;
    Case tableauJeu[Ligne * Colonne];
	while (1) 
    {

    initGrid(tableauJeu);

    placeBombe(nbBombe, tableauJeu);

    display(tableauJeu);

    
    play();
    }

    return 0;
};


// quand choix placement enlever 1 à i et j


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
