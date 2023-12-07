//
// Created by Ilyès K on 03/12/2023.
//

#ifndef PROJET_S3_CELLULES_H
#define PROJET_S3_CELLULES_H

struct s_d_cell
{
    int value;
    int lev_max;
    struct s_d_cell **next;
};

typedef struct s_d_cell t_d_cell;

t_d_cell *create_cell(int val,int max);
#endif //PROJET_S3_CELLULES_H
