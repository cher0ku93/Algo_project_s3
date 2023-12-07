//
// Created by Ilyès K on 03/12/2023.
//

#include "listes.h"
#include <stdio.h>
#include <stdlib.h>

t_d_list *createList(int max_l){
    //Allocation de la mémoire pour la nouvelle liste :
    t_d_list *new_list = (t_d_list*) malloc(sizeof(t_d_list));

    //Si liste correctement créée :
    if(new_list!=NULL){
        new_list->max_levels = max_l;
        new_list->heads = (t_d_cell**)malloc(max_l*sizeof (t_d_cell*));
        //Initialisation des heads à NULL :1
        for(int i = 0; i<max_l; i++){
            new_list->heads[i] = NULL;}
        return new_list;
    }

    //Sinon :
    printf("Erreur d'allocation mémoire pour la liste..");
    free(new_list);
    exit(EXIT_FAILURE);
}



// Insertion d'une cellule dans une liste à plusieurs niveaux tout en maintenant l'ordre croissant
void add_cell_sorted(t_d_cell *cell, t_d_list *list) {
    // Vérifier si la liste et la cellule ont été correctement allouées
    if (list == NULL || cell == NULL || cell->lev_max > list->max_levels) {
        printf("Erreur : Liste/cellule invalide ou valeur maximum de niveau saisie supérieur à la valeur maximum de la liste\n");
        return;
    }

    // Parcourir chaque niveau de la liste
    for (int i = 0; i < list->max_levels && i <= cell->lev_max; i++) {
        t_d_cell **head = &(list->heads[i]);

        // Parcourir la liste jusqu'à trouver la bonne position pour insérer la cellule
        while (*head != NULL && (*head)->value <= cell->value) {
            // Autoriser les doublons en vérifiant la différence
            if ((*head)->value == cell->value) {
                break;  // Sortir si la valeur est identique (doublon)
            }
            head = &((*head)->next[i]);
        }

        // Insérer la cellule à la position appropriée pour le niveau actuel
        cell->next[i] = *head;
        *head = cell;
    }
}

// Fonction sécurisée accompagnée grâce au buffer qui permet la création et l'ajout direct dans une liste à niveaux tout en maintenant l'ordre croissant
void create_and_add_cell_sorted(t_d_list *list) {
    int valeur, niveau;
    char buffer[100];

    printf("---Création et ajout d'une cellule---\n");
    printf("Merci de saisir la valeur de la cellule :\n");

    // Utilisation du buffer et boucle pour éviter le débordement et la saisie incorrecte
    fflush(stdin); // On vide le buffer pour éviter les parasites

    do {
        printf("\tSaisir un entier : ");
        fgets(buffer, sizeof(buffer), stdin);
    } while (sscanf(buffer, "%d", &valeur) != 1);

    printf("Merci de saisir le niveau de la cellule :\n");

    do {
        printf("\tSaisir un niveau : ");
        fgets(buffer, sizeof(buffer), stdin);

        // On vérifie que la saisie est un entier
        if (sscanf(buffer, "%d", &niveau) != 1) {
            printf("Merci de faire une saisie correcte.\n");
        }
    } while ((niveau < 0) || (niveau > list->max_levels) || (sscanf(buffer, "%d", &niveau) != 1));

    // Création de la cellule et ajout en maintenant l'ordre croissant
    t_d_cell *newcell = create_cell(valeur, niveau);
    add_cell_sorted(newcell, list);
}


void printLevel(t_d_list list, int level)
{
    // Vérifier si le niveau est invalide
    if (level < 0 || level >= list.max_levels)
    {
        // Afficher un message d'erreur
        fprintf(stderr, "Le niveau saisie n'existe pas\n");
        return;  // Sortir de la fonction si le niveau est invalide
    }

    // Afficher le début de la liste pour le niveau spécifié
    printf("[list head%d @-] --> ", level);

    // Initialiser le pointeur au début de la liste pour le niveau spécifié
    t_d_cell *current = list.heads[level];

    // Parcourir la liste et afficher chaque élément
    while (current != NULL)
    {
        // Afficher la valeur de la cellule
        printf("[ %d|@-] --> ", current->value);

        // Passer à la cellule suivante dans le niveau
        current = current->next[level];
    }

    // Afficher NULL pour indiquer la fin de la liste pour ce niveau
    printf("NULL\n");
}


//Affichage de la liste//
void display_list(t_d_list list) {

    printLevel(list, 0);//Affichage de la première ligne comme base

    //Boucle for pour aller du niveau 0 au dernier niveau:
    for (int i = 1; i < list.max_levels ; i++) {
        t_d_cell *curr = list.heads[0];//cellule repère initalisée à l'indice 0 du tableau de cellules//
        t_d_cell *curr_level = list.heads[i];//cellule permettant de se situer dans les niveaux en fct de la boucle for//
        printf("[list head%d @-] ", i);
        //Tant que la LLC n'est pas nulle :
        while (curr != NULL) {
            //si la valeur actuelle n'est pas nulle et qu'elle est égale à la valeur du niveau précédent alors :
            if (curr_level != NULL && curr->value == curr_level->value) {
                printf("--> [ %d|@-] ", curr_level->value);
                curr_level = curr_level->next[i];
            } else {
                printf("------------");//si non affichage de l'espacement
            }
            curr = curr->next[0];//passage à la prochaine cellule
        }
        printf("--> NULL\n");
    }
    return;

}










//Recherche simple 0//

int isInList(int val, t_d_list list, int level){
    p_cell temp = list.head[level];
    while (temp != NULL && temp->value <= val) {
        if (temp->value == val) {
            return 1;
        }
        temp = temp->next[level];
    }
    return 0;
}

//Rercherche dichotomique//

int recherche_dicho(t_d_list mylist, int levelmax, int val)
{
    p_cell temp, prev;
    int i=2;
    int j=1;
    temp = mylist.head[levelmax-1];
    while (temp!=NULL && i<=levelmax+1)
    {
        if (temp->value == val)
        {
            return 1;
        }
        else if (temp->value >val && temp == mylist.head[levelmax-j])
        {
            temp = mylist.head[levelmax-i];
            i++;
            j++;
        }
        else if (val > temp->value)
        {
            prev=temp;
            temp = temp->next[levelmax-i];
            i++;
        }
        else
        {
            temp=prev->next[levelmax-i];
            i++;
        }
    }
    return 0;
}


//timer//

int nb_level, i = 0;
    //t_d_list list;
    int *levels;

    printf("Choisissez le nombre de niveau : ");
    scanf("%d", &nb_level);
    while (nb_level < 1) {
        printf("Le nombre de niveau doit être supérieur à 0 : ");
        scanf("%d", &nb_level);
    }
    list = CreateEmptyList(nb_level);
    list.max_cell = (pow(2, nb_level) - 1);

    levels = createLevels(nb_level, list.max_cell);

    for (i = 0; i < list.max_cell; i++) {
        insertList(&list, i + 1, levels[i] + 1);
    }

    printf("\n");
printf("Resultat pour la recherche au niveau 0 :\n");
    for(int n = 1000; n <= 100000; n = 10){
        printf("-Pour %d valeurs : ", n);
        startTimer();
        for(int k = 0; k < n; k++){
            isInList(k, list, 0);
        }
        stopTimer();
        displayTime();
        printf("\n");
    }

    //---------------------------------------------

    printf("Resultat pour la recherche dicho :\n");
    for(int n = 1000; n <= 100000; n= 10){
        printf("-Pour %d valeurs : ", n);
        startTimer();
        for(int k = 0; k < n; k++){
            recherche_dicho(list, nb_level,k);
        }
        stopTimer();
        displayTime();
        printf("\n");
    }


