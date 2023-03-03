int SDL_Init(SDL_INIT_EVERYTHING);

int min(int a, int b) { return (a > b) ? b : a; }
int max(int a, int b) { return (a < b) ? b : a; }

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include < limits.h >
#include <windows.h>
#include <SDL.h>
#include <windows.h>

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

#include <windows.h>

void Color(int couleurDuTexte, int couleurDeFond)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

void textColor(Case* tableau, int indice)
{
    // fonction couleur du texte
    if (tableau[indice].number == -1)
    {
        Color(12, 0);
    }
    else if (tableau[indice].number == 0)
    {
        Color(8, 0);
    }
    else if (tableau[indice].number == 1)
    {
        Color(1, 0);
    }
    else if (tableau[indice].number == 2)
    {
        Color(11, 0);
    }
    else if (tableau[indice].number == 3)
    {
        Color(10, 0);
    }
    else if (tableau[indice].number == 4)
    {
        Color(9, 0);
    }
    else if (tableau[indice].number == 5)
    {
        Color(4, 0);
    }
    else if (tableau[indice].number == 6)
    {
        Color(6, 0);
    }
    else if (tableau[indice].number == 7)
    {
        Color(2, 0);
    }
    else if (tableau[indice].number == 8)
    {
        Color(13, 0);
    }
    else if (tableau[indice].number == 9)
    {
        Color(6, 0);
    }
        
}


int getIndex1D(int i, int j)
{
    //permet de recuperer la valeur de l'adresse memoire grâce à des coordonnees

    // j = colone
    // i = ligne

    return i * COLONNE + j;

};


void returnIndex1D(int place, int* coordonneesX, int* coordonneesY)
{
    //permet de recuperer les coordonnees grâce aux coordonnes de la memoire
    *coordonneesY = (place % COLONNE);

    *coordonneesX = (place - (place % COLONNE)) / COLONNE;
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
            printf("Le nombre choisi n'est compris entre %d et %d! ", min, max);
        };
    };

};

char askResponseInput(char c1, char c2)
{
    while (1) {
        char input;
        int error = scanf_s("%c", &input, 1);
        viderBuffer();
        if (error == 0) {
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

void positionChoice(int* x, int* y)
{
    printf("Quelle ligne voulez vous jouer ?: ");
    *x = askNumberInput(1, LIGNE);
    printf("Maintenant quelle colonne voulez vous jouer ?: ");
    *y = askNumberInput(1, COLONNE);
};


void initGrid(Case* tableauJeu)
{
    Case odefault = { 0,0 ,'0' };

    for (int i = 0; i < LIGNE; i++)
    {
        for (int y = 0; y < COLONNE; y++)
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
    for (int i = 0; i < COLONNE; i++)
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
            if (tableauReveal[getIndex1D(i, y)].statut == 0 && tableauReveal[getIndex1D(i, y)].symbol == '?')
            {
                tableauReveal[getIndex1D(i, y)].statut = 1;
                tableauReveal[getIndex1D(i, y)].symbol = '0';
            };
            textColor(tableauReveal, getIndex1D(i, y));
            printf(" %c ", tableauReveal[getIndex1D(i, y)].symbol);
            Color(15, 0);
        };
        printf("\n");
    }
    printf("\n");
};

void firstReveal(Case* tableauJeu, int ligne, int colonne, int* tableauDispBombe, int* tableauBombTaille)
{
    for (int i = ligne + 3; i >= ligne - 2; i = i - 1)
    {
        for (int j = colonne + 3; j >= colonne - 2; j = j - 1)
        {
            if (i < 0 || j < 0 || i > LIGNE - 1 || j > COLONNE - 1)
                continue;

            int index = getIndex1D(i, j);
            memcpy(tableauDispBombe + index, tableauDispBombe + index + 1, sizeof(int) * ((*tableauBombTaille) - (index + 1)));
            (*tableauBombTaille)--;
            tableauDispBombe = realloc(tableauDispBombe, sizeof(int) * (*tableauBombTaille));
        };
    };
}

void revealNearby(int  x, int  y, Case* tableauJeu, int* compteCasePlayed, int count)
{
    int index = getIndex1D(x, y);
    tableauJeu[index].statut = 1;
    *compteCasePlayed = *compteCasePlayed + 1;

    if (tableauJeu[index].number == 0)
    {
        int maxX = max(0, x - 1);
        int minX = min(LIGNE, x + 2);
        int maxY = max(0, y - 1);
        int minY = min(COLONNE, y + 2);
        for (int i = maxX; i < minX; i++)
        {
            for (int j = maxY; j < minY; j++)
            {
                if (tableauJeu[getIndex1D(i, j)].statut != 1)
                {
                    revealNearby(i, j, tableauJeu, compteCasePlayed, count + 1);
                }
            };
        };
    };
};

void display(Case* tableauJeu)
{
    // print colonne
    printf("      ");
    for (int y = 0; y < COLONNE; y++)
    {
        if (y >= 9)
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
                if (tableauJeu[getIndex1D(i, y)].symbol != '*' && tableauJeu[getIndex1D(i, y)].symbol != 'F')
                {
                    tableauJeu[getIndex1D(i, y)].symbol = tableauJeu[getIndex1D(i, y)].number + '0';
                };
                textColor(tableauJeu, getIndex1D(i, y));
                printf(" %c ", tableauJeu[getIndex1D(i, y)].symbol);
                Color(15, 0);
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

void placeBombeDebug(int x, int y, Case* tableauJeu)
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



void placeBombe(int nbBombe, Case* tableauJeu, int* tableauDispBombe, int tableauBombTaille)
{
    Case oBombe = { -1,0 ,'*' };
    srand(time(NULL));

    while (nbBombe > 0 && tableauBombTaille > 0)
    {
        //random sur l'indice
        int randomIndice = rand() % tableauBombTaille;
        int randomPos = tableauDispBombe[randomIndice];

        //on retire l'element du tableau
        memcpy(tableauDispBombe + randomIndice, tableauDispBombe + randomIndice + 1, sizeof(int) * (tableauBombTaille - (randomIndice + 1)));
        tableauBombTaille--;
        tableauDispBombe = realloc(tableauDispBombe, sizeof(int) * tableauBombTaille);

        int randomPosX;
        int randomPosY;
        returnIndex1D(randomPos, &randomPosX, &randomPosY);

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


void play(Case* tableauJeu, Case* tableauReveal, int nbBombe, int* coordonneesX, int* coordonneesY)
{

    int compteCasePlayed = 0;
    int gagnant = 0;
    int ligne;
    int colonne;
    while (gagnant == 0) {
        system("cls");
        display(tableauJeu);
        printf("Que souhaitez vous faire,\nf pour jouer drapeau et c pour decouvrir une case (f/c) : ");
        char choix = askResponseInput('f', 'c');

        positionChoice(&ligne, &colonne);
        ligne--;
        colonne--;
        int index = getIndex1D(ligne, colonne);

        if (choix == 'f')
        {
            if (tableauJeu[index].symbol != 'F' && tableauJeu[index].statut == 0)
            {
                tableauJeu[index].symbol = 'F';
                tableauJeu[index].statut = 1;
            }
            else if (tableauJeu[index].statut == 1 && tableauJeu[index].number == -1 && tableauJeu[index].symbol == 'F')
            {
                tableauJeu[index].statut = 0;
                tableauJeu[index].symbol = '?';
            }
            else if (tableauJeu[index].statut == 1 && tableauJeu[index].number >= 0 && tableauJeu[index].symbol == 'F')
            {
                tableauJeu[index].statut = 0;
                tableauJeu[index].symbol = tableauJeu[index].number + '?';
            }
        }
        else if (choix == 'c')
        {
            if (compteCasePlayed == 0)
            {
                int tableauBombTaille = LIGNE * COLONNE;
                int* tableauDispBombe = malloc(sizeof(int) * tableauBombTaille);

                for (int i = 0; i < tableauBombTaille; i++)
                {
                    tableauDispBombe[i] = i;
                };

                firstReveal(tableauJeu, ligne, colonne, tableauDispBombe, &tableauBombTaille);
                placeBombe(nbBombe, tableauJeu, tableauDispBombe, tableauBombTaille);
                memcpy(tableauReveal, tableauJeu, sizeof(Case) * (LIGNE * COLONNE));
                revealNearby(ligne, colonne, tableauJeu, &compteCasePlayed, 0);
                free(tableauDispBombe);
            }
            else
            {
                
                if (tableauJeu[index].number == -1)
                {
                    looseReveal(tableauReveal);
                    printf("Vous avez perdu bande de noobz\n\n");
                    gagnant = 1;
                }
                else if (tableauJeu[index].statut == 1)
                {
                    printf("\nCette case a deja ete jouer. Veuillez jouer une autre case\n");
                }
                else if (tableauJeu[index].statut == 0) {

                    tableauJeu[index].statut = 1;
                    compteCasePlayed = compteCasePlayed + 1;

                    revealNearby(ligne, colonne, tableauJeu, &compteCasePlayed, 0);
                    if (compteCasePlayed == (LIGNE * COLONNE) - nbBombe)
                    {
                        printf("Vous avez gagne bande de Gigachad\n\n");
                        gagnant = 2;
                    }
                }
            }

        }

    };
}

int difficulty(int diff)
{
    if (diff == 1)
    {
        int nbBombe = (int)round((((LIGNE) * (COLONNE)) / 6.0));
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
        int nbBombe = (int)(round((LIGNE) * (COLONNE) / 2));
        return nbBombe;
    }
}

int main(int argc, char* argv[])
{
    const char* SDL_GetError(void);

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s",
        SDL_GetError());
        return EXIT_FAILURE;
    }
         
    while (1) {
        printf("Bonjour quelle difficulte souhaitez vous utilise dans cette partie,\n1:facile  2:moyenne  3:complique  4:HardcoreSaMaman: ");
        DIFFICULTY = askNumberInput(1, 4);
        printf("Combien de lignes souhaitez vous dans cette partie, %d est le nombre minimum: ", DIFFICULTY + 9);
        LIGNE = askNumberInput(DIFFICULTY + 9, INT_MAX);
        printf("Maintenant combien de colonnes souhaitez vous dans cette partie, %d est le nombre minimum: ", DIFFICULTY + 9);
        COLONNE = askNumberInput(DIFFICULTY + 9, INT_MAX);

        


        int coordonneesX = 0;
        int coordonneesY = 0;
        int nbBombe = difficulty(DIFFICULTY);
        int nbFlag = nbBombe;

        Case* tableauJeu = malloc(sizeof(Case) * (LIGNE * COLONNE));
        Case* tableauReveal = malloc(sizeof(Case) * (LIGNE * COLONNE));


        initGrid(tableauJeu);

        play(tableauJeu, tableauReveal, nbBombe, &coordonneesX, &coordonneesY);

        printf("Souhaitez vous rejouez, si oui tapez o et si non tapez n : ");
        char reponse = askResponseInput('o', 'n');

        free(tableauJeu);
        free(tableauReveal);

        if (reponse == 'n')
        {
            void SDL_Quit(void);

            return 0;
        }

    }
};

/* a faire */

// interface graphique

