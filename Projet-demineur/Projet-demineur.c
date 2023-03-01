int min(int a, int b) { return (a > b) ? b : a; }
int max(int a, int b) { return (a < b) ? b : a; }

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include < limits.h >
#include <SDL.h>


SDL_Window* SDL_CreateWindow(const char* title,
    int         x,
    int         y,
    int         w,
    int         h,
    Uint32      flags);

int LIGNE = 10;
int COLONNE = 10;
int DIFFICULTY = 0;

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

    while (i < size) 
    {
        y = 0;
        while (y < size)
        {
            if (i == 0 && y == 0)
            {
                printf("  ");
            }
            if (i==0)
            else
            {
                tableau[i][y] = odefault.number;
                printf("? ");
            }
     

            if (i == 0)
            {
                tableau[i][y] = y;
			};
			if (y == 0)
			{
				tableau[i][y] = i;
			};
    
            if (y == size - 1 && i == size - 1)
            {
                tableau[i][y] = odefault.number;
            };

    };
    printf("\n\n");

    // print ligne
    for (int i = 0; i < LIGNE; i++)
    {
        if (i >= 9)
        {
            printf(" %d  ", i + 1);
        }
        else
        {
            printf(" %d   ", i + 1);
        };

    for (int y = 0; y < COLONNE; y++)
    {
        if (tableauJeu[getIndex1D(i, y)].statut == 1)
        {
            tableauJeu[getIndex1D(i, y)].symbol = tableauJeu[getIndex1D(i, y)].number + '0';
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

    for (int i = x - 1; i < x + 2; i++)
    {
        for (int j = y - 1; j < y + 2; j++)
            if (i < 0 || j < 0 || i > LIGNE - 1 || j > COLONNE - 1)
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
                if (i < 0 || j < 0 || i > LIGNE - 1 || j > COLONNE - 1)
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


void play(int ligne, int colonne, Case * tableauJeu, Case * tableauReveal, int nbBombe, int *compteCasePlayed, int* tableauDispBombe, int tableauBombTaille, int * coordonneesX, int * coordonneesY)
{
    int gagnant = 0;
    while (gagnant == 0) {
        system("cls");
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
            printf("%d", *compteCasePlayed);
            if (*compteCasePlayed == 0)
            {
                firstReveal(tableauJeu, ligne, colonne, tableauDispBombe, tableauBombTaille, compteCasePlayed);
                placeBombe(nbBombe, tableauJeu, &coordonneesX, &coordonneesY, tableauDispBombe, tableauBombTaille);
                revealNearby(ligne, colonne, tableauJeu, compteCasePlayed);
            }
            else
            {
                revealNearby(ligne, colonne, tableauJeu, compteCasePlayed);

                if (tableauJeu[getIndex1D(ligne - 1, colonne - 1)].number == -1)
                {
                    looseReveal(tableauReveal);
                    printf("Vous avez perdu bande de noobz\n\n");
                    gagnant = 1;
                }
                else if (*compteCasePlayed == LIGNE * COLONNE - nbBombe)
                {
                    printf("Vous avez gagne bande de Gigachad");
                    gagnant = 2;
                }
                else if (tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut == 0) {

                    tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut = 1;
                    tableauJeu[getIndex1D(ligne - 1, colonne - 1)].symbol = 3;
                    *compteCasePlayed = compteCasePlayed + 1;
                }
                else if (tableauJeu[getIndex1D(ligne - 1, colonne - 1)].statut == 1)
                {
                    printf("\nCette case a deja ete jouer, veuillez jouer autre chose\n");
                }
            }
            
        }
        	
    };
}

int difficulty(int diff)
{
    if (diff == 1)
    {
        int nbBombe = (int)round(((LIGNE) * (COLONNE)) / 6.0);
        return nbBombe;
    }
    else if (diff == 2)
    {
		int nbBombe = (int)(round(((LIGNE) * (COLONNE)) / 6.0)) * 2;
		return nbBombe;
    }
	else if (diff == 3)
	{
		int nbBombe = (int)(round(((LIGNE) * (COLONNE)) / 6.0)) * 3;
		return nbBombe;
	}
	else if (diff == 4)
	{
		int nbBombe = (int)(round(((LIGNE) * (COLONNE)) -1 ));
		return nbBombe;
	}
}

int main()
{
    while (1) {
        printf("Bonjour vous souhaitez combien de lignes dans cette partie : ");
        LIGNE = askNumberInput(2, INT_MAX);
        printf("Maintenant vous souhaitez combien de colonnes dans cette partie :");
        COLONNE = askNumberInput(2, INT_MAX);
		printf("et enfin vous souhaitez quelle difficulte dans cette partie 1:facile 2:moyenne 3:complique 4:HardcoreSaMaman:");
        DIFFICULTY = askNumberInput(1, 4);
        int coordonneesX = 0;
        int coordonneesY = 0;
        int nbBombe = difficulty(DIFFICULTY);
        int nbFlag = nbBombe;
        int ligne = 0;
        int colonne = 0;
		int compteCasePlayed = 0;
        int tableauBombTaille = LIGNE * COLONNE;
		
        Case * tableauJeu = malloc(sizeof(Case) * (LIGNE * COLONNE));
		Case* tableauReveal = malloc(sizeof(Case) * (LIGNE * COLONNE));
		int * tableauDispBombe = malloc(sizeof(int) * tableauBombTaille);

        for (int i = 0; i < tableauBombTaille; i++)
        {
            tableauDispBombe[i] = i;
        };
      
        initGrid(tableauJeu);

        //placeBombeDebug(0, 0, tableauJeu);

        memcpy(tableauReveal, tableauJeu, sizeof(Case)* (LIGNE * COLONNE));


        play(ligne, colonne, tableauJeu,tableauReveal, nbBombe, &compteCasePlayed, tableauDispBombe, tableauBombTaille, coordonneesX, coordonneesY);

        printf("Souhaitez vous rejouez, si oui tapez o et si non tapez n : ");
        char reponse = askResponseInput('o', 'n');

		free(tableauJeu);
		free(tableauReveal);
        free(tableauDispBombe);

        if (reponse == 'n')
        {
            return 0;
        }

    }
};

/* a faire */

// première découverte
// interface graphique

