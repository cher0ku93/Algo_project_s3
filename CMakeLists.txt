cmake_minimum_required(VERSION 3.26)
project(Projet_S3 C)

set(CMAKE_C_STANDARD 99)

add_executable(Projet_S3 main.c
        part_1/listes.c
        part_1/listes.h
        part_1/cellules.c
        part_1/cellules.h
        menus/menu_one.c
        menus/menu_one.h
        menus/menu_two.c
        menus/menu_two.h
        part_2/liste_2.c
        part_2/liste_2.h
        part_2/timer.c
        part_2/timer.h
        menus/menu_three.c
        menus/menu_three.h
        part_3/agenda.c
        part_3/agenda.h
)
