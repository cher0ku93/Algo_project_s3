//
// Created by Ilyès, Diaby, Hippolyte
//

#include "menu_one.h"
#include "menu_three.h"
#include "menu_two.h"
#include <stdio.h>
#include <stdlib.h>

t_d_list  *mylist;
char buffer[100];

void back1(){
    menu1();
}


//Menu projet//
    void menu_principal() {
        int part = 0;

        printf("\nQuel partie du projet souhaitez-vous lancer ?\n");
        printf("-------------------------------------------------");
        printf("\n-> Partie I\n\t-> Partie II\n\t\t-> Partie III\n");
        printf("-------------------------------------------------\n");
        printf("\nPour quitter le programme entrez 0.\n");
        printf("\nVotre choix (0,1,2,3) : ");

        fflush(stdin);//On vide le buffer pour éviter les parasites
        do {
            fgets(buffer, sizeof(buffer), stdin);
            if (sscanf(buffer, "%d", &part) != 1) {
                printf("Merci de faire une saisie correcte -> ");
            }
        } while (sscanf(buffer, "%d", &part) != 1);

        if (part == 0) {
            printf("\nArrêt du programme...\n");
            printf("Au revoir !\n");
            exit(EXIT_SUCCESS);
        }

        switch (part) {
            case 1 : {
                menu1();
                break;
            }
            case 2 : {
                menu2();
                break;
            }
            case 3 : {
                menu3();
                break;
            }
            default: {
                printf("\nChoix incorrect !\n");
                menu_principal();
            }

        }
    }



//Menu permettant création cellule + listes//
    int menu1() {

        int choice;


        printf("\n------Partie 1------\n");

        printf("\n1. Créer une liste à niveau.\n");
        printf("2. Créer puis ajouter une cellule.\n");
        printf("3. Afficher les cellules d'un niveau.\n");
        printf("4. Afficher la liste complète.\n");
        printf("5. Supprimer la liste enregistrée\n");
        printf("6. Menu précédent\n");
        printf("\nVotre choix : ");


        do {
            fgets(buffer, sizeof(buffer), stdin);
            if (sscanf(buffer, "%d", &choice) != 1) {
                printf("Merci de faire une saisie correcte -> ");
                continue;  // Recommence la boucle
            }
        } while (sscanf(buffer, "%d", &choice) != 1);


        switch (choice) {
            case 1: {

                int niveau;

                printf("\n---Création d'une liste---\n");

                if (mylist != NULL) {
                    printf("Liste déjà créée :)");
                    back1();
                } else {
                    printf("Saisir le niveau de la liste : ");

                    do {
                        fgets(buffer, sizeof(buffer), stdin);
                        if (sscanf(buffer, "%d", &niveau) != 1) {
                            printf("\n Merci de saisir un entier : ");
                            continue;  // Recommence la boucle
                        }
                    } while (sscanf(buffer, "%d", &niveau) != 1);
                    mylist = createList(niveau);
                    printf("\nListe créée avec succès : \n");
                    display_list(*mylist);
                    menu1();
                }
                break;
            }
            case 2: {

                if (mylist == NULL) {
                    printf("\nAttention, vous n'avez pas de listes...\nCommencez par créer une liste avec des niveaux :) !\n");
                    menu1();
                } else {
                    create_and_add_cell_sorted(mylist);
                    printf("\nVoici votre nouvelle liste mise à jour : \n");
                    display_list(*mylist);
                    menu1();
                }
                break;
            }
            case 3: {
                int niveau;
                if (mylist == NULL) {
                    printf("\nAttention, vous n'avez pas de listes...\nCommencez par créer une liste avec des niveaux :) !\n");
                    menu1();
                } else {
                    printf("Saisir le niveau de la liste que vous souhaitez afficher : ");

                    do {
                        fgets(buffer, sizeof(buffer), stdin);
                        if (sscanf(buffer, "%d", &niveau) != 1) {
                            printf("\n Merci de saisir un entier : ");
                            continue;  // Recommence la boucle
                        }
                    } while (sscanf(buffer, "%d", &niveau) != 1);
                    printLevel(*mylist, niveau);
                    menu1();
                }
                break;
            }
            case 4 : {
                printf("\n---Affichage de la liste---\n");
                if (mylist == NULL) {
                    printf("\nAttention, vous n'avez pas de listes...\nCommencez par créer une liste avec des niveaux :) !\n");
                    menu1();
                }
                display_list(*mylist);
                menu1();
            }
            case 5 : {
                printf("%d",mylist->max_levels);
                if (mylist == NULL) {
                    printf("\nAttention, vous n'avez pas de listes...\nCommencez par créer une liste avec des niveaux :) !\n");
                    menu1();
                }
                printf("\nSuppression de la liste en cours...");
                suppression_list(&mylist);
                printf("\nListe supprimée");
                back1();
            }
            case 6 : {
                menu_principal();
                vide_tampon();
            }


            default: {
                printf("Erreur de choix");
                menu1();
            }
        }

        return 0;
    }