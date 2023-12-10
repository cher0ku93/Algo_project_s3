//
// Created by Ilyès, Diaby, Hippolyte
//

#ifndef PROJET_S3_AGENDA_H
#define PROJET_S3_AGENDA_H


// Structure pour la date
typedef struct {
    int jour;
    int mois;
    int annee;
    int heure;
    int minute;
} Date;

// Structure pour un rendez-vous
struct Rdv {
    Date date_rdv;
    int duree_h; // Durée en heures du rendez-vous
    int duree_m; // Durée en minutes du rendez-vous
    char *objet;
    struct Rdv *next;
};

typedef struct Rdv Rdv;

// Structure pour un contact
struct Contact {
    char *nom;
    char *prenom;
    Rdv *rdv_list; // Liste de rendez-vous pour le contact
};

typedef struct Contact Contact;

// Structure pour une cellule contact dans la liste
struct t_d_cell {
    Contact contact;
    struct t_d_cell *next; // Contact suivant dans la liste
};

typedef struct t_d_cell t_d_cell2;

// Structure pour une liste de contacts
struct ListContacts {
    t_d_cell2 *head;
    int max_levels;
};

typedef struct ListContacts ListContacts;

ListContacts *createList3(int max_l);

Contact createContact();

void addContactToList(ListContacts *list, Contact newContact);

void create_rdv(Contact *contact);

Contact *searchContact(ListContacts *list);

void displayContactList(ListContacts *list);


#endif //PROJET_S3_AGENDA_H
