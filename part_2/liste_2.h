//
// Created by Ilyès, Diaby, Hippolyte
//

#ifndef PROJET_S3_LISTE_2_H
#define PROJET_S3_LISTE_2_H

#include "../part_1/listes.h"

#include "../part_1/listes.h"

int* createLevels2(int nb_level);


//t_d_list *createList2(int puissance);
int saisie_secur();

void insertList(t_d_list *list, int val, int level);

void inserthead(t_d_list *list,int i, t_d_cell *new_cell);

int* createlevels(int level, int cell_max);

t_d_list createEmptyList(int level);

int recherche_niveau0(int val, t_d_list list, int level);

int recherche_dicho(t_d_list mylist, int levelmax, int val);

void display_list2(t_d_list list,int n);

void suppression_list2(t_d_list **list,int n);

void back();

#endif //PROJET_S3_LISTE_2_H
