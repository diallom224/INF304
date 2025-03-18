#ifndef _OBSERVATEUR_H_
#define _OBSERVATEUR_H_

typedef enum {A, G, D, M} Alphabet;   
typedef enum {Init, Mes, Erreur} Etat; 

/* Renvoie l'état initial de l'automate */
Etat Etat_initial(void);

/* Fonction de transition des automates */
Etat Etat_transition(Etat e, Alphabet c);

/* Vérifie si un état est final */
int est_final(Etat e);



#endif
