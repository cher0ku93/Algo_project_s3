//
// Created by Ilyès K on 08/12/2023.
//

#ifndef PROJET_S3_AGENDA_H
#define PROJET_S3_AGENDA_H

#include "../menus/menu_three.h"

// Structure pour stocker les informations d'un contact


//  Champs d'un rdv
typedef struct {
    int jour;
    int mois;
    int annee;
    int heure_r_d_v;
    int minute_r_d_v;
    int duree_h;
    int duree_m;
    char *objet;
} r_d_v;

// Cellule rdv pour LLC
struct rdv_cell {
    r_d_v r_d_v;
    r_d_v * next;
};
typedef struct rdv_cell cell_r_d_V, *p_cell_r_d_v;


// Structure contact
typedef struct {
    char *nom;
    char *prenom;
    p_cell_r_d_v racine;
} contact;



// Prototype

contact creer_contact();
void ajouter_r_d_v(contact* contact);
r_d_v creer_r_d_v();
void afficher_r_d_v(contact contact);
void supprimer_r_d_v(contact* contact);

void vide_tampon();

#endif //PROJET_S3_AGENDA_H
