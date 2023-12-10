//
// Created by Ilyès, Diaby, Hippolyte
//

#include "agenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Pour rentrer le nom et le prénom
char *scanString(void) {
    char buffer[100];
    scanf("%99s", buffer); // Limitation pour éviter les débordements
    char *input = malloc(strlen(buffer) + 1); // Allouer de la mémoire pour la chaîne
    strcpy(input, buffer); // Copier la chaîne dans la mémoire allouée
    return input;
}

ListContacts *createList3(int max_l) {
    // Allocation de mémoire pour la nouvelle liste :
    ListContacts *new_list = (ListContacts *)malloc(sizeof(ListContacts));

    // Si la liste est correctement créée :
    if (new_list != NULL) {
        new_list->max_levels = max_l;
        new_list->head = NULL; // On initialise la tête de la liste à NULL

        return new_list;
    }

    // Sinon :
    printf("Erreur d'allocation mémoire pour la liste..");
    free(new_list);
    exit(EXIT_FAILURE);
}


// Fonction pour créer un contact
Contact createContact() {
    Contact newContact;
    printf("Entrez le nom du contact : ");
    newContact.nom = scanString();
    printf("Entrez le prénom du contact : ");
    newContact.prenom = scanString();
    newContact.rdv_list = NULL;
    return newContact;
}

// Fonction pour ajouter un contact à la fin de la liste
void addContactToList(ListContacts *list, Contact newContact) {
    // Création d'une nouvelle cellule pour le contact
    t_d_cell2 *newCell = (t_d_cell2 *)malloc(sizeof(t_d_cell2));
    if (newCell == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }

    // Copie du nouveau contact dans la cellule
    newCell->contact = newContact;
    newCell->next = NULL;

    // Si la liste est vide, la nouvelle cellule devient la tête de la liste
    if (list->head == NULL) {
        list->head = newCell;
    } else {
        // Sinon, parcourir la liste pour trouver la dernière cellule et ajouter la nouvelle cellule à la fin
        t_d_cell2 *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCell;
    }
}
// Fonction pour ajouter un nouveau rendez-vous à un contact
void create_rdv(Contact *contact) {
    printf("Ajout d'un nouveau rdv:\n");
    Rdv newRdv;

    // Saisie des informations pour le nouveau rendez-vous
    printf("Entrez le jour du rendez-vous : ");
    scanf("%d", &newRdv.date_rdv.jour);

    printf("Entrez le mois du rendez-vous : ");
    scanf("%d", &newRdv.date_rdv.mois);

    printf("Entrez l'année du rendez-vous : ");
    scanf("%d", &newRdv.date_rdv.annee);

    printf("Entrez l'heure du rendez-vous (format 24 heures) : ");
    scanf("%d", &newRdv.date_rdv.heure);

    printf("Entrez les minutes du rendez-vous : ");
    scanf("%d", &newRdv.date_rdv.minute);

    printf("Entrez la durée en heures du rendez-vous : ");
    scanf("%d", &newRdv.duree_h);

    printf("Entrez la durée en minutes du rendez-vous : ");
    scanf("%d", &newRdv.duree_m);

    printf("Entrez l'objet du rendez-vous : ");
    newRdv.objet = scanString();

    // Création d'une nouvelle cellule pour le rendez-vous
    Rdv *newRdvCell = (Rdv *)malloc(sizeof(Rdv));
    if (newRdvCell == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }
    *newRdvCell = newRdv;
    newRdvCell->next = NULL;

    // Si la liste est vide ou le premier rendez-vous est postérieur au nouveau rendez-vous
    if (contact->rdv_list == NULL ||
        (contact->rdv_list->date_rdv.annee > newRdv.date_rdv.annee) ||
        (contact->rdv_list->date_rdv.annee == newRdv.date_rdv.annee &&
        contact->rdv_list->date_rdv.mois > newRdv.date_rdv.mois) ||
        (contact->rdv_list->date_rdv.annee == newRdv.date_rdv.annee
        && contact->rdv_list->date_rdv.mois == newRdv.date_rdv.mois
        && contact->rdv_list->date_rdv.jour > newRdv.date_rdv.jour) ||
        (contact->rdv_list->date_rdv.annee == newRdv.date_rdv.annee
        && contact->rdv_list->date_rdv.mois == newRdv.date_rdv.mois
        && contact->rdv_list->date_rdv.jour == newRdv.date_rdv.jour &&
         (contact->rdv_list->date_rdv.heure > newRdv.date_rdv.heure
         || (contact->rdv_list->date_rdv.heure == newRdv.date_rdv.heure
         && contact->rdv_list->date_rdv.minute > newRdv.date_rdv.minute)))) {
        newRdvCell->next = contact->rdv_list;
        contact->rdv_list = newRdvCell;
    } else {
        Rdv *current = contact->rdv_list;
        Rdv *previous = NULL;

        // Parcours de la liste pour trouver l'emplacement adéquat
        while (current != NULL && (current->date_rdv.annee < newRdv.date_rdv.annee ||
                                   (current->date_rdv.annee == newRdv.date_rdv.annee
                                   && current->date_rdv.mois < newRdv.date_rdv.mois) ||
                                   (current->date_rdv.annee == newRdv.date_rdv.annee
                                   && current->date_rdv.mois == newRdv.date_rdv.mois
                                   && current->date_rdv.jour < newRdv.date_rdv.jour) ||
                                   (current->date_rdv.annee == newRdv.date_rdv.annee
                                   && current->date_rdv.mois == newRdv.date_rdv.mois
                                   && current->date_rdv.jour == newRdv.date_rdv.jour &&
                                    (current->date_rdv.heure < newRdv.date_rdv.heure
                                    || (current->date_rdv.heure == newRdv.date_rdv.heure
                                    && current->date_rdv.minute < newRdv.date_rdv.minute))))) {
            previous = current;
            current = current->next;
        }

        newRdvCell->next = current;
        previous->next = newRdvCell;
    }
}

// Fonction pour rechercher un contact par son nom//
Contact *searchContact(ListContacts *list) {
    if (list == NULL || list->head == NULL) {
        // La liste est vide
        return NULL;
    }

    printf("Entrez le nom du contact à rechercher : ");
    char *searchName = scanString();

    // Parcourir la liste à partir de la tête
    struct t_d_cell *current = list->head;
    while (current != NULL) {
        // Utilisation de strcmp pour comparer les caractères, cela nous évite d'écrire une fonction
        //sachant que strcmp nous est fourni dans la librairie.
        if (strcmp(current->contact.nom, searchName) == 0) {
            free(searchName);
            return &(current->contact);
        }

        // Passer à la cellule contact suivante dans la liste
        current = current->next;
    }

    // Aucun contact trouvé avec le nom spécifié
    free(searchName); // Libérer la mémoire allouée pour le nom de recherche
    return NULL;
}


/*
// Fonction pour afficher la liste de contacts par niveau
void displayContactList(ListContacts *list) {
    if (list == NULL || list->head == NULL) {
        // La liste est vide
        printf("La liste de contacts est vide.\n");
        return;
    }

    // Parcourir la liste et afficher chaque contact avec ses rendez-vous
    t_d_cell2 *current = list->head;
    while (current != NULL) {
        // Afficher le contact
        printf("[ %s %s ] --> ", current->contact.nom, current->contact.prenom);

        // Afficher les rendez-vous pour ce contact
        Rdv *rdv_current = current->contact.rdv_list;
        printf("\n");
        while (rdv_current != NULL) {
            printf("[ %02d/%02d/%d %02d:%02d %d:%02d %s ] --> ",
                   rdv_current->date_rdv.jour, rdv_current->date_rdv.mois,
                   rdv_current->date_rdv.annee, rdv_current->date_rdv.heure,
                   rdv_current->date_rdv.minute, rdv_current->duree_h,
                   rdv_current->duree_m, rdv_current->objet);

            // Passer au rendez-vous suivant
            rdv_current = rdv_current->next;
        }

        // Passer à la cellule contact suivante dans la liste
        current = current->next;
    }

    // Afficher NULL pour indiquer la fin de la liste
    printf("NULL\n");
}
*/

// Fonction pour afficher la liste de contacts par niveau
void displayContactList(ListContacts *list) {
    if (list == NULL || list->head == NULL) {
        // La liste est vide
        printf("La liste de contacts est vide.\n");
        return;
    }

    // Parcourir la liste et afficher chaque contact avec ses rendez-vous
    t_d_cell2 *current = list->head;
    while (current != NULL) {
        // Afficher le contact
        printf("[ %s %s ] --> \n", current->contact.nom, current->contact.prenom);

        // Afficher les rendez-vous pour ce contact en colonne
        Rdv *rdv_current = current->contact.rdv_list;
        while (rdv_current != NULL) {
            printf("    [ Date: %02d/%02d/%d, Heure: %02d:%02d, Durée: %d:%02d, Objet: %s ]\n",
                   rdv_current->date_rdv.jour, rdv_current->date_rdv.mois,
                   rdv_current->date_rdv.annee, rdv_current->date_rdv.heure,
                   rdv_current->date_rdv.minute, rdv_current->duree_h,
                   rdv_current->duree_m, rdv_current->objet);

            // Passer au rendez-vous suivant
            rdv_current = rdv_current->next;
        }

        // Passer à la cellule contact suivante dans la liste
        current = current->next;
    }

    // Afficher NULL pour indiquer la fin de la liste
    printf("NULL\n");
}



