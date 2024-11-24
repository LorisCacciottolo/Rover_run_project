#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "loc.h"
#include "moves.h"
#include "tree.h"


// Function to display the current cycle number
void nbCycles(int cycle) {
    printf("\n=== === === Cycle nb %-3d=== === ===\n\n", cycle);
}



int main() {
    printf("\n *   .   +  *    .   +  *  +  *   .   +  *    .   +  *  *");
    printf("\n .  +  *===| Welcome In The Rover Run Project !|===*  +  .");
    printf("\n *   .   +  *    .   +  *  +  *   .   +  *    .   +  *  *\n\n");

    //create the map and get the initial robot position
    t_map map = createMapFromFile("C:..\\MARC-master\\maps\\example1.map");
    t_localisation currentLoc = initialRobotPosition(map);  // Initial position of the robot
    int cycle = 0;
    int nb_moves = 5;
    int nb_choices = 4;

    //display the initial position and orientation of the robot
    nbCycles(cycle);
    printf("Initial Position: (%d, %d)\n", currentLoc.pos.x, currentLoc.pos.y);
    printf("Orientation: %s\n", currentLoc.ori == NORTH ? "NORTH" :
    currentLoc.ori == SOUTH ? "SOUTH" : currentLoc.ori == EAST ? "EAST" : "WEST");

    displayMapRobot(map, currentLoc.pos);  //display the initial map with the robot's position


    t_move *moves = chooseRandomMoves(nb_moves);  //choose random moves
    t_node *current_node = NULL;
    t_node *root1 = NULL;

    //main loop to manage the robot's movement
    while (1) {
        //display the list of chosen moves for the current cycle

        //create a new decision tree from the current position
        root1 = createNode(current_node ? current_node->value : 1000,
                           0, nb_moves, F_10,
                           current_node ? current_node->loc : currentLoc);
        createSons(root1, nb_moves, nb_choices, moves,
                   current_node ? current_node->loc : currentLoc, map, 0);

        //find the next node with the minimum cost (shortest distance to the base)
        current_node = minimumCost(root1);

        //if a valid node is found, update the robot's position and display the map
        if (current_node != NULL) {
            currentLoc = current_node->loc;  //update robot's position
            cycle++;
            nbCycles(cycle);
            printf("Position: (%d, %d)\n", currentLoc.pos.x, currentLoc.pos.y);
            printf("Distance to the base: %d units\n", current_node->value);

            //display the updated map with the new position of the robot
            displayMapRobot(map, currentLoc.pos);

            //display the sequence of movements made by the robot
            displayRobotMoves(moves, nb_moves);
        }


        if (current_node == NULL || current_node->value == 0) {
            break;
        }

        //generate new random moves for the next cycle
        free(moves);
        moves = chooseRandomMoves(nb_moves);
    }

    //free memory for the last set of moves
    free(moves);
    printf("\n *   .   +  *    .   +  *  +  *   .   +  *    .   +  *  *");
    printf("\n              === === === === === === === ===       ");
    printf("\n        === | The robot has reached the base! | === ");
    printf("\n         ===| Mission Accomplished! Great Job! |=== ");
    printf("\n              === === === === === === === ===        ");
    printf("\n *   .   +  *    .   +  * \\\(^~~^)/ *   .   +  *    .   +  *\n");
    return 0;
}
