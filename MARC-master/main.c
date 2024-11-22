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


void printPath(const char *prefix, const char *string) {
    printf("%s ", prefix);
    if (string != NULL)
        printf("%s", string);
    else
        printf("(null)");
    printf("\n");
}

char* arrayrandomproba() {
    char *arrayrandomproba = (char*)malloc((MAX_CHILDREN + 1) * sizeof(char));
    if (arrayrandomproba == NULL) {
        return NULL;
    }

    int SIZE = 100;
    int F_10 = 22, F_20 = 15, F_30 = 7;
    int R_10 = 7, TR = 21, TL = 21, TB = 7;

    srand(time(0));

    char arrayloop[SIZE];
    int index = 0;

    for (int i = 0; i < F_10; i++) arrayloop[index++] = 'A';
    for (int i = 0; i < F_20; i++) arrayloop[index++] = 'B';
    for (int i = 0; i < F_30; i++) arrayloop[index++] = 'C';
    for (int i = 0; i < R_10; i++) arrayloop[index++] = 'R';
    for (int i = 0; i < TR; i++) arrayloop[index++] = 'T';
    for (int i = 0; i < TL; i++) arrayloop[index++] = 'L';
    for (int i = 0; i < TB; i++) arrayloop[index++] = 'J';

    for (int i = 0; i < 9; i++) {
        int randomnumber = rand() % SIZE;
        arrayrandomproba[i] = arrayloop[randomnumber];

        switch (arrayrandomproba[i]) {
            case 'A': F_10--; break;
            case 'B': F_20--; break;
            case 'C': F_30--; break;
            case 'R': R_10--; break;
            case 'T': TR--; break;
            case 'L': TL--; break;
            case 'J': TB--; break;
        }

        for (int j = randomnumber; j < SIZE - 1; j++) {
            arrayloop[j] = arrayloop[j + 1];
        }
        SIZE--;
    }

    arrayrandomproba[MAX_CHILDREN] = '\0';
    return arrayrandomproba;
}

// Struct of tree
typedef struct t_node {
    char path[MAX_PATH_LENGTH];
    int val;
    struct t_node *children[MAX_CHILDREN];
} t_node;


// Struct of tree root
typedef struct s_tree
{
    t_node *root;
} t_tree;

t_tree createEmptyTree(){
    t_tree temp;
    temp.root = NULL;
    return temp;
}




// Map created with dimensions 7 x 6
int calculate_node(char* t_path, t_map map, t_localisation loc) {
    t_orientation ori = NORTH;
    t_localisation phantomloc = loc;
    int size = strlen(t_path);

    for (int i = 0; i < size; i++) {
        switch(t_path[i]) {
            case 'A': phantomloc = translate(phantomloc, F_10); break;
            case 'B':
                for(int wrizz=0;wrizz<2;wrizz++)
                    phantomloc = translate(phantomloc, F_10);
                break;
            case 'C':
                for(int wrizz=0;wrizz<3;wrizz++)
                    phantomloc = translate(phantomloc, F_10);
                break;
            case 'R': phantomloc = translate(phantomloc, B_10); break;
            case 'T': phantomloc.ori = rotate(phantomloc.ori, T_RIGHT); break;
            case 'L': phantomloc.ori = rotate(phantomloc.ori, T_LEFT); break;
            case 'J': phantomloc.ori = rotate(phantomloc.ori, U_TURN); break;
            default: break;
        }
    }
    if (phantomloc.pos.x < 0 || phantomloc.pos.x >= 7 || phantomloc.pos.y < 0 || phantomloc.pos.y >= 6) {
        // printf("Erreur : Rover out of range\n");
        return 999999;  // Imposible Path
    }
    int Cost = map.costs[phantomloc.pos.y][phantomloc.pos.x];

    // printf("Position: (%d, %d), Orientation %d cost: %d\n", phantomloc.pos.x, phantomloc.pos.y, phantomloc.ori, totalCost);
    return Cost;
}


t_node *createNode(const char *t_path, t_map map, t_localisation loc) {
    t_node *node = (t_node *)malloc(sizeof(t_node));

    strncpy(node->path, t_path, MAX_PATH_LENGTH - 1);
    node->path[MAX_PATH_LENGTH - 1] = '\0';

    node->val = calculate_node(t_path, map, loc);



    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }


    // printf("node info: path: %s, val: %d\n", node->path, node->val);
    return node;
}

void generateCombinations(t_node *node, const char *alphabet, int depth, int maxDepth, t_map map, t_localisation loc) {
    if (depth == maxDepth) {
        //printf("Chemin final : %s\n", node->path);
        return;
    }

    int len = strlen(alphabet);
    for (int i = 0; i < len; i++) {
        // Create new chain alphabet[i]
        char reducedAlphabet[len];
        strncpy(reducedAlphabet, alphabet, i); // Copy letters before i
        strncpy(reducedAlphabet + i, alphabet + i + 1, len - i - 1); // Copy letters after i
        reducedAlphabet[len - 1] = '\0';

        // Add to current path
        char newPath[MAX_PATH_LENGTH];
        snprintf(newPath, MAX_PATH_LENGTH, "%s%c", node->path, alphabet[i]);

        t_node *child = createNode(newPath, map, loc);
        node->children[i] = child;

        generateCombinations(child, reducedAlphabet, depth + 1, maxDepth, map, loc);
    }
}


// Reste plus qu'a fix cette fonction car deja j'ai pas compris comment ca peut marcher et j'arrive pas a return tout le path dcp force a nous
void findOptimalPath(t_node* node, t_node** optimalNode, int* minCost, char** optimalPath) {
    if (node == NULL) return;

    if (node->val < *minCost && (strlen(node->path) == 5 || node->val == 0)) {
        *minCost = node->val;
        *optimalNode = node;
        *optimalPath = node->path;
    }

    for (int i = 0; i < 9; i++) {
        findOptimalPath(node->children[i], optimalNode, minCost, optimalPath);
    }
}





void printTree(t_node *node, int depth) {
    if (node == NULL) return;

    // Indentations
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    // Node informations
    printf("Node(Path: %s, Value: %d)\n", node->path, node->val);

    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->children[i] != NULL) {
            printTree(node->children[i], depth + 1);
        }
    }
}

void freeTree(t_node *node) {
    if (node == NULL) return;

    for (int i = 0; i < MAX_CHILDREN; i++) {
        freeTree(node->children[i]);
    }
    free(node);
}

int countNodes(t_node *node) {
    if (node == NULL) {
        return 0;
    }

    int count = 1;

    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->children[i] != NULL) {
            count += countNodes(node->children[i]);
        }
    }

    return count;
}










void displayNode(t_node *node, int depth) {
    if (node == NULL) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("Value(%d): %d\n", depth, node->val);

    for (int i = 0; i < 9; i++) {
        displayNode(node->children[i], depth + 1);
    }
}

void displayTree(t_tree *tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("L'arbre est vide.\n");
        return;
    }
    printf("Affichage de l'arbre:\n");
    displayNode(tree->root, 0);
}



void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}




void needinfo() {
    t_map map = createMapFromFile("./maps/example1.map");

    int Xdep = 4;
    int Ydep = 6;
    t_orientation ori = NORTH;

    t_localisation loc = loc_init(Xdep, Ydep, ori);

    clock_t start, end;
    clock_t start1,start2,end1,end2;
    double cpu_time_used1, cpu_time_used2,cpu_time_used3;
    start = clock();

    char* alphabet = arrayrandomproba();
    int maxDepth = 5;

    t_tree tree = createEmptyTree();
    t_node *root = createNode("", map, loc);
    tree.root = root;

    start1 = clock();
    generateCombinations(root, alphabet, 0, maxDepth, map, loc);
    end1 = clock();

    t_node *optimalNode = NULL;
    int minCost = 9000;
    char* optimalPath = NULL;
    start2 = clock();
    findOptimalPath(root, &optimalNode, &minCost, &optimalPath);
    end2 = clock();

    calculate_node(optimalPath, map, loc);

    end = clock();
    cpu_time_used1 = ((double) (end - start)) / CLOCKS_PER_SEC;
    cpu_time_used2 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
    cpu_time_used3 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;

    char wannaprint[10];
    printf("Hey wanna get the information of the project ?\nYes/No : ");
    scanf("%s", wannaprint);




    if (strcmp(wannaprint, "yes") == 0 || strcmp(wannaprint, "Yes") == 0) {
        printf("\n");
        printf("      __...--~~~~~-._   _.-~~~~~--...__\n");
        printf("    //               `V'               \\ \n");
        printf("   //                 |                 \\ \n");
        printf("  //__...--~~~~~~-._  |  _.-~~~~~~--...__\\ \n");
        printf(" //__.....----~~~~._\\ | /_.~~~~----.....__\\\n");
        printf("====================\\\\|//====================\n");
        printf("                     `---`\n");
        printf("///////////////// INFORMATIONS ///////////////////");

        printf("\n");
        printf("x axis: %d, y axis: %d\n", loc.pos.x, loc.pos.y);


        printf("movements randomly choosen by the algorithm: ");
        printf(alphabet);
        printf("\n");
        if (optimalPath != NULL) {
            printf("Optimal path: %s\n", optimalPath);
            printf("Cost: %d\n", minCost);
            printf("( ˶ˆᗜˆ˵ )\n");
        } else
            printf("Safly no path find...\n૮(˶ㅠ︿ㅠ)ა\n");

        printf("Time taken to execute the generateCombinations function : %f\n", cpu_time_used2);
        printf("Time taken to execute the findOptimalPath function : %f\n", cpu_time_used3);
        printf("Time taken to execute all the project: %f\n", cpu_time_used1);
    }
    free(alphabet);
}

int main(){
    needinfo();
    return 0;
}

