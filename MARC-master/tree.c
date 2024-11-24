//
// Created by 33768 on 13/11/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "moves.h"
#include "map.h"
#include "loc.h"


t_node * createNode(int val, int depth, int nb_sons, t_move move, t_localisation loc)
{
    t_node * root = (t_node *)malloc(sizeof(t_node));
    //initialize node's properties
    root->value = val; //cost of the current position
    root->nb_sons = nb_sons;
    root->loc = loc;
    root->move = move;

    // Initialize the array storing the move with the current move
    for (int i = 0; i < 5; i++) {
        if (i == depth) {
            root->movements[i] = move; // stores the incoming move
        } else {
            root->movements[i] = STAYATBASE;  // put at default
        }
    }
    // Initialize the sons pointers of the node
    for (int i = 0; i < 9; i++) {
        root->sons[i] = NULL;
    }

    return root;
}

void createSons(t_node* node, int nb_moves, int nb_choices, t_move rem_moves[], t_localisation loc, t_map map, int depth)
{
    if (depth >= nb_choices) { //end recursion
        return;
    }

    for (int i = 0; i < nb_moves; i++)
    {
        //rem_moves[] : array stacking the remaining movements we will use for the sons
        //update the localisation of the robot according to a move
        t_localisation newLoc = move(loc, rem_moves[i]);


        //ensure the new location is valid
        if (isValidLocalisation(newLoc.pos, map.x_max, map.y_max))
        {
            //create a new child node
            t_node* son = createNode(map.costs[newLoc.pos.y][newLoc.pos.x],depth + 1,nb_moves,rem_moves[i],newLoc);

            //copy parent's movement
            for (int j = 0 ; j < depth ; j++) {
                son->movements[j] = node->movements[j];
            }
            //add the current move
            son->movements[depth] = rem_moves[i];
            node->sons[i] = son;
            createSons(son, nb_moves, nb_choices, rem_moves, newLoc, map, depth + 1); //recursive call
        }
    }
}


t_node* minimumCost(t_node* root)
{
    //if the current node is NULL or its value is invalid, return NULL
    if (!root || root->value >= 10000) {
        return NULL;
    }

    //assume the current node is the minimum initially
    t_node* minimum_node = root;

    //recursively check all child nodes
    for (int i = 0; i < root->nb_sons; i++) {
        t_node* son_min = minimumCost(root->sons[i]); //find the minimum node in the current subtree

        //if a valid smaller value is found, update the minimum node
        if (son_min && son_min->value < minimum_node->value) {
            minimum_node = son_min;
        }
    }

    //return the minimum node found
    return minimum_node;
}



void displayTree(t_node* root, int depth)
{
    if (root == NULL) { //ends recursion
        return;
    }

    //print indentation
    for (int i = 0; i < depth; i++) {
        printf(" ");
    }

    //for every child of the current node, calls displayTree with an incremented level (level + 1)
    //to display the subtree rooted at this child.
    for (int i = 0; i < root->nb_sons; i++) {
        displayTree(root->sons[i], depth + 1);
    }
}


