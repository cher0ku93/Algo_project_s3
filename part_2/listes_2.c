//
// Created by Ilyès K on 06/12/2023.
//

#include "listes_2.h"
#include <stdlib.h>
#include <stdio.h>
#include "math.h"



t_d_list *createList2(int max_l,int puiss) {
    //Allocation de la mémoire pour la nouvelle liste :
    t_d_list *new_list = (t_d_list *) malloc(sizeof(t_d_list));

    //Si liste correctement créée :
    if (new_list != NULL) {
        new_list->max_levels = max_l;
        new_list->heads = (t_d_cell **) malloc(puiss * sizeof(t_d_cell *));
        //Initialisation des heads à NULL :1
        for (int i = 0; i < puiss; i++) {
            new_list->heads[i] = NULL;
        }
        return new_list;
    }
}

//Création des niveaux en fonction de la puissances//
int* createLevels2(int nb_level) {
    int n = pow(2, nb_level) - 1;
    int* levels = calloc(n, sizeof(int));
    for(int i = 1; i < nb_level; i++){
        for(int j = pow(2,i)-1; j < n; j += pow(2,i)){
            levels[j] += 1;
        }
    }
    return levels;
}


//Inserer en tête//
void inserthead(t_d_list *list,int i, t_d_cell *new_cell){
    new_cell->next[i] = list->heads[i];
    list->heads[i]= new_cell;
}

//Inserer dans la liste//
void insertList(t_d_list *list, int val, int level) {
    t_d_cell *new_cell = create_cell(val, level);
    for (int i = 0; i < level; i++) {
        if (list->heads[i] == NULL) { // insertion tete de liste
            inserthead(list, i, new_cell);
        } else if ((list->heads[i] != NULL) && (list->heads[i]->value >= val)) {
            inserthead(list, i, new_cell);
        } else if (list->heads[i] != NULL) { // insertion milieu de liste
            t_d_cell *temp = list->heads[i];
            t_d_cell *prev;
            while (temp != NULL && temp->value <= val) {
                prev = temp;
                temp = temp->next[i];
            }
            prev->next[i] = new_cell;
            new_cell->next[i] = temp;
        }
    }
}

//Fonction pour sécuriser la saisie//
int saisie_secur() {
    char buffer[100];
    int a;
    do {
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &a) != 1) {
            printf("Merci de faire une saisie correcte -> ");
            continue;  // Recommence la boucle
        }

    } while (sscanf(buffer, "%d", &a) != 1);
    return a;
}


//Fonction de recherche dans le niveau zéro//
int recherche_niveau0(int val, t_d_list list, int level){
    t_d_cell *temp = list.heads[level];
    while (temp != NULL && temp->value <= val) {
        if (temp->value == val) {
            return 1;
        }
        temp = temp->next[level];
    }
    return 0;
}

//Fonction recherche dichotomique//
int recherche_dicho(t_d_list mylist, int levelmax, int val)
{
    t_d_cell *temp, *prev;
    int i=2;
    int j=1;
    temp = mylist.heads[levelmax-1];
    while (temp!=NULL && i<=levelmax+1)
    {
        if (temp->value == val) {
            return 1;
        }
        else if (temp->value > val && temp == mylist.heads[levelmax-j])
        {
            temp = mylist.heads[levelmax-i];
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

/*int recherche_dicho(t_d_list mylist, int levelmax, int val) {
    int i = levelmax - 1;
    t_d_cell *temp = mylist.heads[i];
    while (temp != NULL && i >= 0) {if (temp->value == val) {
            printf("Liste no : %d et val no : %d ",i,mylist.heads[i]->value);
            return 1; // Valeur trouvée
        } else if (temp->value > val) {
            // Si la valeur actuelle est plus grande, descendre d'un niveau
            i--;
            if (i >= 0) {
                temp = mylist.heads[i];
            }
        } else {
            // Avancer dans la liste au niveau courant
            t_d_cell *prev = temp;
            temp = temp->next[i];
            if (temp == NULL || temp->value > val) {
                // Si la prochaine valeur est plus grande, descendre d'un niveau
                i--;
                if (i >= 0) {
                    temp = mylist.heads[i];
                }
            }
        }
    }

    return 0; // La valeur n'a pas été trouvée
}*/


//Fonction d'affichage de la partie 2//
void display_list2(t_d_list list,int n) {

    printLevel(list, 0);//Affichage de la première ligne comme base

    //Boucle for pour aller du niveau 0 au dernier niveau:
    for (int i = 1; i < n; i++) {
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


//Fonction suppression liste enregistrée partie 2//
void suppression_list2(t_d_list **list,int n) {
    if (list == NULL || *list == NULL) {
        return;  // Liste déjà vide ou non allouée
    }

    // Libérer la mémoire de chaque niveau de la liste
    for (int i = 0; i < n; i++) {
        t_d_cell *curr = (*list)->heads[i];
        while (curr != NULL) {
            t_d_cell *temp = curr;
            curr = curr->next[i];
            free(temp);
        }
    }

    // Libérer la mémoire du tableau de pointeurs
    free((*list)->heads);

    // Mettre le pointeur de liste à NULL
    free(*list);
    *list = NULL;
}


























