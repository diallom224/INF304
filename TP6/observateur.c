#include "observateur.h"

/* Renvoie l'état initial de l'automate */
Etat Etat_initial() {
    return Init; 
}

/* Fonction de transition des automates */
Etat Etat_transition(Etat e, Alphabet c) {
    switch (e) {
        case Init:
            switch(c) {
                case A: 
                    return Erreur;
                case G: 
                case D:
                    return Init;
                case M:
                    return Mes;
            }
            break; 
        case Mes:
            switch (c) {
                case A: 
                case G: 
                case D:
                    return Init;
                case M:
                    return Mes;  
            }
            break; 
        case Erreur:
            return Erreur;
    }   
    return Erreur;  
}

/* Vérifie si un état est final */
int est_final(Etat e) {
    return e != Erreur;
}
