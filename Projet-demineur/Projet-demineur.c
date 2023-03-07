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
#include <ctype.h>

#define GAP_X 80
#define GAP_Y 50


int LIGNE = 10;
int COLONNE = 10;
int DIFFICULTY = 0;
char GRAPH = ' ';



typedef struct Case
{
    // Fonction permettant la création de la structure des case du démineur

    int number; //chiffre present dans la case 0 par defaut, -1 pour une bombe ou nb bombe autour 
    int statut; //statut de la case 0 si pas decouvert, 1 si decouvert et -1 pour le drapeau
    char symbol; // symbole montre sur la grille de jeu

}Case;

#include <windows.h>

void Color(int couleurDuTexte, int couleurDeFond)
{
    // fonction permettant de changer la couleur

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
    // Fonction permettant de demander au joueur quelle valeur il veut utiliser
    // Par la suite cela nous servira pour les lignes et colonnes du démineur

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
    // Fonction permettant de demander au joueur quelle caractère il veut utiliser
    // Par la suite cela nous servira pour savoir s'il veut poser un drapeau ou découvrir une case

    char c3 = toupper(c1);
    char c4 = toupper(c2);
    while (1) {
        char input;
        int error = scanf_s("%c", &input, 1);
        viderBuffer();
        if (error == 0) {
            printf("Vous avez entrez un ou des chiffres, entrez %c et %c ! ", c1, c2);
        }
        else if (input == c1 || input == c2 || input == c3 || input == c4) {
            return input;
        }
        else {
            printf("Vous devez repondre %c ou %c ! ", c1, c2);
        };
    };

};

void positionChoice(int* x, int* y)
{
    // Permet de demander à l'utilisateur quelle ligne et colonne il souhaite jouer

    printf("Quelle ligne voulez vous jouer ?: ");
    *x = askNumberInput(1, LIGNE);
    printf("Maintenant quelle colonne voulez vous jouer ?: ");
    *y = askNumberInput(1, COLONNE);
};


void initGrid(Case* tableauJeu)
{
    // Permet d'initialiser un tableau avec des cases ayant pour nombre 0 pour statut 0 (non découvert) et pour symbol un 0

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
    // Permet de révéler une case en passant son statut à 1

    if (tableauJeu[getIndex1D(x, y)].statut == 0)
    {
        tableauJeu[getIndex1D(x, y)].statut = 1;
    };
};

void looseReveal(Case* tableauReveal)
{
    //Permet d'afficher le tableau généré avec tout de révélé

    // Chiffres en haut
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

    // Chiffres sur le coté et affichage du tableau
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
    //Permet de faire la premièré révélation lorsque l'on joue. C'est à dire que l'on va d'écouvrir 1 cases et les 8 autour (en carré) en statut révélé et pour nombre 0.
    //Et la case choisi + les 24 cases autour (en carré) comme quoi elles ne peuvent plus être des bombes
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
    //Permet de révéler toutes les cases ayant pour nombre 0 autour de celle venant d'être révélé de manière récursive
    int index = getIndex1D(x, y);
    tableauJeu[index].statut = 1;
    *compteCasePlayed = *compteCasePlayed + 1;

    if (tableauJeu[index].number == 0)
    {
        //permet d'encadrer les zones de recherche pour chercher les cases ayant pour nombre 0
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
                    //récursivité
                    revealNearby(i, j, tableauJeu, compteCasePlayed, count + 1);
                }
            };
        };
    };
};

void display(Case* tableauJeu)
{
    //Permet d'afficher les grilles du démineur
    
    
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
    //Fonction de débug permettant de placer des bombes aux coordonnées souhaitaient

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
    //Permet de placer des bombes dans la grille du démineurs de façon aléatoire.

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


void game(Case* tableauJeu, Case* tableauReveal, int nbBombe, int* coordonneesX, int* coordonneesY)
{
    //Permet de lancer le jeu du démineur 

    int compteCasePlayed = 0;
    int gagnant = 0;
    int ligne;
    int colonne;
    while (gagnant == 0) {
        display(tableauJeu);
        printf("Que souhaitez vous faire,\nf pour jouer drapeau et c pour decouvrir une case (f/c) : ");
        char choix = askResponseInput('f', 'c');

        positionChoice(&ligne, &colonne);
        ligne--;
        colonne--;
        int index = getIndex1D(ligne, colonne);
        //système("cls");
        if (choix == 'F' || choix == 'f')
        {
            if (tableauJeu[index].number != -1)
            {
                looseReveal(tableauReveal);
                printf("Vous avez perdu bande de noobz\n\n");
                gagnant = 1;
            }
            else if (tableauJeu[index].symbol != 'F' && tableauJeu[index].statut == 0)
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
        else if (choix == 'c' || choix == 'C')
        {
            if (compteCasePlayed == 0)
            {
                int tableauBombTaille = LIGNE * COLONNE;
                int* tableauDispBombe = malloc(sizeof(int) * tableauBombTaille);

                for (int i = 0; i < tableauBombTaille; i++)
                {
                    tableauDispBombe[i] = i;
                };

                //placeBombeDebug(0, 0, tableauJeu);
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
                    printf("\nCette case a deja ete jouer. Veuillez jouer une autre case\n\n");
                }
                else if (tableauJeu[index].statut == 0) {

                    tableauJeu[index].statut = 1;

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
    //Permet de définir le nombre de bombe totale par rapport à la difficulté choisie

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

// SDL
int setWindowColor(SDL_Renderer* renderer, SDL_Color color)
{
   if (SDL_SetRenderDrawColor(renderer, color.r, color.g,
        color.b, color.a) < 0)
       return -1;
   if (SDL_RenderClear(renderer) < 0)
       return -1;
   return 0;
   }


void graphiqueGrid(SDL_Window* renderer)
{
    // init grille
    int col = GAP_X;
    int lign = GAP_Y;
    int count = 0;
    for (int i = 0; i < LIGNE; i++)
    {
        col = 80;
        for (int j = 0; j < COLONNE; j++)
        {
            if (count % 2 == 0)
            {
                SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255); //On dessine en vert foncé
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255); //On dessine en vert clair
            }
            SDL_Rect rect = { col, lign, 50, 50 };
            SDL_RenderFillRect(renderer, &rect);

            col = col + 50;
            count++;
        }
        lign = lign + 50;
        count++;
    }
};

int positionPossible(int x, int y, int heigth , int length)
{

    if (x >= 0 && x <= (length * LIGNE))
    {
        if (y >= 0  && y <= (heigth * COLONNE))
        {
            return 1;
        }
    }
}

void graphiqueIndice(int x, int y, int heigth, int length)
{
    int indiceColonne;
    int indiceLigne;
    if (positionPossible(x, y, heigth, length) == 1)
    {
        indiceColonne = (int)(x / 50);
        indiceLigne = (int)(y / 50);
        printf("indice %d\n", getIndex1D(indiceLigne, indiceColonne));

    }
    else
    {
        printf("dommage\n");
    }
}
graphiquePosition(int x, int y, int heigth, int length)
{
    if (positionPossible(x, y, heigth, length) == 1)
    {

    }
}
int main()
{
    //SDL

    //init SDL page et renderer
    SDL_Window* window = NULL;
    SDL_Window* renderer = NULL;
    SDL_Texture* texture = NULL;
    int statut = EXIT_FAILURE;
    SDL_Event event;
    Uint8* clavier;
    SDL_bool quit = SDL_FALSE;
    SDL_Color orange = { 100, 100, 100, 255 };

    // button
    int x, y;
    Uint32 boutons;


    int heigth = 50;
    int length = 50;

    /* Initialisation, création de la fenêtre et du renderer. */
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s",
            SDL_GetError());
        goto Quit;
    }
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 700, SDL_WINDOW_RESIZABLE);
    if (NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s",
            SDL_GetError());
        goto Quit;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s",
            SDL_GetError());
        goto Quit;
    }
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 200);
    if (NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTexture : %s",
            SDL_GetError());
        goto Quit;
    }

    // background
    setWindowColor(renderer, orange);

    // grille de jeu
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); //On dessine en vert foncé
    SDL_Rect rectGrille = { 50, 50, 800, 600 };
    SDL_RenderFillRect(renderer, &rectGrille);

    while (!quit)
        {
        SDL_PumpEvents();
        boutons = SDL_GetMouseState(&x, &y);
        clavier = SDL_GetKeyboardState(NULL);

        graphiqueGrid(renderer);

        SDL_RenderPresent(renderer);
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT || clavier[SDL_SCANCODE_ESCAPE] || clavier[SDL_SCANCODE_RETURN])
            quit = SDL_TRUE;
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (boutons & SDL_BUTTON(SDL_BUTTON_RIGHT))
            {
                printf("Clic droit a la positions %d - %d\n", x, y);
            }
            else if (boutons & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                printf("Clic gauche a la positions %d - %d\n", x, y);
            }

            graphiqueIndice(x - GAP_X, y - GAP_Y, 50, 50);
        }
        }

    statut = EXIT_SUCCESS;

    //SDL_Rect dst = { 0, 0, 50, 50 };
    //SDL_RenderCopy(renderer, texture, NULL, &dst);

Quit:
    if (NULL != texture)
        SDL_DestroyTexture(texture);
    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;

    return 0;
}

int main2()
{
    //Jeu
    while (1) {
        printf("Bonjour quelle difficulte souhaitez vous utilise dans cette partie,\n1:facile  2:moyenne  3:complique  4:HardcoreSaMaman: ");
        DIFFICULTY = askNumberInput(1, 4);
        printf("Combien de lignes souhaitez vous dans cette partie, %d est le nombre minimum: ", DIFFICULTY + 9);
        LIGNE = askNumberInput(DIFFICULTY + 9, INT_MAX);
        printf("Maintenant combien de colonnes souhaitez vous dans cette partie, %d est le nombre minimum: ", DIFFICULTY + 9);
        COLONNE = askNumberInput(DIFFICULTY + 9, INT_MAX);
        printf("Voulez vous jouer avec la console 'c' ou l'interface graphique 'g' : ");
        GRAPH = askResponseInput('c', 'g');

        int coordonneesX = 0;
        int coordonneesY = 0;
        int nbBombe = difficulty(DIFFICULTY);
        int nbFlag = nbBombe;

            Case* tableauJeu = malloc(sizeof(Case) * (LIGNE * COLONNE));
            Case* tableauReveal = malloc(sizeof(Case) * (LIGNE * COLONNE));


            initGrid(tableauJeu);

            game(tableauJeu, tableauReveal, nbBombe, &coordonneesX, &coordonneesY);

            


            free(tableauJeu); //libère la mémoire
            free(tableauReveal);

            printf("Souhaitez vous rejouez, si oui tapez o et si non tapez n : ");
            char reponse = askResponseInput('o', 'n');

            if (reponse == 'n' || reponse == 'N')
            {
                return 0;
            }
    }
};

/* a faire */

// interface graphique

