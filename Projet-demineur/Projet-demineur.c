int min(int a, int b) { return (a > b) ? b : a; }
int max(int a, int b) { return (a < b) ? b : a; }

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include < limits.h >

int Ligne = 10;
int Colonne = 10;
int diff = 0;

typedef struct Case
{
    int number; //chiffre present dans la case 0 par defaut, -1 pour une bombe ou nb bombe autour 
    int statut; //statut de la case 0 si pas decouvert, 1 si decouvert et -1 pour le drapeau
    char symbol; // symbole montre sur la grille de jeu

}Case;


int getIndex1D(int i, int j)
{
    //permet de recuperer la valeur de l'adresse memoire grâce à des coordonnees

    // j = colone
    // i = ligne

    return i * Colonne + j;

};


void returnIndex1D(int place,int* coordonneesX, int* coordonneesY)
{
    //permet de recuperer les coordonnees grâce aux coordonnes de la memoire
    *coordonneesY = (place % Colonne);
    
    *coordonneesX = (place - (place % Colonne) ) / Colonne;
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
            printf("Le nombre choisi n'est pas entre %d et %d! ", min, max);
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
    printf("Alors quelle ligne veux-tu jouer   ?: ");
    *x = askNumberInput(1, Ligne);
    printf("Maintenant quelle colonne veux-tu jouer ?: ");
    *y = askNumberInput(1, Colonne);
};


void initGrid(Case* tableauJeu)
{
    Case odefault = { 0,0 ,'0' };

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
    if (tableauJeu[getIndex1D(x-1, y-1)].number != -1)
    {
        tableauJeu[getIndex1D(x-1, y-1)].statut = 1;
        *compteCasePlayed = compteCasePlayed + 1;
    }
    
    if (tableauJeu[getIndex1D(x-1, y-1)].number == 0)
    {
        int maxX = max(0, x - 1);
        int minX = min(Colonne - 1, x + 1);
        int maxY = max(0, y - 1);
        int minY = min(Ligne - 1, y + 1);
        for (int i = maxX; i <= minX; i++)
        {
            for (int j = maxY; j <= minY; j++)
            {
                if (tableauJeu[getIndex1D(i, j)].statut != 1)
                {
                    revealNearby(i, j, tableauJeu, compteCasePlayed);
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
        /*if (tableauJeu[getIndex1D(i, y)].statut == 1)
        {
            tableauJeu[getIndex1D(i, y)].symbol = tableauJeu[getIndex1D(i, y)].number + '0';
            printf(" %c ", tableauJeu[getIndex1D(i, y)].symbol);
        }
        else
        {
            printf(" ? ");
        };*/
        printf(" %c ", tableauJeu[getIndex1D(i, y)].symbol);
    };
    printf("\n");
    }  
    
    printf("\n");
};

void placeBombeDebug(int x, int y, Case * tableauJeu)
{
    Case oBombe = { -1,0 ,'*' };
    tableauJeu[getIndex1D(x, y)] = oBombe;

    for (int i = x - 1; i < x + 2; i++)
    {
        for (int j = y - 1; j < y + 2; j++)
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
};



void placeBombe(int nbBombe, Case * tableauJeu, int * coordonneesX, int * coordonneesY, int * tableauDispBombe, int tableauBombTaille)
{
    Case oBombe = { -1,0 ,'*' };
    srand(time(NULL));

    for (int i = 0; i < tableauBombTaille; i++)
    {
        tableauDispBombe[i] = i;
    };
    
    
    while (nbBombe > 0)
    {
        //random sur l'indice
        int randomIndice = rand() % tableauBombTaille;
        int randomPos = tableauDispBombe[randomIndice];

        //on retire l'element du tableau
        memcpy(tableauDispBombe + randomIndice, tableauDispBombe + randomIndice + 1, sizeof(int) * ( tableauBombTaille - (randomIndice + 1) ) );
        tableauBombTaille--;
        tableauDispBombe = realloc(tableauDispBombe, sizeof(int) * tableauBombTaille);


        returnIndex1D(randomPos, &coordonneesX, &coordonneesY);

        int randomPosX = coordonneesX;
        int randomPosY = coordonneesY;
            
        if (tableauJeu[randomPos].number == -1)
        {
            continue;
        };

        tableauJeu[randomPos] = oBombe;

        for (int i = randomPosX - 1; i < randomPosX + 2; i++)
        {
            for (int j = randomPosY - 1; j < randomPosY + 2; j++)
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

void play(int ligne, int colonne, Case * tableauJeu, Case * tableauReveal, int nbBombe, int compteCasePlayed)
{
	
    int gagnant = 0;
    while (gagnant == 0) {
        display(tableauJeu);
        printf("Que souhaitez vous placer d pour un drapeau et c pour casser (d/c) : ");
        char choix = askResponseInput('d', 'c');
        positionChoice(&ligne, &colonne);
        if (choix == 'd') {
            if (tableauJeu[getIndex1D(ligne - 1, colonne - 1)].symbol != 'F')
            {
                tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut = 1;
                tableauJeu[getIndex1D(ligne - 1, colonne - 1)].symbol = 'F';
            }
            else if (tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut == 1 && tableauJeu[getIndex1D(ligne - 1, colonne - 1)].number >= 0)
            {
                tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut = 0;
                tableauJeu[getIndex1D(ligne - 1, colonne - 1)].symbol = tableauJeu[getIndex1D(ligne - 1, colonne - 1)].number + '0';
            }
            else if (tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut == 1 && tableauJeu[getIndex1D(ligne - 1, colonne - 1)].number == -1)
            {
                tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut = 0;
                tableauJeu[getIndex1D(ligne - 1, colonne - 1)].symbol = '?';
            }
        }
        else if (choix == 'c')
        {
            revealNearby(ligne, colonne, tableauJeu, &compteCasePlayed);

            if (tableauJeu[getIndex1D(ligne - 1, colonne - 1)].number == -1)
            {
                looseReveal(tableauReveal);
                printf("Vous avez perdu bande de noobz\n\n");
                gagnant = 1;
            }
            else if (compteCasePlayed == Ligne * Colonne - nbBombe)
            {
                printf("Vous avez gagne bande de Gigachad");
                gagnant = 2;
            }
            else if (tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut == 0) {

                tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut = 1;
                tableauJeu[getIndex1D(ligne - 1, colonne - 1)].symbol = 3;
                compteCasePlayed = compteCasePlayed + 1;
            }
            else if (tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut == 1)
            {
                printf("\nCette case a deja ete jouer, veuillez jouer autre chose\n");
            }
        }
        	
    };
}

int difficulty(int diff)
{
    if (diff == 1)
    {
        int nbBombe = (int)round(((Ligne) * (Colonne)) / 6.0);
        return nbBombe;
    }
    else if (diff == 2)
    {
		int nbBombe = (int)(round(((Ligne) * (Colonne)) / 6.0)) * 2;
		return nbBombe;
    }
	else if (diff == 3)
	{
		int nbBombe = (int)(round(((Ligne) * (Colonne)) / 6.0)) * 3;
		return nbBombe;
	}
	else if (diff == 4)
	{
		int nbBombe = (int)(round(((Ligne) * (Colonne)) -1 ));
		return nbBombe;
	}
}

int main()
{
    while (1) {
        printf("Bonjour vous souhaitez combien de lignes dans cette partie : ");
        Ligne = askNumberInput(2, INT_MAX);
        printf("Maintenant vous souhaitez combien de colonnes dans cette partie :");
        Colonne = askNumberInput(2, INT_MAX);
		printf("et enfin vous souhaitez quelle difficulte dans cette partie 1:facile 2:moyenne 3:complique 4:HardcoreSaMaman:");
        diff = askNumberInput(1, 4);
        int coordonneesX = 0;
        int coordonneesY = 0;
        int nbBombe = difficulty(diff);
        int nbFlag = nbBombe;
        int ligne = 0;
        int colonne = 0;
		int compteCasePlayed = 0;
        int tableauBombTaille = Ligne * Colonne;

		
        Case * tableauJeu = malloc(sizeof(Case) * (Ligne * Colonne));
		Case* tableauReveal = malloc(sizeof(Case) * (Ligne * Colonne));
		int * tableauDispBombe = malloc(sizeof(int) * tableauBombTaille);
        
      
        initGrid(tableauJeu);

        placeBombe(nbBombe, tableauJeu, &coordonneesX, &coordonneesY, tableauDispBombe, tableauBombTaille);
        //placeBombeDebug(0, 0, tableauJeu);

        memcpy(tableauReveal, tableauJeu, sizeof(Case)* (Ligne * Colonne));
        

        play(ligne, colonne, tableauJeu,tableauReveal, nbBombe, &compteCasePlayed);

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

// première découverte
// interface graphique

