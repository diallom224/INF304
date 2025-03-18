#ifndef _PROGRAMME_H_
#define _PROGRAMME_H_

#define PROG_TAILLE_MAX 10000

typedef enum {
  Avancer,
  Gauche,
  Droite,
  Mesure,
  Marque,
  DebutBloc,
  FinBloc,
  EmpilerNb,
  ExecBloc,
  CondExec,
  Echange,
  Mult,
  Add,
  Div,
  Sub,
  Rotation,
  Clone,
  Boucle,
  Ignore
} Type_Commande;

typedef struct {
  Type_Commande cmd;
  int aux;
} Commande;

typedef struct {
  Commande tab[PROG_TAILLE_MAX];
  int lg;
} Programme;

typedef enum {
  PROGRAMME_OK,
  PROGRAMME_ERREUR_FICHIER,
  PROGRAMME_ERREUR_BLOC_NON_FERME,
  PROGRAMME_ERREUR_FERMETURE_BLOC_EXCEDENTAIRE,
  PROGRAMME_ERREUR_COMMANDE_INCORRECTE
} type_erreur_programme;

typedef struct {
  type_erreur_programme type_err;
  char *ligne;
  int num_ligne, num_colonne;
} erreur_programme;

erreur_programme lire_programme(Programme *prog, char *nom_fichier);

#endif
