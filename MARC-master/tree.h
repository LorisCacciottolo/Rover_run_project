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
    t_move moves[10]; //we include \0
    int nb_moves;
} t_path;

t_node * createNode(int val, int depth, int nb_sons, t_move move, t_localisation loc);
void createSons(t_node* node, int nb_moves, int nb_choices, t_move rem_moves[], t_localisation loc, t_map map, int depth);
t_node* minimumCost(t_node* root);
void displayTree(t_node* root, int depth);


#endif //ROVER_RUN_PROJECT_RANDOM_H

