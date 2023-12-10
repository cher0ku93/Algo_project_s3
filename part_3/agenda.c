//
// Created by Ilyès, Diaby, Hippolyte
//

#include "agenda.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//Pour vider le tampon et éviter les parasites de mêmoire pas vider//
void vide_tampon(){
    // Consommer les caractères restants dans le tampon d'entrée
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Pour rentrer le nom et le prénom
char *scanString(void) {
    char buffer[100];
    scanf("%99s", buffer); // Limitation pour éviter les débordements
    char *input = malloc(strlen(buffer) + 1); // Allouer de la mémoire pour la chaîne
    strcpy(input, buffer); // Copier la chaîne dans la mémoire allouée
    return input;
}


// Fonction pour créer un contact
contact creer_contact() {
    contact newContact;
    printf("\n---Création d'une fiche contact---\n");
    printf("\nEntrez le nom : ");
    newContact.nom = scanString();
    printf("\nEntrez le prénom : ");
    newContact.prenom = scanString();
    newContact.racine = NULL;
    return newContact;
}



// Fonction pour créer un rendez-vous
r_d_v creer_r_d_v() {

    r_d_v nv_r_d_v; //nv_r_d_v = 'nouveau rendez-vous'

    printf("\n---Création d'un rendez-vous---\n");

    printf("\nEntrez le jour du rendez-vous: ");
    scanf("%d", &nv_r_d_v.jour);

    printf("\nEntrez son mois : ");
    scanf("%d", &nv_r_d_v.mois);

    printf("\nEntrez son année : ");
    scanf("%d", &nv_r_d_v.annee);

    printf("\nEntrez l'heure du rendez-vous (format 24 heures) : ");
    scanf("%d", &nv_r_d_v.heure_r_d_v);

    printf("\nEntrez les minutes du rendez-vous : ");
    scanf("%d", &nv_r_d_v.minute_r_d_v);

    printf("Entrez la durée en heures du rendez-vous : ");
    scanf("%d", &nv_r_d_v.duree_h);

    printf("Entrez la durée en minutes du rendez-vous : ");
    scanf("%d", &nv_r_d_v.duree_m);

    printf("Entrez l'objet du rendez-vous : ");
    nv_r_d_v.objet = scanString();


    return nv_r_d_v;
}

void ajouter_r_d_v(contact* contact) {

    printf("Ajout d'un nouveau rendez-vous:\n");
    r_d_v nv_r_d_v = creer_r_d_v(); // Obtient le nouveau rendez-vous

    // Création d'une nouvelle cellule pour le rendez-vous
    p_cell_r_d_v   nv_cell_r_d_v = (p_cell_r_d_v)malloc(sizeof(cell_r_d_V));


    if (nv_cell_r_d_v == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }


    nv_cell_r_d_v->r_d_v = nv_r_d_v;
    nv_cell_r_d_v->next = NULL;

    if (contact->racine == NULL || (contact->racine->r_d_v.annee > nv_r_d_v.annee) ||
        (contact->racine->r_d_v.annee == nv_r_d_v.annee && contact->racine->r_d_v.mois > nv_r_d_v.mois) ||
        (contact->racine->r_d_v.annee == nv_r_d_v.annee && contact->racine->r_d_v.mois == nv_r_d_v.mois && contact->racine->r_d_v.jour > nv_r_d_v.jour) ||
        (contact->racine->r_d_v.annee == nv_r_d_v.annee && contact->racine->r_d_v.mois == nv_r_d_v.mois && contact->racine->r_d_v.jour == nv_r_d_v.jour &&
         (contact->racine->r_d_v.heure_r_d_v > nv_r_d_v.heure_r_d_v || (contact->racine->r_d_v.heure_r_d_v == nv_r_d_v.heure_r_d_v && contact->racine->r_d_v.minute_r_d_v > nv_r_d_v.minute_r_d_v)))) {
        nv_cell_r_d_v->next = contact->racine;
        contact->racine = nv_cell_r_d_v;
    } else {
        p_cell_r_d_v current = contact->racine;
        p_cell_r_d_v previous = NULL;

        // Parcours de la liste pour trouver l'emplacement adéquat
        while (current != NULL&& (current->r_d_v.annee < nv_r_d_v.annee || current->r_d_v.annee == nv_r_d_v.annee && current->r_d_v.mois < nv_r_d_v.mois) ||
               (current->r_d_v.annee == nv_r_d_v.annee && current->r_d_v.mois == nv_r_d_v.mois && current->r_d_v.jour < nv_r_d_v.jour) ||
               (current->r_d_v.annee == nv_r_d_v.annee && current->r_d_v.mois == nv_r_d_v.mois && current->r_d_v.jour == nv_r_d_v.jour &&
                (current->r_d_v.heure_r_d_v < nv_r_d_v.heure_r_d_v || (current->r_d_v.heure_r_d_v == nv_r_d_v.heure_r_d_v && current->r_d_v.minute_r_d_v < nv_r_d_v.minute_r_d_v)))) {
            previous = current;
            current = current->next;
        }

        nv_cell_r_d_v->next = current;
        previous->next = nv_cell_r_d_v;
    }
}


void afficher_r_v(contact contact) {
    p_cell_r_d_v current = contact.racine;

    if (current == NULL) {
        printf("Ce contact n'a pas de rendez-vous.\n");
        return;
    }

    printf("Rendez-vous pour %s %s :\n", contact.prenom, contact.nom);

    while (current != NULL) {
        printf("Date : %02d/%02d/%d\n", current->r_d_v.jour, current->r_d_v.mois, current->r_d_v.annee);
        printf("Heure : %02d:%02d\n", current->r_d_v.heure_r_d_v, current->r_d_v.minute_r_d_v);
        printf("Durée : %d:%02d\n", current->r_d_v.duree_h, current->r_d_v.duree_m);
        printf("Objet : %s\n", current->r_d_v.objet);
        printf("\n");
        current = current->next;
    }
}

