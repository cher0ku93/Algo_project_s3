//
// Created by Ilyès K on 03/12/2023.
//

#include "cellules.h"
#include <stdio.h>
#include <stdlib.h>

//Création cellule//
t_d_cell *create_cell(int val,int max){

    t_d_cell *new_cell = malloc(sizeof(t_d_cell));

    if(new_cell==NULL){
        //Si échec alors :

        printf("Echec allocation mémoire cellule !");
        free(new_cell);
        exit(EXIT_FAILURE);
    }
    new_cell->value = val;
    new_cell->lev_max = max;
    //allocation mémoire dynamique pour les niveaux suivant :
    new_cell->next = (t_d_cell**)malloc(max*sizeof(t_d_cell*));
    //Initialisation à NULL du contenu :
    for(int i = 0;i<max;i++){
        new_cell->next[i] = NULL;}
    return new_cell;

}

void freeCell(t_d_cell *cell)
{
    // Libérer la mémoire allouée pour le tableau de pointeurs
    free(cell->next);
    // Libérer la mémoire de la cellule elle-même
    free(cell);
}
