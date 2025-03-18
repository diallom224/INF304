#include "robot.h"
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

/* Affiche les informations du robot */
void afficher_infos_robot(Robot *r) {
    int x, y;
    int x_devant, y_devant;

    // Récupérer la position du robot
    position(r, &x, &y);
    // Récupérer la case devant le robot
    position_devant(r, &x_devant, &y_devant);

    // Afficher la position
    printf("Position : (%d, %d) - Orientation : ", x, y);
    afficher_orientation(orient(r));
    printf("Case devant : (%d, %d)\n", x_devant, y_devant);
}

int main() {
    Robot r;
    
    // Initialiser le robot à la position (5, 5) orienté vers le Nord
    init_robot(&r, 5, 5, Nord);
    printf("Initialisation du robot :\n");
    afficher_infos_robot(&r);

    // Avancer le robot
    avancer(&r);
    printf("\nAprès avoir avancé :\n");
    afficher_infos_robot(&r);

    // Tourner à droite et avancer
    tourner_a_droite(&r);
    printf("\nAprès avoir tourné à droite :\n");
    afficher_infos_robot(&r);
    avancer(&r);
    printf("\nAprès avoir avancé :\n");
    afficher_infos_robot(&r);

    // Tourner à gauche et avancer
    tourner_a_gauche(&r);
    printf("\nAprès avoir tourné à gauche :\n");
    afficher_infos_robot(&r);
    avancer(&r);
    printf("\nAprès avoir avancé :\n");
    afficher_infos_robot(&r);

    return 0;
}
