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

typedef struct { 
    int row;
    int col;
} coordinate;

void eatToast(node**, coordinate*, int, int, int, int);
void rotate(node**, coordinate*, int, int);
int *chooseNext(node**, coordinate*, int, int, int, int, int, int, int, int, int, int);
void relativePosition(node**, int, int);
void relativePositionForTrain2(node**, coordinate*, int , int);


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

    // rotate
    for (int i = 0; i < r; i++){
        scanf("%d %d", &r_k, &l_k);
        rotate(map, position, r_k, l_k);
    }
    
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

void rotate(node** map, coordinate* position, int r_k, int l_k){
    // find center
    int center_i = position[r_k-1].row;
    int center_j = position[r_k-1].col;

    node temp;

    int count = l_k / 2;
    int check = 0;

    for (int i = center_i - count, j = center_i + count; i < center_i + count; i++, j--){
        for (int k = center_j - count, l = center_j + count; k <= center_j + count; k++, l--){
            if (i == j && k == l){
                break;
            }
            
            temp = map[i][k];
            map[i][k] = map[j][l];
            map[j][l] = temp;

            position[map[j][l].rank-1].row = j;
            position[map[j][l].rank-1].col = l;
            position[map[i][k].rank-1].row = i;
            position[map[i][k].rank-1].col = k;

        }
        if (i == j){
            break;
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