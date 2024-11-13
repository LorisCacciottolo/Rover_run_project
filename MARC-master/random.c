//
// Created by 33768 on 13/11/2024.
//
#include <stdlib.h>
#include <stdio.h>


char* randomMoves(){
    if (randomMoves == NULL){
        return NULL;
    }
    char* randomMoves = malloc(9 * sizeof(char));
}

int F_10 = 22, F_20 = 15, F_30 = 7, B_10 = 7, T_LEFT = 21, T_RIGHT = 21, U_TURN = 7;

char availableMoves[] = {F_10, F_20, F_30, B_10, T_LEFT, T_RIGHT, U_TURN };



for (int i = 0; i < 9; i++) {
        int randomnumber = rand() % 7;
        randomMoves[i] = availableMoves[randomnumber];
}