// Projet-demineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define Ligne 10
#define Colonne 10



typedef struct Case
{
    int number; //chiffre présent dans la case 0 par défaut, -1 pour une bombe ou nb bombe autour 
    int statut; //statut de la case 0 si pas découvert, 1 si découvert et -1 pour le drapeau
    char symbol; // symbole montré sur la grille de jeu

}Case;


int getIndex1D(int i, int j)
{
    //permet de récupérer la valeur de l'adresse mémoire grâce à des coordonnées

    // j = colone
    // i = ligne

    return i * Ligne + j;

};

void returnIndex1D(int i, int place)
{
    //permet de récupérer les coordonnées grâce aux coordonnes
    int x = (place % i);
    
    int y = (place - x )/i;


    printf("\n %d, %d\n\n", x, y);

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
        viderBuffer();
        if (error == 0) {
            printf("Vous avez entrez une ou des lettres, entrez un nombre entre %d et %d! ", min, max);
        }
        else if (input >= min && input <= max) {
            return input;
        }
        else {
            printf("le nombre choisi n'est pas entre %d et %d! ", min, max);
        };
    };

};

char askResponseInput(char c1, char c2)
{
	while (1) {
		char input;
		int error = scanf_s("%c", &input, 1);
		if (error == 0) {
			viderBuffer();
			printf("Vous avez entrez un ou des chiffres, entrez %c et %c ! ", c1, c2);
		}
		else if (input == c1 || input == c2) {
			return input;
		}
		else {
			viderBuffer();
			printf("Vous devez repondre %c ou %c ! ", c1, c2);
		};
	};

};

void positionChoice(int * x, int * y) 
{
    printf("bonsoir michel tu veut jouer quel ligne ? ");
    *x = askNumberInput(1, Ligne);
    printf("Maintenant tu veut jouer quelles colonne ? ");
    *y = askNumberInput(1, Colonne);
};

void actionChoice()
{

};



void play(int ligne, int colonne, Case tableauJeu[Ligne * Colonne])
{
    display(tableauJeu);

            positionChoice(&ligne, &colonne);
            tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut = 1;
            tableauJeu[getIndex1D(ligne - 1, colonne - 1)].symbol = 3;
}

void initGrid(Case tableauJeu[Ligne * Colonne])
{
    Case odefault = { 0,0 ,'?' };

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
    printf("      ");
    for (int i = 0; i < Ligne; i++)
    {
        if (i >= 10)
        {
            printf("%d ", i + 1);
        }
        else
        {
            printf("%d  ", i + 1);
        };

    };
    printf("\n\n");


    for (int i = 0; i < Ligne; i++)
    {
        if (i >= 9)
        {
            printf(" %d  ", i + 1);
        }
        else
        {
            printf(" %d   ", i + 1);
        };

        for (int y = 0; y < Colonne; y++)
        {
            printf(" %c ", tableauJeu[getIndex1D(i, y)].symbol);
        };
        printf("\n");
    }
    printf("\n");
};


void placeBombe(int nbBombe, Case tableauJeu[Ligne * Colonne])
{
    //int tableauPBombe[Ligne * Colonne];

    Case oBombe = { -1,0 ,'*' };
    srand(time(NULL));

    while (nbBombe > 0)
    {

        int randomX = rand() % (Ligne);
        int randomY = rand() % (Colonne);

        if (tableauJeu[getIndex1D(randomX, randomY)].number == -1)
        {
            continue;
        };

        tableauJeu[getIndex1D(randomX, randomY)] = oBombe;

        for (int i = randomX - 1; i < 2; i++)
        {
            for (int j = randomY - 1; j < 2; j)
                if (i < 0 || j < 0 || i > Ligne - 1 || j > Colonne - 1)
                {
                    continue;
                }
                else
                {
                    tableauJeu[getIndex1D(i, j)].number++;
                    tableauJeu[getIndex1D(i, j)].symbol = tableauJeu[getIndex1D(i, j)].number + '0';
                };

            };
            nbBombe = nbBombe - 1;
    };
};

void placeFlag(int position, char flaged, Case tableauJeu[Ligne * Colonne], int * nbFlag)
{
    if (flaged == 'd')
    {
        if (*nbFlag > 0)
        {
            if (tableauJeu[position].symbol != 'F')
            {
                tableauJeu[position].symbol = 'F';
                *nbFlag--;
            }
            else
            {
                tableauJeu[position].symbol = tableauJeu[position].number + '0';
                *nbFlag++;
            };
        }
        else
        {
            tableauJeu[position].symbol = tableauJeu[position].number + '0';
            *nbFlag++;
        };
       
    };
};

int main()
{
    while (1) {
        int nbBombe = (int)round(((Ligne) * (Colonne)) / 6.0);
        int nbFlag = nbBombe;
        int ligne;
        int colonne;
        
        Case tableauJeu[Ligne * Colonne];
        initGrid(tableauJeu);
        placeBombe(nbBombe, tableauJeu);
        while (1)
        {
            play(tableauJeu, ligne, colonne);
        }
		printf("Souhaitez vous rejouez, si oui tapez o et si non tapez n");
		char reponse = askResponseInput('o', 'n');
		if (reponse == 'o') {
            return 1;
		}
		else
		{
			return 0;
		}
    };
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
