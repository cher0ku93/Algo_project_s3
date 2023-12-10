//
// Created by Ilyès, Diaby, Hippolyte
//

#include "menu_three.h"
#include "../part_3/agenda.h"
#include "../menus/menu_one.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

ListContacts *myList ;

int menu3(){
    char buffer[100];

    printf("\n------Partie 3------\n");
    printf("\n1. Créer ma liste de contacts");
    printf("\n2. Créer un contact");
    printf("\n3. Ajouter un rendez-vous");
    printf("\n4. Afficher un contact");
    printf("\n5. Supprimer un contact");
    printf("\n6. Retour au menu principal\n");


    int choice;

    printf("\nVotre choix :");

    do {
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &choice) != 1) {
            printf("Merci de faire une saisie correcte -> ");
            continue;  // Recommence la boucle
        }
    } while (sscanf(buffer, "%d", &choice) != 1);

    switch (choice){
        case 1 : {
            int nb_rdv;

            printf("\nCombien de rendez-vous maximum souhaitez vous pour vos contacts ?\nVotre choix : ");

            do {
                nb_rdv = saisie_secur();
            }while(nb_rdv==0);
            myList = createList3(nb_rdv);
            menu3();
        }
        case 2:{
            if (myList == NULL) {
                printf("\nAttention, vous n'avez pas de listes...\nCommencez par créer une liste de contacts :) !\n");
                menu3();
            } else {
                printf("\n---Création d'un contact---\n");
                Contact newcontact = createContact();
                addContactToList(myList, newcontact);
                fflush(stdin);
                fflush(stdout);
                menu3();
            }
        }
        case 3:{
            if (myList == NULL) {
                printf("\nAttention, vous n'avez pas de listes...\nCommencez par créer une liste de contacts :) !\n");
                menu3();
            } else {
                printf("\n---Ajout d'un Rendez-vous---\n");
                displayContactList(myList);
                Contact *to_find;
                to_find = searchContact(myList);
                if (to_find!=NULL){
                    create_rdv(to_find);
                }
                else{
                    printf("\nZut ! Votre contact n'existe pas. ");
                }
                fflush(stdin);
                fflush(stdout);
                menu3();
            }
        }
        case 6 : {
            menu_principal();
        }
        default: {
            printf("\nChoix incorrect ou partie non terminée\n");
            menu_principal();
        }
    }
    return 0;
}
