#include "robot.h"
#include "terrain.h"
#include <stdio.h>

#define TAILLE_TERRAIN 10

/* Affiche une orientation sur la sortie standard */
void afficher_orientation(Orientation o) {
    switch (o) {
    case Nord:
        printf("Nord\n");
        break;
    case Est:
        printf("Est\n");
        break;
    case Sud:
        printf("Sud\n");
        break;
    case Ouest:
        printf("Ouest\n");
        break;
    }
}

void afficher_infos_robot(Robot *r) {
    int x, y;

    // Récupérer la position du robot
    position(r, &x, &y);
    // Afficher la position
    printf("Position : (%d, %d) - Orientation : ", x, y);
    afficher_orientation(orient(r));
    printf("\n");
}

void afficher_terrain_et_robot(Terrain *t, Robot *r) {
    int i, j;
    char c;

    for (j = 0; j < hauteur(t); j++) {
        for (i = 0; i < largeur(t); i++) {
            if ((i == abscisse(r)) && (j == ordonnee(r))) {
                // Afficher le robot selon son orientation
                switch (orient(r)) {
                case Nord:
                    c = '^';
                    break;
                case Est:
                    c = '>';
                    break;
                case Sud:
                    c = 'v';
                    break;
                case Ouest:
                    c = '<';
                    break;
                }
            } else {
                // Afficher la case
                switch (t->tab[i][j]) {
                case LIBRE:
                    c = '.';
                    break;
                case ROCHER:
                    c = '#';
                    break;
                case EAU:
                    c = '~';
                    break;
                }
            }
            printf("%c", c);
        }
        printf("\n");
    }
}

/* Renvoie vrai si le robot r, de sa position et orientation courante,
   peut avancer dans le terrain t */
int robot_peut_avancer(Terrain *t, Robot *r) {
    int x, y;
    position_devant(r, &x, &y);
    
    // Vérifier si la position devant le robot est à l'intérieur du terrain
    if (x < 0 || x >= largeur(t) || y < 0 || y >= hauteur(t)) {
        return 0; 
    }

    
    return est_case_libre(t, x, y);
}

int main(int argc, char **argv) {
    Terrain t;
    FILE *f;
    erreur_terrain e;
    int x, y;
    Robot r;
    char c;

    while (1) {
        // Lecture du terrain : nom du fichier en ligne de commande
        printf("Entrez le nom du fichier de terrain : ");
        char nom_fichier[100];
        scanf("%s", nom_fichier);
        
        // Lecture du terrain
        f = fopen(nom_fichier, "r");
        if (f == NULL) {
            printf("Erreur: Impossible d'ouvrir le fichier %s\n", nom_fichier);
            continue; 
        }

        e = lire_terrain(f, &t, &x, &y);
        fclose(f);

        if (e != TERRAIN_OK) {
            // Affichage du message d'erreur correspondant
            switch (e) {
                case TERRAIN_ERREUR_FICHIER:
                    printf("Erreur lors de l'ouverture du fichier.\n");
                    break;
                case TERRAIN_LARGEUR_INVALIDE:
                    printf("Erreur: Largeur invalide.\n");
                    break;
                case TERRAIN_HAUTEUR_INVALIDE:
                    printf("Erreur: Hauteur invalide.\n");
                    break;
                case TERRAIN_LIGNE_TROP_COURTE:
                    printf("Erreur: Ligne trop courte.\n");
                    break;
                case TERRAIN_LIGNE_TROP_LONGUE:
                    printf("Erreur: Ligne trop longue.\n");
                    break;
                case TERRAIN_CARACTERE_INCONNU:
                    printf("Erreur: Caractère inconnu dans le terrain.\n");
                    break;
                case TERRAIN_TROP_PEU_DE_LIGNES:
                    printf("Erreur: Trop peu de lignes dans le terrain.\n");
                    break;
                default:
                    printf("Erreur inconnue.\n");
                    break;
            }
            continue;   
        }

        // Initialisation du robot
        init_robot(&r, x, y, Est);
        afficher_infos_robot(&r);
        afficher_terrain_et_robot(&t, &r);

        // Boucle de commande
        printf("Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in) : ");
        scanf(" %c", &c);
        while (c != 'f') {
            int x, y; 
            switch (c) {
            case 'G':
            case 'g':
                tourner_a_gauche(&r);
                break;
            case 'D':
            case 'd':
                tourner_a_droite(&r);
                break;
            case 'A':
            case 'a':
                position_devant(&r, &x, &y);
                if (robot_peut_avancer(&t, &r)) {
                    avancer(&r);
                } else {
                    printf(" !! Le robot ne peut pas avancer !!\n");
                }
            }

            afficher_infos_robot(&r);
            afficher_terrain_et_robot(&t, &r);

            printf("Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in) : ");
            scanf(" %c", &c);
        }

        // Demander si l'utilisateur veut continuer avec un autre fichier
        char continuer;
        printf("Voulez-vous charger un autre terrain ? (o/n) : ");
        scanf(" %c", &continuer);
        if (continuer != 'o' && continuer != 'O') {
            break; 
        }
    }

    return 0;
}
 