#include "terrain.h"
#include <stdio.h>

void afficher_message_erreur(erreur_terrain err) {
    switch (err) {
        case TERRAIN_ERREUR_FICHIER:
            printf("Erreur : le fichier ne peut pas être ouvert.\n");
            break;
        case TERRAIN_LARGEUR_INVALIDE:
            printf("Erreur : largeur invalide.\n");
            break;
        case TERRAIN_HAUTEUR_INVALIDE:
            printf("Erreur : hauteur invalide.\n");
            break;
        case TERRAIN_CARACTERE_INCONNU:
            printf("Erreur : caractère inconnu dans le terrain.\n");
            break;
        case TERRAIN_LIGNE_TROP_COURTE:
            printf("Erreur : ligne trop courte.\n");
            break;
        case TERRAIN_LIGNE_TROP_LONGUE:
            printf("Erreur : ligne trop longue.\n");
            break;
        case TERRAIN_TROP_PEU_DE_LIGNES:
            printf("Erreur : trop peu de lignes lues.\n");
            break;
        case TERRAIN_OK:
        default:
            printf("Aucune erreur.\n");
            break;
    }
}

int main(int argc, char **argv) {
    FILE *f;
    Terrain t;
    int x, y;
    char nom_fichier[256]; 

    
    if (argc < 2) {
        printf("Usage : %s <fichier>\n", argv[0]);
        return 1;
    }

    while (1) {
        f = fopen(argv[1], "r");

        // Vérifier si le fichier s'est ouvert avec succès
        if (f == NULL) {
            printf("Erreur lors de l'ouverture du fichier '%s'. Veuillez entrer un nouveau nom de fichier : ", argv[1]);
            scanf("%s", nom_fichier); 
            argv[1] = nom_fichier; 
            continue; 
        }

        // Si le fichier est ouvert avec succès, lire le terrain
        erreur_terrain err = lire_terrain(f, &t, &x, &y);
        fclose(f); 

        // Vérifier si la lecture a réussi
        if (err != TERRAIN_OK) {
            afficher_message_erreur(err); 
            printf("Veuillez entrer un nouveau nom de fichier : ");
            scanf("%s", nom_fichier);
            argv[1] = nom_fichier; 
            continue; 
        }

        // Si tout s'est bien passé, afficher le terrain et la position du robot
        afficher_terrain(&t);
        printf("Position initiale du robot : (%d, %d)\n", x, y);
        break; 
    }

    return 0;
}
