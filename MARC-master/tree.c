//
// Created by 33768 on 13/11/2024.
//
#include <stdlib.h>
#include <stdio.h>


char* randomMoves(){
    char* randomMoves = malloc(9 * sizeof(char));
    if (randomMoves == NULL){
        return NULL;
    }


int F_10 = 22, F_20 = 15, F_30 = 7, B_10 = 7, T_LEFT = 21, T_RIGHT = 21, U_TURN = 7;
int ind = 99;
char availableMoves[] = {'F_10', 'F_20', 'F_30', 'B_10', 'T_LEFT', 'T_RIGHT', 'U_TURN' };



for (int i = 0; i < 9; i++) {

    int randomNumber = rand() % ind;
    if (randomNumber <= F_10) {
        randomMoves[i] = availableMoves[0];
        F_10--;

        if (F_10 < randomNumber <= F_20 + F_10) {
            randomMoves[i] = availableMoves[1];
            F_20--;
        }
        if (F_20 + F_10 < randomNumber <= F_20 + F_10 + F_30) {
            randomMoves[i] = availableMoves[2];
            F_30--;

        }
        if (F_20 + F_10 + F_30 < randomNumber <= F_20 + F_10 + F_30 + B_10) {
            randomMoves[i] = availableMoves[3];
            B_10--;
        }
        if (F_20 + F_10 + F_30 + B_10 < randomNumber <= F_20 + F_10 + F_30 + B_10 + T_LEFT) {
            randomMoves[i] = availableMoves[4];
            T_LEFT--;
        }
        if (F_20 + F_10 + F_30 + B_10 + T_LEFT < randomNumber <= F_20 + F_10 + F_30 + B_10 + T_LEFT + T_RIGHT) {
            randomMoves[i] = availableMoves[5];
            T_RIGHT--;
        }
        if (F_20 + F_10 + F_30 + B_10 + T_LEFT + T_RIGHT < randomNumber <=
            F_20 + F_10 + F_30 + B_10 + T_LEFT + T_RIGHT + U_TURN) {
            randomMoves[i] = availableMoves[6];
            U_TURN--;
        }

        ind--;
    }
}