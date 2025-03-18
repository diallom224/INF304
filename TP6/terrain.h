#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <stdio.h>

typedef enum {
    LIBRE,
    EAU,
    ROCHER
} Case;

#define DIM_MAX 256

typedef struct {
    int largeur, hauteur;
    Case tab[DIM_MAX][DIM_MAX];
} Terrain;

typedef enum {
    TERRAIN_ERREUR_FICHIER,
    TERRAIN_LARGEUR_INVALIDE,
    TERRAIN_HAUTEUR_INVALIDE,
    TERRAIN_CARACTERE_INCONNU,
    TERRAIN_LIGNE_TROP_COURTE,
    TERRAIN_LIGNE_TROP_LONGUE,
    TERRAIN_TROP_PEU_DE_LIGNES,
    TERRAIN_LIGNES_MANQUANTES,
    TERRAIN_POSITION_ROBOT_MANQUANTE,
    TERRAIN_OK
} erreur_terrain;

erreur_terrain lire_terrain(FILE *f, Terrain *t, int *x, int *y);
int largeur(Terrain *t);
int hauteur(Terrain *t);
int est_case_libre(Terrain *t, int x, int y);
void afficher_terrain(Terrain *t);
void ecrire_terrain(FILE *f, Terrain *t, int x, int y);

#endif
