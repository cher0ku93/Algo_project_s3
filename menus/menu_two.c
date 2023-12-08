//
// Created by Ilyès, Diaby, Hippolyte
//


//-----------------//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//-----------------//
#include "menu_two.h"
#include "menu_one.h"
//-----------------//
#include "../part_2/timer.h"
#include "math.h"


void back(){
    menu2();
}


t_d_list  *mylist2;
char buffer2[100];


int menu2() {

    int choice;

    printf("\n------Partie 2------\n");
    printf("\n1. Créer une liste ");
    printf("\n2. Recherche dans le niveau 0 ");
    printf("\n3. Recherche à partir du niveau le plus haut");
    printf("\n4. Timer");
    printf("\n5. Supprimer la liste enregistrée");
    printf("\n6. Menu principal\n");
    printf("\nVotre choix : ");


    do {
        fgets(buffer2, sizeof(buffer2), stdin);
        if (sscanf(buffer2, "%d", &choice) != 1) {
            printf("Merci de faire une saisie correcte -> ");
            continue;
        }

    } while (sscanf(buffer2, "%d", &choice) != 1);

    fflush(stdout);

    int level = 0;
    int i;

    switch (choice) {

        case 1: {

            int *levels;

            if (mylist2 != NULL) {
                printf("\nListe déjà créée :)\n");
                menu2();
            }

            printf("Saisir la nombre de niveaux de votre liste : ");
            level = saisie_secur();

            while (level < 0) {
                printf("doit etre sup à 0");
                level = saisie_secur();
            }

            //Création de la liste:
            mylist2 = createList(level);
            mylist2->max_levels = level;
            levels = createLevels2(level);

            //Insertion en tête dans la liste :
            for (i = 0; i <pow(2,mylist2->max_levels)-1; i++) {
                insertList(mylist2, i + 1, levels[i] + 1);
            }
            //Affichage de la liste:
            printf("\n");
            display_list(*mylist2);
            printf("\n");
            menu2();
        }

        case 2 : {

            if (mylist2 == NULL) {
                printf("\nAttention, vous n'avez pas de listes...\nCommencez par créer une liste avec des niveaux :) !\n");
                menu1();
            }

            int val, res;

            printf("\nEntrez la valeur à rechercher dans le niveau 0 : ");
            val = saisie_secur();

            res = recherche_niveau0(val, *mylist2, 0);

            if (res == 1) {
                printf("La valeur %d est bien présente au niveau 0 !", val);
                back();
            }
            printf("La valeur %d n'est pas présente au niveau 0. ", val);

            back();
            fflush(stdin);
            fflush(stdout);
            break;
        }
        case 3: {
            if (mylist2 == NULL) {
                printf("\nAttention, vous n'avez pas de listes...\nCommencez par créer une liste avec des niveaux :) !\n");
                menu2();
            }
            int val;
            int res;
            printf("\nEntrez la valeur à rechercher : ");
            val = saisie_secur();

            res = recherche_dicho(*mylist2, mylist2->max_levels, val);
            if (res == 1) {
                printf("Valeur trouvée par la dichotomie\n");
                back();
            } else {
                printf("Valeur inexistante dans l'ensemble des listes\n");
                back();
            }
        }

        case 4:{

            printf("\n----Recherche avec timer----\n");

            FILE *log_file = fopen("../part_2/log.txt", "w");
            char format[] = "%d\t%s\t%s\n";
            char *time_lvl0;
            char *time_all_levels;

            srand((unsigned int)time(NULL));


            int nb_level, current;
            int *levels;

            printf("Choisissez le nombre de niveau : ");
            scanf("%d", &nb_level);
            while (nb_level < 1) {
                printf("Le nombre de niveau doit être supérieur à 0 : ");
                scanf("%d", &nb_level);
            }

            mylist2 = createList(nb_level);
            mylist2->max_levels = ((int)pow(2, nb_level) - 1);

            levels = createLevels2(nb_level);

            // Affichage des niveaux testés :
            for (int a = 0; a < nb_level; a++) {
                printf("Niveau %d testé\n", a);

                for (current = 0; current < (pow(2, nb_level) - 1); current++) {
                    insertList(mylist2, current + 1, levels[current] + 1);
                }
                startTimer();

                // Recherche au niveau 0
                printf("Resultat pour la recherche au niveau 0 :\n");
                for (int n = 1000; n <= 100000; n *= 10) {
                    printf("-Pour %d valeurs : ", n);
                    startTimer();
                    int w;
                    for (int k = 0; k < n; k++) {
                        w = rand() % ((int)pow(2, nb_level) - 1);
                        recherche_niveau0(w, *mylist2, 0);
                    }
                    stopTimer();
                    displayTime();
                    printf("\n");
                }
                time_lvl0 = getTimeAsString();

                // Recherche multi-niveaux
                printf("Resultat pour la recherche dichotomique :\n");
                for (int n = 1000; n <= 100000; n *= 10) {
                    printf("-Pour %d valeurs : ", n);
                    startTimer();
                    int w;
                    for (int k = 0; k < n; k++) {
                        w = rand() % ((int)pow(2, nb_level) - 1);
                        recherche_dicho(*mylist2, nb_level, w);
                    }
                    stopTimer();
                    displayTime();
                    printf("\n");
                }
                time_all_levels = getTimeAsString();

                fprintf(log_file, format, a, time_lvl0, time_all_levels);
                stopTimer();
                printf("\n");
            }

            fclose(log_file);
            fflush(stdin);
            fflush(stdout);
            menu2();
            break;

        }
        case 5: {
            if (mylist2 == NULL) {
                printf("\nAttention, vous n'avez pas de listes...\nCommencer par créer une liste avec des niveaux :) !\n");
                menu2();
            }
            printf("\nSuppression de la liste en cours...");
            suppression_list2(&mylist2, level);
            printf("\nListe supprimée\n");
        }
        case 6 : {
            menu_principal();
        }
        default: {
            printf("Erreur de choix");
            menu2();
        }
    }
    return 0;
}
