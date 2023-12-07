//
// Created by Ilyès K on 03/12/2023.
//

#ifndef PROJET_S3_LISTES_H
#define PROJET_S3_LISTES_H
#include "../part_1/cellules.h"

#include "cellules.h"

typedef struct s_d_list
{
    int max_levels;
    t_d_cell **heads;
} t_d_list;


t_d_list *createList(int max_l);
void display_list(t_d_list list);
void printLevel(t_d_list list, int level);
void create_and_add_cell_sorted(t_d_list *list);
void add_cell_sorted(t_d_cell *cell, t_d_list *list);
void suppression_list(t_d_list **list);

#endif //PROJET_S3_LISTES_H
