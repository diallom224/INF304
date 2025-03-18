#include <stdio.h>
#include <stdlib.h>
#include "programme.h"
#include "environnement.h"
#include "observateur.h"



// Fonction pour convertir une commande en alphabet
Alphabet convertir_commande_en_alphabet(Type_Commande cmd) {
    switch (cmd) {
        case Avancer: return A;
        case Gauche: return G;
        case Droite: return D;
        case Mesure: return M;
        default: return Erreur; 
        printf("bien converti\n");
    }
}

// Tester un programme
void tester_programme(const char *fichier_terrain, const char *fichier_programme) {
    // Initialiser l'environnement
    Environnement envt;
    erreur_terrain erreur_envt = initialise_environnement(&envt, fichier_terrain);
    if (erreur_envt != TERRAIN_OK) {
        printf("Erreur lors de l'initialisation du terrain\n");
        return;
    }

    // Lire le programme
    Programme prog;
    erreur_programme erreur_prog = lire_programme(&prog, fichier_programme);
    if (erreur_prog.type_err != PROGRAMME_OK) {
        printf("Erreur lors de la lecture du programme : %s\n", erreur_prog.ligne);
        return;
    }

    // Initialiser l'état de l'observateur
    Etat etat = Etat_initial();
    
    // Boucle pour exécuter les instructions
    int i = 0;
    int programme_valide = 1;
    while (i < prog.lg && programme_valide) {
        Commande instr = prog.tab[i];

        // Transition de l'état de l'observateur en fonction de l'instruction
        etat = Etat_transition(etat, convertir_commande_en_alphabet(instr.cmd));

        // Vérifier si l'état est un état d'erreur
        if (etat == Erreur) {
            printf("Erreur d'exécution du programme à la ligne %d\n", i + 1);
            programme_valide = 0;
            break;
        }

        // Appliquer l'instruction au robot et au terrain
        switch (instr.cmd) {
            case Avancer:
                if (avancer_envt(&envt) != OK_DEPL) {
                    printf("Erreur de déplacement à la ligne %d\n", i + 1);
                    programme_valide = 0;
                }
                break;

            case Gauche:
                gauche_envt(&envt);
                break;

            case Droite:
                droite_envt(&envt);
                break;

            case Mesure:
                // Ajouter le code pour effectuer une mesure avec envt ici
                break;

            default:
                printf("Commande non prise en charge à la ligne %d\n", i + 1);
                programme_valide = 0;
                break;
        }

        // Afficher l'état de l'environnement et du robot après chaque instruction
        afficher_envt(&envt);
        i++;
    }

    if (programme_valide) {
        printf("Le programme a été exécuté avec succès.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <fichier_terrain> <fichier_programme>\n", argv[0]);
        return 1;
    }

    // Tester le programme avec les fichiers fournis en argument
    tester_programme(argv[1], argv[2]);

    return 0;
}
