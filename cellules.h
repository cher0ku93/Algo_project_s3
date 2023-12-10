//
// Created by Ilyès, Diaby, Hippolyte
//

#ifndef PROJET_S3_CELLULES_H
#define PROJET_S3_CELLULES_H

struct s_d_cell
{
    int value;
    //nombre du niveaux maximum de la cellule:
    int lev_max;
    //Tableau contenant nos cellules suivante :
    struct s_d_cell **next;
};
typedef struct s_d_cell t_d_cell;

t_d_cell *create_cell(int val,int max);
#endif //PROJET_S3_CELLULES_H
