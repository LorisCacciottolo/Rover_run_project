#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "map.h"
#include "loc.h"
#include "moves.h"

#define MAX_CHILDREN 9
#define MAX_PATH_LENGTH 6


int main(){
    //initialising the map
    t_map map;
    displayMap(map);
    t_localisation robot = initialRobotPosition(map);
    return 0;
}

