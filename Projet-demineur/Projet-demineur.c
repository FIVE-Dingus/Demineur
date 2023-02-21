// Projet-demineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#define size 10 + 1

int main()
{
    int tableau[size][size];
    
    int i = 0;
    int y = 0;

    while (i < size) 
    {
        y = 0;
        while (y < size)
        {
            tableau[i][y] =  0;
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
                tableau[i][y] = 00;
            };

            if (i == 0 && y >= 10 || y == 0 && i >= 10)
            {
                printf("  %d ", tableau[i][y]);
            }               
            else
            {
                printf("  %d  ", tableau[i][y]);
            };

            
            y++;
        };
        printf("\n");
        i++;
    }

    printf("\nhello\n");

    return 0;
}


typedef struct Case
{
    int number; //chiffre présent dans la case 0 par défaut, -1 pour une bombe
    int statut; //statut de la case 0 si pas découvert, 1 si découvert et -1 pour le drapeau

}Case;





// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
