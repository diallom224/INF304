#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terrain.h"
#include "robot.h"
#include "programme.h"
#include "interprete.h"  
#include "observateur.h"

void gestion_erreur_terrain(erreur_terrain err);
void gestion_erreur_programme(erreur_programme err);
void affichage_position_programme(erreur_programme e);

#define LMAX 256


int etat_attendu(Robot r, int ax, int ay, char ao) {
    int rx = abscisse(&r);
    int ry = ordonnee(&r);
    char ro;

    switch (orient(&r)) {
        case Nord:  ro = 'N'; break;
        case Sud:   ro = 'S'; break;
        case Est:   ro = 'E'; break;
        case Ouest: ro = 'O'; break;
    }

    if (rx == ax && ry == ay && ro == ao) {
        if (ao == 'N') {
            printf("Le robot est sur une position normale.\n");
        }
        printf("Ok.\n");
        return 0;
    } else {
        printf("Position attendue : (%d, %d), orientation : %c\n", ax, ay, ao);
        printf("Position obtenue : (%d, %d), orientation : %c\n", rx, ry, ro);
        printf("Test échoué.\n");
        return 1;
    }
}


// Fonction pour afficher la position du robot à chaque étape
// Première version de la fonction
void afficher_position_debogage(Robot r) {
    printf("Position actuelle : (%d, %d), orientation : ", abscisse(&r), ordonnee(&r));
    switch (orient(&r)) {
        case Nord:  printf("N\n"); break;
        case Sud:   printf("S\n"); break;
        case Est:   printf("E\n"); break;
        case Ouest: printf("O\n"); break;
    }
}

// Deuxième version de la fonction (modifiée)
void afficher_position(Robot r) {
    printf("Position actuelle : (%d, %d), orientation : ", abscisse(&r), ordonnee(&r));
    switch (orient(&r)) {
        case Nord:  printf("N\n"); break;
        case Sud:   printf("S\n"); break;
        case Est:   printf("E\n"); break;
        case Ouest: printf("O\n"); break;
    }
}


// Fonction principale
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <fichier test>\n", argv[0]);
        return 1;
    }

    char nom_fenvt[LMAX];
    char nom_fprog[LMAX];
    Environnement envt;
    Programme prog;
    erreur_terrain errt;
    erreur_programme errp;
    int nbstepmax, nbstep = 0, ax = 0, ay = 0;
    char cevent, ao = 'N';
    etat_inter etat;
    resultat_inter res;

    FILE *ftest = fopen(argv[1], "r");
    if (ftest == NULL) {
        perror("Erreur d'ouverture du fichier de test");
        return 1;
    }

    // Lecture des informations du fichier de test
    fscanf(ftest, "%s\n", nom_fenvt);
    errt = initialise_environnement(&envt, nom_fenvt);
    gestion_erreur_terrain(errt);

    fscanf(ftest, "%s\n", nom_fprog);
    errp = lire_programme(&prog, nom_fprog);
    gestion_erreur_programme(errp);

    fscanf(ftest, "%d\n", &nbstepmax);
    fscanf(ftest, " %c\n", &cevent);

    if (cevent == 'N' || cevent == 'F') {
        fscanf(ftest, "%d %d\n", &ax, &ay);
        fscanf(ftest, " %c", &ao);
    }
    fclose(ftest);

    // Initialisation de l'état et des variables
    init_etat(&etat);
    res = OK_ROBOT;

    // Boucle principale d'exécution du programme
    while (nbstep < nbstepmax && res == OK_ROBOT) {
        res = exec_pas(&prog, &envt, &etat);
        nbstep++;

        // Affichage de la position et de l'orientation à chaque étape
        afficher_position(envt.r);
    }

    // Vérification de l'état du robot après l'exécution
    switch (res) {
        case OK_ROBOT:
            printf("Robot sur une case libre, programme non terminé\n");
            if (cevent == 'N') {
                return etat_attendu(envt.r, ax, ay, ao);
            } else {
                printf("Test échoué, état attendu = %c\n", cevent);
                return 1;
            }

        case SORTIE_ROBOT:
            printf("Le robot est sorti :-)\n");
            if (cevent == 'S') {
                printf("Ok.\n");
                return 0;
            } else {
                printf("Test échoué, état attendu = %c\n", cevent);
                return 1;
            }

        case ARRET_ROBOT:
            printf("Robot sur une case libre, programme terminé :-/\n");
            if (cevent == 'F') {
                return etat_attendu(envt.r, ax, ay, ao);
            } else {
                printf("Test échoué, état attendu = %c\n", cevent);
                return 1;
            }

        case PLOUF_ROBOT:
            printf("Le robot est tombé dans l'eau :-(\n");
            if (cevent == 'P') {
                printf("Ok.\n");
                return 0;
            } else {
                printf("Test échoué, état attendu = %c\n", cevent);
                return 1;
            }

        case CRASH_ROBOT:
            printf("Le robot s'est écrasé sur un obstacle X-(\n");
            if (cevent == 'O') {
                printf("Ok.\n");
                return 0;
            } else {
                printf("Test échoué, état attendu = %c\n", cevent);
                return 1;
            }

        case ERREUR_PILE_VIDE:
            printf("ERREUR : pile vide\n");
            return 1;

        case ERREUR_ADRESSAGE:
            printf("ERREUR : erreur d'adressage\n");
            return 1;

        case ERREUR_DIVISION_PAR_ZERO:
            printf("ERREUR : division par zéro\n");
            return 1;

        default:
            printf("Erreur inconnue\n");
            return 1;
    }

    printf("Nombre de pas maximum atteint sans événement attendu\n");
    return 1;
}

// Gestion des erreurs liées au terrain
void gestion_erreur_terrain(erreur_terrain e) {
  switch (e) {
  case TERRAIN_OK:
    break;
  case TERRAIN_ERREUR_FICHIER:
    printf("Erreur lecture du terrain : erreur d'ouverture du fichier\n");
    exit(1);
  case TERRAIN_LARGEUR_INVALIDE:
    printf("Erreur lecture du terrain : largeur incorrecte\n");
    exit(1);
  case TERRAIN_HAUTEUR_INVALIDE:
    printf("Erreur lecture du terrain : hauteur incorrecte\n");
    exit(1);
  case TERRAIN_CARACTERE_INCONNU:
    printf("Erreur lecture du terrain : caractère incorrect\n");
    exit(1);
  case TERRAIN_LIGNE_TROP_LONGUE:
    printf("Erreur lecture du terrain : ligne trop longue\n");
    exit(1);
  case TERRAIN_LIGNE_TROP_COURTE:
    printf("Erreur lecture du terrain : ligne trop courte\n");
    exit(1);
  case TERRAIN_TROP_PEU_DE_LIGNES:
    printf("Erreur lecture du terrain : lignes manquantes\n");
    exit(1);
  case TERRAIN_LIGNES_MANQUANTES:
    printf("Erreur lecture du terrain : lignes manquantes\n");
    exit(1);
  case TERRAIN_POSITION_ROBOT_MANQUANTE:
    printf("Erreur lecture du terrain : position initiale du robot manquante\n");
    exit(1);
  }
}

// Gestion des erreurs liées au programme
void gestion_erreur_programme(erreur_programme e) {
  switch (e.type_err) {
  case PROGRAMME_OK:
    break;
  case PROGRAMME_ERREUR_FICHIER:
    printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
    exit(2);
  case PROGRAMME_ERREUR_BLOC_NON_FERME:
    printf("Erreur lecture du programme : bloc non fermé\n");
    exit(2);
  case PROGRAMME_ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
    printf("Erreur lecture du programme : fermeture de bloc excédentaire\n");
    affichage_position_programme(e);
    exit(2);
  case PROGRAMME_ERREUR_COMMANDE_INCORRECTE:
    printf("Erreur lecture du programme : commande incorrecte\n");
    affichage_position_programme(e);
    exit(2);
  }
}

// Affichage de la position du programme en cas d'erreur
void affichage_position_programme(erreur_programme e) {
  int i;
  printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
  printf("%s\n", e.ligne);
  for (i = 1; i < e.num_colonne; i++) {
    printf(" ");
  }
  printf("^\n");
}


