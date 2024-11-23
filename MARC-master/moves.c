//
// Created by flasque on 19/10/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "moves.h"
#include <time.h>

/* prototypes of local functions */
/* local functions are used only in this file, as helper functions */

/**
 * @brief Function to rotate the robot according to a move and its actual orientation
 * @param ori : the actual orientation of the robot
 * @param move : the move to do
 * @return the new orientation of the robot
 */
t_orientation rotate(t_orientation, t_move );

/**
 * @brief function to translate the robot according to a move and its actual position
 * @param loc : the actual localisation of the robot
 * @param move : the move to do
 * @return the new localisation of the robot
 */
t_localisation translate(t_localisation , t_move);

/* definition of local functions */

t_orientation rotate(t_orientation ori, t_move move)
{
    int rst=0;
    switch (move)
    {
        case T_LEFT:
            rst=3;
            break;
        case T_RIGHT:
            rst=1;
            break;
        case U_TURN:
            rst=2;
            break;
        default: // should not happen
            rst=0;
            break;
    }
    return (ori+rst)%4;
}

t_localisation translate(t_localisation loc, t_move move)
{
    /** rules for coordinates:
     *  - x grows to the right with step of +1
     *  - y grows to the bottom with step of +1
     *  - the origin (x=0, y=0) is at the top left corner
     */
    t_position res=loc.pos;
    switch (move) {
        case F_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 1;
                    break;
                case EAST:
                    res.x = loc.pos.x + 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 1;
                    break;
                case WEST:
                    res.x = loc.pos.x - 1;
                    break;
                default:
                    break;
            }
            break;
        case F_20:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 2;
                    break;
                case EAST:
                    res.x = loc.pos.x + 2;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 2;
                    break;
                case WEST:
                    res.x = loc.pos.x - 2;
                    break;
                default:
                    break;
            }
            break;
        case F_30:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 3;
                    break;
                case EAST:
                    res.x = loc.pos.x + 3;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 3;
                    break;
                case WEST:
                    res.x = loc.pos.x - 3;
                    break;
                default:
                    break;
            }
            break;
        case B_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y + 1;
                    break;
                case EAST:
                    res.x = loc.pos.x - 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y - 1;
                    break;
                case WEST:
                    res.x = loc.pos.x + 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return loc_init(res.x, res.y, loc.ori);

}

/* definitions of exported functions */

char *getMoveAsString(t_move move)
{
    return _moves[move];
}

t_localisation move(t_localisation loc, t_move move)
{
    t_localisation new_loc=loc;
    if ((move >=T_LEFT) && (move <= U_TURN))
    {
        new_loc.ori = rotate(loc.ori, move);
    }
    else
    {
        new_loc = translate(loc, move);
    }

    return new_loc;
}

void updateLocalisation(t_localisation *p_loc, t_move m)
{
    *p_loc = move(*p_loc, m);
    return;
}


/**
 * @brief Function to choose random moves
 * @param nbmov : The number of random moves to choose
 * @return The list of the stored random moves
 */
t_move* chooseRandomMoves(int nbmov) {
    //initialisation of the number of possible moves for each type of move
    int random;
    int maxval_F10 = 21;
    int maxval_F20 = 36;
    int maxval_F30 = 43;
    int maxval_B10 = 50;
    int maxval_RIGHT = 71;
    int maxval_LEFT = 92;
    int maxval_UTURN = 99;

    srand(time(NULL)); //to make sure we get a different rand nb each time

    t_move *list = malloc(nbmov * sizeof(t_move));
    if (list == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    //the loop decreases the number of possible other moves once a random move is chosen
    for (int i = 0; i < nbmov; i++) {
        random = rand() % (maxval_UTURN+1); //generates a random number between 1 and maxval_UTURN

        if (random <= maxval_F10) {
            list[i] = F_10;//stores current move in list
            maxval_F10--;
            maxval_F20--;
            maxval_F30--;
            maxval_B10--;
            maxval_RIGHT--;
            maxval_LEFT--;
            maxval_UTURN--;

        } else if (random <= maxval_F20) {
            list[i] = F_20; //stores current move in list
            maxval_F20--;
            maxval_F30--;
            maxval_B10--;
            maxval_RIGHT--;
            maxval_LEFT--;
            maxval_UTURN--;
        } else if (random <= maxval_F30) {
            list[i] = F_30;//stores current move in list
            maxval_F30--;
            maxval_B10--;
            maxval_RIGHT--;
            maxval_LEFT--;
            maxval_UTURN--;
        } else if (random <= maxval_B10) {
            list[i] = B_10;//stores current move in list
            maxval_B10--;
            maxval_RIGHT--;
            maxval_LEFT--;
            maxval_UTURN--;
        } else if (random <= maxval_RIGHT) {
            list[i] = T_RIGHT;//stores current move in list
            maxval_RIGHT--;
            maxval_LEFT--;
            maxval_UTURN--;
        } else if (random <= maxval_LEFT) {
            list[i] = T_LEFT;//stores current move in list
            maxval_LEFT--;
            maxval_UTURN--;
        } else {
            list[i] = U_TURN;//stores current move in list
            maxval_UTURN--;
        }
    }

    return list; // returns the list with the random moves stored in it

}


/**
 * @brief Function to get the string corresponding to a move
 * @param move : the move we want to convert in a string
 * @return the string corresponding to the move
 */
const char* string_t_moves(t_move move) { //clearer display output for the moves
    switch (move) {
        case F_10: return "Go forward 10 m";
        case F_20: return "Go forward 20 m";
        case F_30: return "Go forward 30 m";
        case B_10: return "Go backward 10 m";
        case T_LEFT: return "Turn 90deg left";
        case T_RIGHT: return "Turn 90deg right";
        case U_TURN: return "Do a U-Turn";
        case STAYATBASE: return "Stay at base";
        default: return "Undefined move";
    }
}