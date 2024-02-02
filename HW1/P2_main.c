#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

typedef struct { 
    int rank;
    int toast;
    int up, down, left, right; // relative position
    int up_distance, down_distance, left_distance, right_distance; // distance to the closest bakery
    int close;  // 1: open, 0: close
    int visited; 
} node;

typedef struct listNode{ 
    int rank;
    int toast;
    int close;  // 1: open, 0: close
    int visited; 
    struct listNode *leftL, *rightL, *upL, *downL;
} listNode;

typedef struct { 
    int row;
    int col;
} coordinate;

void eatToast(node**, coordinate*, int, int, int, int);
int *chooseNext(node**, coordinate*, int, int, int, int, int, int, int, int, int, int);
void relativePosition(node**, int, int);
void relativePositionForTrain2(node**, coordinate*, int , int);
void listRotation(listNode**, listNode**, listNode**, listNode**, int, int);
void listToArray(node**, coordinate*, listNode*, int, int);

int main(){
    int input = 0;
    int n = 0;   // ROW
    int m = 0;   // COL
    int t1 = 0;  // train1
    int t2 = 0;  // train2
    int r = 0;   // race
    int r_k = 0; // initial gathering rank
    int l_k = 0; // maximum riding length
    int s_k = 0; // size of the cycling team
    int round = 1; // round k
    scanf("%d %d", &n, &m);

    // array memory allocation for position
    coordinate *position = (coordinate*)malloc(sizeof(coordinate) * n * m);
    
    // 2D-array memory allocation for bakery map
    node **map = (node**)malloc(sizeof(node*) * n);
    for(int i = 0; i < n; i++){
        map[i] = (node*)malloc(sizeof(node) * m);
    }

    // 2D-array rank initialization & position initialization & visited
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            scanf("%d", &input);
            map[i][j].rank = input;
            map[i][j].close = 1; // open bakery
            map[i][j].visited = 0; // visited initialization
            // position initialization
            position[input-1].row = i;
            position[input-1].col = j;
        }
    }

    // relative position initialization
    relativePosition(map, n, m);
    
    // 2D-array toast initialization
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            scanf("%d", &map[i][j].toast);
        }
    }

    // initialize train1, race and train2
    scanf("%d %d %d", &t1, &r, &t2);

    // train1
    for (int i = 0; i < t1; i++){
        scanf("%d %d %d", &r_k, &l_k, &s_k);
        eatToast(map, position, r_k, l_k, s_k, round);
        round++;
    }
    
    // 4-way positive linked list
    int length = m * n;
    listNode *head = NULL;
    listNode *tempHead = NULL;
    listNode *preTempHead = NULL;
    listNode *temp = NULL;
    listNode *current = NULL;
    listNode **listPosition = (listNode**)malloc(sizeof(listNode*) * m * n);
    
    listNode *head_r = NULL;
    listNode *tempHead_r = NULL;
    listNode *preTempHead_r = NULL;
    listNode *temp_r = NULL;
    listNode *current_r = NULL;
    listNode **listPosition_r = (listNode**)malloc(sizeof(listNode*) * m * n);

    // 4-way positive linked list initialization
    for (int i = 0; i < n; i++){
        listNode *newHeadNode = (listNode*)malloc(sizeof(listNode));
        if (i == 0){
            newHeadNode->rank = map[i][0].rank;
            newHeadNode->toast = map[i][0].toast;
            newHeadNode->close = map[i][0].close;
            newHeadNode->visited = map[i][0].visited;
            newHeadNode->leftL = NULL;
            newHeadNode->rightL = NULL;
            newHeadNode->upL = NULL;
            newHeadNode->downL = NULL;
            tempHead = newHeadNode;
            preTempHead = newHeadNode;
            head = newHeadNode;
            temp = newHeadNode;
            current = newHeadNode;
            listPosition[tempHead->rank-1] = tempHead;
        }
        else{
            newHeadNode->rank = map[i][0].rank;
            newHeadNode->toast = map[i][0].toast;
            newHeadNode->close = map[i][0].close;
            newHeadNode->visited = map[i][0].visited;
            newHeadNode->leftL = NULL;
            newHeadNode->rightL = NULL;
            newHeadNode->upL = preTempHead;
            preTempHead->downL = newHeadNode;
            newHeadNode->downL = NULL;
            tempHead = newHeadNode;
            current = newHeadNode;
            temp = preTempHead;
            listPosition[tempHead->rank-1] = tempHead; 
        }
        
        for (int j = 0; j < m; j++){
            // escape first node
            if (j == 0){
                continue;
            } 

            listNode *newNode = (listNode*)malloc(sizeof(listNode));

            if (i == 0){
                newNode->rank = map[i][j].rank;
                newNode->toast = map[i][j].toast;
                newNode->close = map[i][j].close;
                newNode->visited = map[i][j].visited;
                newNode->leftL = current;
                current->rightL = newNode;
                current = current->rightL;
                temp = temp->rightL;
                listPosition[current->rank-1] = current;
            }
            else{
                newNode->rank = map[i][j].rank;
                newNode->toast = map[i][j].toast;
                newNode->close = map[i][j].close;
                newNode->visited = map[i][j].visited;
                newNode->leftL = current;
                current->rightL = newNode;
                current = current->rightL;
                temp = temp->rightL;
                current->upL = temp;
                temp->downL = current;
                listPosition[current->rank-1] = current;
            }
        }
        preTempHead = tempHead;
    }
    
    // 4-way reverse linked list initialization
    for (int i = n - 1; i >= 0; i--){
        listNode *newHeadNode = (listNode*)malloc(sizeof(listNode));
        if (i == n-1){
            newHeadNode->rank = map[i][m-1].rank;
            newHeadNode->toast = map[i][m-1].toast;
            newHeadNode->close = map[i][m-1].close;
            newHeadNode->visited = map[i][m-1].visited;
            newHeadNode->leftL = NULL;
            newHeadNode->rightL = NULL;
            newHeadNode->upL = NULL;
            newHeadNode->downL = NULL;
            tempHead_r = newHeadNode;
            preTempHead_r = newHeadNode;
            head_r = newHeadNode;
            temp_r = newHeadNode;
            current_r = newHeadNode;
            listPosition_r[tempHead_r->rank-1] = tempHead_r;
        }
        else{
            newHeadNode->rank = map[i][m-1].rank;
            newHeadNode->toast = map[i][m-1].toast;
            newHeadNode->close = map[i][m-1].close;
            newHeadNode->visited = map[i][m-1].visited;
            newHeadNode->leftL = NULL;
            newHeadNode->rightL = NULL;
            newHeadNode->upL = preTempHead_r;
            preTempHead_r->downL = newHeadNode;
            newHeadNode->downL = NULL;
            tempHead_r = newHeadNode;
            current_r = newHeadNode;
            temp_r = preTempHead_r;
            listPosition_r[tempHead_r->rank-1] = tempHead_r;
        }
        
        for (int j = m - 1; j >= 0; j--){
            // escape first node
            if (j == m - 1){
                continue;
            } 

            listNode *newNode = (listNode*)malloc(sizeof(listNode));

            if (i == n - 1){
                newNode->rank = map[i][j].rank;
                newNode->toast = map[i][j].toast;
                newNode->close = map[i][j].close;
                newNode->visited = map[i][j].visited;
                newNode->leftL = current_r;
                current_r->rightL = newNode;
                current_r = current_r->rightL;
                temp_r = temp_r->rightL;
                listPosition_r[current_r->rank-1] = current_r;
            }
            else{
                newNode->rank = map[i][j].rank;
                newNode->toast = map[i][j].toast;
                newNode->close = map[i][j].close;
                newNode->visited = map[i][j].visited;
                newNode->leftL = current_r;
                current_r->rightL = newNode;
                current_r = current_r->rightL;
                temp_r = temp_r->rightL;
                current_r->upL = temp_r;
                temp_r->downL = current_r;
                listPosition_r[current_r->rank-1] = current_r;
            }
        }
        preTempHead_r = tempHead_r;
    }

    // rotate
    for (int i = 0; i < r; i++){
        scanf("%d %d", &r_k, &l_k);
        listRotation(&head, &head_r, listPosition, listPosition_r, r_k, l_k);
    }

    // transfer linked list back to array
    listToArray(map, position, head, n, m);

    // relative position initialization
    relativePositionForTrain2(map, position, n, m);

    // train2
    for (int i = 0; i < t2; i++){
        scanf("%d %d %d", &r_k, &l_k, &s_k);
        eatToast(map, position, r_k, l_k, s_k, round);
        round++;
    }

    // map print
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("%d ", map[i][j].toast);
        }
        printf("\n");
    } 

    return 0;
}

// function
void eatToast(node **map, coordinate *position,int r_k, int l_k, int s_k, int round) {
    int center_i = position[r_k-1].row;
    int center_j = position[r_k-1].col;
    map[center_i][center_j].visited = round;

    int temp_i = 0;
    int temp_j = 0;

    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;
    int up_distance = 0;
    int down_distance = 0;
    int left_distance = 0;
    int right_distance = 0;
    int length = 0;

    // day k
    while (length < l_k){
        up = map[center_i][center_j].up;
        down = map[center_i][center_j].down;
        left = map[center_i][center_j].left;
        right = map[center_i][center_j].right;
        up_distance = map[center_i][center_j].up_distance;
        down_distance = map[center_i][center_j].down_distance;
        left_distance = map[center_i][center_j].left_distance;
        right_distance = map[center_i][center_j].right_distance;
        int *bestChoice = chooseNext(map, position, up, down, left, right, up_distance, down_distance, left_distance, right_distance, round, r_k);
        
        if (bestChoice[1] >= 999999){
            break;
        }
        
        length += 1;

        // eat toast, update the center & direction
        center_i = position[bestChoice[0]-1].row;
        center_j = position[bestChoice[0]-1].col;
        map[center_i][center_j].toast -= s_k;    // eat toast
        map[center_i][center_j].visited = round; // update the whether the bakery is visited or not

        if (map[center_i][center_j].toast <= 0){
            map[center_i][center_j].close = 0; // close bakery
            map[center_i][center_j].toast = 0;
            // update the direction & distance
            // up & down
            if (map[center_i][center_j].up != -1 && map[center_i][center_j].down != -1){
                // up
                temp_i = position[map[center_i][center_j].up-1].row;
                temp_j = position[map[center_i][center_j].up-1].col;
                map[temp_i][temp_j].down = map[center_i][center_j].down;
                map[temp_i][temp_j].down_distance = (map[center_i][center_j].down_distance + map[center_i][center_j].up_distance);
                // down
                temp_i = position[map[center_i][center_j].down-1].row;
                temp_j = position[map[center_i][center_j].down-1].col;
                map[temp_i][temp_j].up = map[center_i][center_j].up;
                map[temp_i][temp_j].up_distance = (map[center_i][center_j].up_distance + map[center_i][center_j].down_distance);
            }
            else if (map[center_i][center_j].up != -1 && map[center_i][center_j].down == -1){
                temp_i = position[map[center_i][center_j].up-1].row;
                temp_j = position[map[center_i][center_j].up-1].col;
                map[temp_i][temp_j].down = map[center_i][center_j].down;
                map[temp_i][temp_j].down_distance = (map[center_i][center_j].down_distance + map[center_i][center_j].up_distance);
            }
            else if (map[center_i][center_j].up == -1 && map[center_i][center_j].down != -1){
                temp_i = position[map[center_i][center_j].down-1].row;
                temp_j = position[map[center_i][center_j].down-1].col;
                map[temp_i][temp_j].up = map[center_i][center_j].up;
                map[temp_i][temp_j].up_distance = (map[center_i][center_j].up_distance + map[center_i][center_j].down_distance);
            }

            // left & right
            if (map[center_i][center_j].left != -1 && map[center_i][center_j].right != -1){
                // left
                temp_i = position[map[center_i][center_j].left-1].row;
                temp_j = position[map[center_i][center_j].left-1].col;
                map[temp_i][temp_j].right = map[center_i][center_j].right;
                map[temp_i][temp_j].right_distance = (map[center_i][center_j].right_distance + map[center_i][center_j].left_distance);
                // right
                temp_i = position[map[center_i][center_j].right-1].row;
                temp_j = position[map[center_i][center_j].right-1].col;
                map[temp_i][temp_j].left = map[center_i][center_j].left;
                map[temp_i][temp_j].left_distance = (map[center_i][center_j].left_distance + map[center_i][center_j].right_distance);
            }
            else if (map[center_i][center_j].left != -1 && map[center_i][center_j].right == -1){
                temp_i = position[map[center_i][center_j].left-1].row;
                temp_j = position[map[center_i][center_j].left-1].col;
                map[temp_i][temp_j].right = map[center_i][center_j].right;
                map[temp_i][temp_j].right_distance = (map[center_i][center_j].right_distance + map[center_i][center_j].left_distance);
            }
            else if (map[center_i][center_j].left == -1 && map[center_i][center_j].right != -1){
                temp_i = position[map[center_i][center_j].right-1].row;
                temp_j = position[map[center_i][center_j].right-1].col;
                map[temp_i][temp_j].left = map[center_i][center_j].left;
                map[temp_i][temp_j].left_distance = (map[center_i][center_j].left_distance + map[center_i][center_j].right_distance);
            } 
        }
    }
}

int *chooseNext(node **map, coordinate *position, int up, int down, int left, int right, int up_distance, int down_distance, int left_distance, int right_distance, int round, int r_k){
    int *result = (int*)malloc(2 * sizeof(int));
    int min_rank = 999999;
    int min_distance = 999999;
    int center_i , center_j;

    // compare
    if (up != -1){
        // check up
        center_i = position[up-1].row;
        center_j = position[up-1].col;
        while (map[center_i][center_j].visited == round){
            up = map[center_i][center_j].up;
            up_distance += map[center_i][center_j].up_distance;
            if (up == -1){
               break;
            }
            center_i = position[up-1].row;
            center_j = position[up-1].col;
        }

        if (up != -1){
            if (up_distance < min_distance){
                min_rank = up;
                min_distance = up_distance;
            }
            else if (up_distance == min_distance){
                if (up <= min_rank){
                    min_rank = up;
                    min_distance = up_distance;
                }
            }
        }
    }

    if (down != -1){
        // check down
        center_i = position[down-1].row;
        center_j = position[down-1].col;
        while (map[center_i][center_j].visited == round){
            down = map[center_i][center_j].down;
            down_distance += map[center_i][center_j].down_distance;
            if (down == -1){
               break;
            }
            center_i = position[down-1].row;
            center_j = position[down-1].col;
        }

        if (down != -1){
            if (down_distance < min_distance){
                min_rank = down;
                min_distance = down_distance;
            }
            else if (down_distance == min_distance){
                if (down <= min_rank){
                    min_rank = down;
                    min_distance = down_distance;
                }
            }
        }
    }
    
    if (left != -1){
        // check left
        center_i = position[left-1].row;
        center_j = position[left-1].col;
        while (map[center_i][center_j].visited == round){
            left = map[center_i][center_j].left;
            left_distance += map[center_i][center_j].left_distance;
            if (left == -1){
               break;
            }
            center_i = position[left-1].row;
            center_j = position[left-1].col;
        }

        if (left != -1){
            if (left_distance < min_distance){
                min_rank = left;
                min_distance = left_distance;
            }
            else if (left_distance == min_distance){
                if (left <= min_rank){
                    min_rank = left;
                    min_distance = left_distance;
                }
            }
        }
    }
    
    if (right != -1){
        // check right
        center_i = position[right-1].row;
        center_j = position[right-1].col;
        while (map[center_i][center_j].visited == round){
            right = map[center_i][center_j].right;
            right_distance += map[center_i][center_j].right_distance;
            if (right == -1){
               break;
            }
            center_i = position[right-1].row;
            center_j = position[right-1].col;
        }

        if (right != -1){
            if (right_distance < min_distance){
                min_rank = right;
                min_distance = right_distance;
            }
            else if (right_distance == min_distance){
                if (right <= min_rank){
                    min_rank = right;
                    min_distance = right_distance;
                }
            }
        }
    }

    result[0] = min_rank;
    result[1] = min_distance;

    return result;
}

void relativePosition(node **map, int n, int m){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            // up
            if (i == 0){
                map[i][j].up = -1;
                map[i][j].up_distance = 999999; // infinity
            } 
            else {
                map[i][j].up = map[i-1][j].rank;
                map[i][j].up_distance = 1;
            }

            // down
            if (i == n-1){
                map[i][j].down = -1;
                map[i][j].down_distance = 999999;
            } 
            else {
                map[i][j].down = map[i+1][j].rank;
                map[i][j].down_distance = 1;
            }

            // left
            if (j == 0){
                map[i][j].left = -1;
                map[i][j].left_distance = 999999;
            } 
            else {
                map[i][j].left = map[i][j-1].rank;
                map[i][j].left_distance = 1;
            }

            // right
            if (j == m-1){
                map[i][j].right = -1;
                map[i][j].right_distance = 999999;
            } 
            else {
                map[i][j].right = map[i][j+1].rank;
                map[i][j].right_distance = 1;
            }
        }
    }
}

void relativePositionForTrain2(node **map, coordinate *position, int n, int m){
    // initialize relative position
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            // up
            if (i == 0){
                map[i][j].up = -1;
                map[i][j].up_distance = 999999; // infinity
            } 
            else {
                map[i][j].up = map[i-1][j].rank;
                map[i][j].up_distance = 1;
            }

            // down
            if (i == n-1){
                map[i][j].down = -1;
                map[i][j].down_distance = 999999;
            } 
            else {
                map[i][j].down = map[i+1][j].rank;
                map[i][j].down_distance = 1;
            }

            // left
            if (j == 0){
                map[i][j].left = -1;
                map[i][j].left_distance = 999999;
            } 
            else {
                map[i][j].left = map[i][j-1].rank;
                map[i][j].left_distance = 1;
            }

            // right
            if (j == m-1){
                map[i][j].right = -1;
                map[i][j].right_distance = 999999;
            } 
            else {
                map[i][j].right = map[i][j+1].rank;
                map[i][j].right_distance = 1;
            }

        }
    }

    int temp_i = 0;
    int temp_j = 0;

    // deal with relative bakery position
    int count = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            // closed bakery
            if (map[i][j].close == 0){
                // up and down
                if (map[i][j].up != -1 && map[i][j].down != -1){
                    // up
                    temp_i = position[map[i][j].up-1].row;
                    temp_j = position[map[i][j].up-1].col;
                    map[temp_i][temp_j].down = map[i][j].down;
                    map[temp_i][temp_j].down_distance = (map[i][j].down_distance + map[i][j].up_distance);
                    // down
                    temp_i = position[map[i][j].down-1].row;
                    temp_j = position[map[i][j].down-1].col;
                    map[temp_i][temp_j].up = map[i][j].up;
                    map[temp_i][temp_j].up_distance = (map[i][j].up_distance + map[i][j].down_distance);
                }  
                else if (map[i][j].up != -1 && map[i][j].down == -1){
                    temp_i = position[map[i][j].up-1].row;
                    temp_j = position[map[i][j].up-1].col;
                    map[temp_i][temp_j].down = map[i][j].down;
                    map[temp_i][temp_j].down_distance = (map[i][j].down_distance + map[i][j].up_distance);
                }
                else if (map[i][j].up == -1 && map[i][j].down != -1){
                    temp_i = position[map[i][j].down-1].row;
                    temp_j = position[map[i][j].down-1].col;
                    map[temp_i][temp_j].up = map[i][j].up;
                    map[temp_i][temp_j].up_distance = (map[i][j].up_distance + map[i][j].down_distance);
                }

                // left and right
                if (map[i][j].left != -1 && map[i][j].right != -1){
                    // left
                    temp_i = position[map[i][j].left-1].row;
                    temp_j = position[map[i][j].left-1].col;
                    map[temp_i][temp_j].right = map[i][j].right;
                    map[temp_i][temp_j].right_distance = (map[i][j].right_distance + map[i][j].left_distance);
                    // right
                    temp_i = position[map[i][j].right-1].row;
                    temp_j = position[map[i][j].right-1].col;
                    map[temp_i][temp_j].left = map[i][j].left;
                    map[temp_i][temp_j].left_distance = (map[i][j].left_distance + map[i][j].right_distance);
                }
                else if (map[i][j].left != -1 && map[i][j].right == -1){
                    temp_i = position[map[i][j].left-1].row;
                    temp_j = position[map[i][j].left-1].col;
                    map[temp_i][temp_j].right = map[i][j].right;
                    map[temp_i][temp_j].right_distance = (map[i][j].right_distance + map[i][j].left_distance);
                }
                else if (map[i][j].left == -1 && map[i][j].right != -1){
                    temp_i = position[map[i][j].right-1].row;
                    temp_j = position[map[i][j].right-1].col;
                    map[temp_i][temp_j].left = map[i][j].left;
                    map[temp_i][temp_j].left_distance = (map[i][j].left_distance + map[i][j].right_distance);
                }
            }
        } 
    }
}

void listRotation(listNode** head, listNode** head_r, listNode** listPosition, listNode** listPosition_r, int r_k, int l_k){
    if (l_k == 1){
        return;
    }
    
    listNode *center;
    listNode *center_r;
    listNode *leftUpHead;
    listNode *leftUpHead_r;
    listNode *rightDownHead;
    listNode *rightDownHead_r;
    listNode *rightUpHead;
    listNode *rightUpHead_r;
    listNode *leftDownHead;
    listNode *leftDownHead_r;
    listNode *tempU;
    listNode *tempD;
    listNode *tempL;
    listNode *tempR;
    int length = l_k/2;
    int count = 0;
    
    center = listPosition[r_k-1];
    center_r = listPosition_r[r_k-1];
    leftUpHead = center;
    leftUpHead_r = center_r;
    rightDownHead = center;
    rightDownHead_r = center_r;
    rightUpHead = center;
    rightUpHead_r = center_r;
    leftDownHead = center;
    leftDownHead_r = center_r;


    // left & right
    for (int i = 0; i < length; i++){
        leftUpHead = leftUpHead->leftL;
        leftUpHead_r = leftUpHead_r->leftL;
        rightUpHead = rightUpHead->rightL;
        rightUpHead_r = rightUpHead_r->rightL;
        leftDownHead = leftDownHead->leftL;
        leftDownHead_r = leftDownHead_r->leftL;
        rightDownHead = rightDownHead->rightL;
        rightDownHead_r = rightDownHead_r->rightL;
    }

    // up and down
    for (int i = 0; i < length; i++){
        leftUpHead = leftUpHead->upL;
        leftUpHead_r = leftUpHead_r->upL;
        rightUpHead = rightUpHead->upL;
        rightUpHead_r = rightUpHead_r->upL;
        leftDownHead = leftDownHead->downL;
        leftDownHead_r = leftDownHead_r->downL;
        rightDownHead = rightDownHead->downL;
        rightDownHead_r = rightDownHead_r->downL;
    }
    
    if (leftUpHead == *head ){
        *head = leftUpHead_r;
    }
    
    else if (leftUpHead_r == *head){
        *head = leftUpHead;
    }

    if (leftUpHead_r == *head_r){
        *head_r = leftUpHead;
    }
    else if (leftUpHead == *head_r){
        *head_r = leftUpHead_r;
    }

    for (int i = 1; i < l_k; i++){
        if (i == 1){
            // upLeft
            tempU = leftUpHead_r->upL;
            tempL = leftUpHead_r->leftL;
            leftUpHead_r->upL = leftUpHead->upL;
            if (leftUpHead->upL != NULL){
                leftUpHead->upL->downL = leftUpHead_r;
            }
            leftUpHead_r->leftL = leftUpHead->leftL;
            if (leftUpHead->leftL != NULL){
                leftUpHead->leftL->rightL = leftUpHead_r;
            }
            leftUpHead->upL = tempU;
            if (tempU != NULL){
                tempU->downL = leftUpHead;
            }
            leftUpHead->leftL = tempL;
            if (tempL != NULL){
                tempL->rightL = leftUpHead;
            }

            leftUpHead = leftUpHead->downL;
            leftUpHead_r = leftUpHead_r->downL;
            // upRight
            tempU = rightUpHead_r->upL;
            tempR = rightUpHead_r->rightL;
            rightUpHead_r->upL = rightUpHead->upL;
            if (rightUpHead->upL != NULL){
                rightUpHead->upL->downL = rightUpHead_r;
            }
            rightUpHead_r->rightL = rightUpHead->rightL;
            if (rightUpHead->rightL != NULL){
                rightUpHead->rightL->leftL = rightUpHead_r;
            }
            rightUpHead->upL = tempU;
            if (tempU != NULL){
                tempU->downL = rightUpHead;
            }
            rightUpHead->rightL = tempR;
            if (tempR != NULL){
                tempR->leftL = rightUpHead;
            }

            rightUpHead = rightUpHead->leftL;
            rightUpHead_r = rightUpHead_r->leftL;
            // downLeft
            tempD = leftDownHead_r->downL;
            tempL = leftDownHead_r->leftL;
            leftDownHead_r->downL = leftDownHead->downL;
            if (leftDownHead->downL != NULL){
                leftDownHead->downL->upL = leftDownHead_r;
            }
            leftDownHead_r->leftL = leftDownHead->leftL;
            if (leftDownHead->leftL != NULL){
                leftDownHead->leftL->rightL = leftDownHead_r;
            }
            leftDownHead->downL = tempD;
            if (tempD != NULL){
                tempD->upL = leftDownHead;
            }
            leftDownHead->leftL = tempL;
            if (tempL != NULL){
                tempL->rightL = leftDownHead;
            }

            leftDownHead = leftDownHead->rightL;
            leftDownHead_r = leftDownHead_r->rightL;
            // downRight
            tempD = rightDownHead_r->downL;
            tempR = rightDownHead_r->rightL;
            rightDownHead_r->downL = rightDownHead->downL;
            if (rightDownHead->downL != NULL){
                rightDownHead->downL->upL = rightDownHead_r;
            }
            rightDownHead_r->rightL = rightDownHead->rightL;
            if (rightDownHead->rightL != NULL){
                rightDownHead->rightL->leftL = rightDownHead_r;
            }
            rightDownHead->downL = tempD;
            if (tempD != NULL){
                tempD->upL = rightDownHead;
            }
            rightDownHead->rightL = tempR;
            if (tempR != NULL){
                tempR->leftL = rightDownHead;
            }

            rightDownHead = rightDownHead->upL;
            rightDownHead_r = rightDownHead_r->upL;
            continue;
        }
        // upLeft
        tempL = leftUpHead_r->leftL;
        leftUpHead_r->leftL = leftUpHead->leftL;
        if (leftUpHead->leftL != NULL){
            leftUpHead->leftL->rightL = leftUpHead_r;
        }
        leftUpHead->leftL = tempL;
        if (tempL != NULL){
            tempL->rightL = leftUpHead;
        }

        leftUpHead = leftUpHead->downL;
        leftUpHead_r = leftUpHead_r->downL;
        // upRight
        tempU = rightUpHead_r->upL;
        rightUpHead_r->upL = rightUpHead->upL;
        if (rightUpHead->upL != NULL){
            rightUpHead->upL->downL = rightUpHead_r;
        }
        rightUpHead->upL = tempU;
        if (tempU != NULL){
            tempU->downL = rightUpHead;
        }

        rightUpHead = rightUpHead->leftL;
        rightUpHead_r = rightUpHead_r->leftL;
        // downLeft
        tempD = leftDownHead_r->downL;
        leftDownHead_r->downL = leftDownHead->downL;
        if (leftDownHead->downL != NULL){
            leftDownHead->downL->upL = leftDownHead_r;
        }
        leftDownHead->downL = tempD;
        if (tempD != NULL){
            tempD->upL = leftDownHead;
        }

        leftDownHead = leftDownHead->rightL;
        leftDownHead_r = leftDownHead_r->rightL;
        // downRight
        tempR = rightDownHead_r->rightL;
        rightDownHead_r->rightL = rightDownHead->rightL;
        if (rightDownHead->rightL != NULL){
            rightDownHead->rightL->leftL = rightDownHead_r;
        }
        rightDownHead->rightL = tempR;
        if (tempR != NULL){
            tempR->leftL = rightDownHead;
        }

        rightDownHead = rightDownHead->upL;
        rightDownHead_r = rightDownHead_r->upL;
    }
}

void listToArray(node** map, coordinate* position, listNode* head, int n, int m){
    // print 4-way linked list
    listNode *tempHead = head;
    listNode *current = head;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            map[i][j].rank = current->rank;
            map[i][j].toast = current->toast;
            map[i][j].close = current->close;
            map[i][j].visited = current->visited;
            position[map[i][j].rank-1].row = i;
            position[map[i][j].rank-1].col = j;
            current = current->rightL;
        }
        
        tempHead = tempHead->downL;
        current = tempHead;
    } 
}