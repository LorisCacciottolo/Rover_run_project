//
// Created by 33768 on 13/11/2024.
//

#ifndef ROVER_RUN_PROJECT_RANDOM_H
#define ROVER_RUN_PROJECT_RANDOM_H


#include "moves.h"
#include "map.h"


typedef struct s_node {
    int value ;
    int nb_sons;
    t_localisation loc;
    t_move move;
    t_move movements[5];
    struct t_node * sons[9];
}t_node;

typedef struct s_path{
    t_move moves[10];
    int nb_moves;
} t_path;




#endif //ROVER_RUN_PROJECT_RANDOM_H

