int min(int a, int b) { return (a > b) ? b : a; }
int max(int a, int b) { return (a < b) ? b : a; }

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include < limits.h >

int askNumberInput(int min, int max);

int Ligne = 10;
int Colonne = 10;

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

    return i * Colonne + j;

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
		viderBuffer();
		if (error == 0){
			printf("Vous avez entrez un ou des chiffres, entrez %c et %c ! ", c1, c2);
		}
		else if (input == c1 || input == c2) {
			return input;
		}
		else {
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


void initGrid(Case* tableauJeu)
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

void reveal(Case* tableauJeu, int x, int y)
{
    if (tableauJeu[getIndex1D(x, y)].statut == 0)
    {
        tableauJeu[getIndex1D(x, y)].statut = 1;
    };
};

void looseReveal(Case* tableauReveal)
{
    printf("      ");
    for (int i = 0; i < Colonne; i++)
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
            if (tableauReveal[getIndex1D(i, y)].statut == 0 && tableauReveal[getIndex1D(i, y)].symbol == '?')
            {
                tableauReveal[getIndex1D(i, y)].statut = 1;
                tableauReveal[getIndex1D(i, y)].symbol = '0';
            };
        
            printf(" %c ", tableauReveal[getIndex1D(i, y)].symbol);
        };
        printf("\n");
    }
    printf("\n");
};

void revealNearby(int  x, int  y, Case * tableauJeu, int* compteCasePlayed)
{
    if (tableauJeu[getIndex1D(x, y)].number != -1)
    {
        tableauJeu[getIndex1D(x, y)].statut = 1;
    }

    *compteCasePlayed = compteCasePlayed + 1;
    int maxX = max(0, x - 1);
    int minX = min(Ligne - 1, x + 1);
    int maxY = max(0, y - 1);
    int minY = min(Colonne - 1, y + 1);

    if (tableauJeu[getIndex1D(x, y)].number == 0)
    {
        for (int i = maxX; i < minX; i++)
        {
            for (int j = maxY; j < minY; j++)
            {
                if (tableauJeu[getIndex1D(i, j)].statut != 1)
                {
                    revealNearby(i, j, tableauJeu, Ligne, Colonne);
                };
            };
        };
    };
};

void display(Case* tableauJeu)
{
    // print colonne
    printf("      ");
    for (int y = 0; y < Colonne; y++)
    {
        if (y >= 10)
        {
            printf("%d ", y + 1);
        }
        else
        {
            printf("%d  ", y + 1);
        };

    };
    printf("\n\n");

    // print ligne
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
        if (tableauJeu[getIndex1D(i, y)].statut == 1)
        {
            printf(" %c ", tableauJeu[getIndex1D(i, y)].symbol);
        }
        else
        {
            printf(" ? ");
        };
        //printf(" %c ", tableauJeu[getIndex1D(i, y)].symbol);
    };
    printf("\n");
    }  
    
    printf("\n");
};

void placeBombeDebug(int x, int y, Case * tableauJeu)
{
    Case oBombe = { -1,0 ,'*' };
    tableauJeu[getIndex1D(x, y)] = oBombe;

}

void placeBombe(int nbBombe, Case * tableauJeu)
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

        for (int i = randomX - 1; i < randomX + 2; i++)
        {
            for (int j = randomY - 1; j < randomY + 2; j++)
                if (i < 0 || j < 0 || i > Ligne - 1 || j > Colonne - 1)
                {
                    continue;
                }
                else
                {
                    if (tableauJeu[getIndex1D(i, j)].symbol != '*') 
                    {
                        tableauJeu[getIndex1D(i, j)].number++;
                        tableauJeu[getIndex1D(i, j)].symbol = tableauJeu[getIndex1D(i, j)].number + '0';
                    }
                };

        };
        
        nbBombe = nbBombe - 1;
    };
};

void play(int ligne, int colonne, Case * tableauJeu, Case * tableauReveal, int nbBombe)
{
	int compteCasePlayed = 0;
    int gagnant = 0;
    while (gagnant == 0) {
        display(tableauJeu);
        printf("Que souhaitez vous placer d pour un drapeau et c pour casser : ");
        char choix = askResponseInput('d', 'c');
        positionChoice(&ligne, &colonne);
        revealNearby(ligne, colonne, tableauJeu, &compteCasePlayed);
        if (choix == 'd' && tableauJeu[getIndex1D(ligne - 1, colonne - 1)].symbol != 'F')
		{
			tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut = 1;
			tableauJeu[getIndex1D(ligne - 1, colonne - 1)].symbol = 'F';
		}
        else if (choix == 'd' && tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut == 1 && tableauJeu[getIndex1D(ligne - 1, colonne - 1)].number >= 0)
        {
            tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut = 0;
            tableauJeu[getIndex1D(ligne - 1, colonne - 1)].symbol = tableauJeu[getIndex1D(ligne - 1, colonne - 1)].number + '0';
        }
        else if(choix == 'd' && tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut == 1 && tableauJeu[getIndex1D(ligne - 1, colonne - 1)].number == -1)
        {
			tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut = 0;
			tableauJeu[getIndex1D(ligne - 1, colonne - 1)].symbol = '?';
        }
		else if (choix == 'c' && tableauJeu[getIndex1D(ligne - 1, colonne - 1)].number == -1)
        {
            looseReveal(tableauReveal);
            printf("Vous avez perdu bande de noobz\n\n");
            gagnant = 1; 
        }
        else if (compteCasePlayed == Ligne * Colonne - nbBombe)
        {
          printf("Vous avez gagné bande de Gigachad");
          gagnant = 2;
        }
        else if (choix == 'c' && tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut == 0) {
            tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut = 1;
            tableauJeu[getIndex1D(ligne - 1, colonne - 1)].symbol = 3;
			compteCasePlayed = compteCasePlayed + 1;
        }
        else if (choix == 'c' && tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut == 1)
        {
            printf("\nCette case a déja été jouer veuillez jouer autre chose\n");
        }
    };
}

int main()
{
    while (1) {
        printf("Bonjour vous souhaitez combien de ligne dans cette partie : ");
        Ligne = askNumberInput(2, INT_MAX);
        printf("Bonjour vous souhaitez combien de colonne dans cette partie :");
        Colonne = askNumberInput(2, INT_MAX);
        int nbBombe = (int)round(((Ligne) * (Colonne)) / 6.0);
        int nbFlag = nbBombe;
        int ligne = 0;
        int colonne = 0;
        

        Case * tableauJeu = malloc(sizeof(Case) * (Ligne * Colonne));
        Case * tableauReveal = malloc(sizeof(Case) * (Ligne * Colonne));
      
        initGrid(tableauJeu);
        placeBombe(nbBombe, tableauJeu);

        memcpy(tableauReveal, tableauJeu, sizeof(Case)* (Ligne * Colonne));
        //placeBombeDebug(0, 0, tableauJeu);

        play(ligne, colonne, tableauJeu,tableauReveal, nbBombe);

        printf("Souhaitez vous rejouez, si oui tapez o et si non tapez n : ");
        char reponse = askResponseInput('o', 'n');

		free(tableauJeu);
		free(tableauReveal);

        if (reponse == 'n')
        {
            return 0;
        }

    }
};

/* a faire */

// quand on gagne
// fonction découverte



//tab = malloc(sizeof(int));
//free(tab);
//realloc(tab,(sizeof(int));
//memcpy

// quand choix placement enlever 1 à i et j

// debut découvre tout ceux de number 0 et le premier ayant un nombre supérieur à 1
