//
// Created by Ilyès K on 2023.
//


//-----------------//
#include <stdio.h>
//-----------------//
#include "menu_two.h"
#include "menu_one.h"
//-----------------//
#include "../part_2/liste_2.h"

#include "math.h"


void back(){
    menu2();
}


t_d_list  *mylist2;
char buffer[100];


int menu2(){

    int choice;

    printf("\n------Partie 2------\n");
    printf("\n1. Créer une liste ");
    printf("\n2. Recherche dans le niveau 0 ");
    printf("\n3. Recherche à partir du niveau le plus haut");
    printf("\n4. Timer");
    printf("\n5. Supprimer la liste enregistrée");
    printf("\n6. Menu principal\n");
    printf("\nVotre choix : ");


    do{
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &choice) != 1) {
            printf("Merci de faire une saisie correcte -> ");
            continue;  // Recommence la boucle
        }

    }while(sscanf(buffer, "%d", &choice)!=1);

    fflush(stdout);

    int level = 0;
    int i;

    switch (choice) {
        case 1:{

            int *levels;

            if(mylist2!=NULL){
                printf("\nListe déjà créée :)\n");
                menu2();
            }

            printf("Saisir la nombre de niveaux de votre liste : ");
            level = saisie_secur();

            while(level<0){
                printf("doit etre sup à 0");
                level=saisie_secur();
            }

            mylist2 = createList(level);
            mylist2->max_levels=(pow(2,level)-1);
            levels = createLevels2(level);

            for(i=0;i<mylist2->max_levels;i++){
                insertList(mylist2,i+1,levels[i]+1);
            }
            printf("\n");
            display_list2(*mylist2,level);
            menu2();
        }
        case 2 : {

            int val,res;

            printf("\nEntrez la valeur à rechercher dans le niveau 0 : ");
            val = saisie_secur();

            res = recherche_niveau0(val,*mylist2,0);

            if(res==1){
                printf("La valeur %d est bien présente au niveau 0 !",val);
                back();
            }
            printf("La valeur %d n'est pas présente au niveau 0. ",val);

            menu2();
            fflush(stdout);
            break;
        }
        case 3: {
            int val,res;
            printf("\nEntrez la valeur à rechercher : ");
            val = saisie_secur();
            res = recherche_dicho(*mylist2,level,val);
            if(res!=1){

                printf("Valeur inexistante dans l'ensemble des listes");
            }
            printf("Valeur trouvée par la dichotomie");
            back();
        }
        case 5:{
            printf("\nSuppression de la liste en cours...");
            suppression_list2(&mylist2,level);
            printf("\nListe supprimée\n");
        }
        case 6 :{
            menu_principal();
        }
        default:{
            printf("Erreur de choix");
            menu2();
        }
    }
    return 0;
}
