#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

// index of cat
typedef struct node{ 
    long long appetite;
    long long color;
    struct list_node *address;
    int index;
} node;

typedef struct list_node{ 
    long long appetite;
    long long color;
    int index;
    struct list_node *next;
    struct list_node *prev;
} list_node;


// color
typedef struct color_node{ 
    long long key;  // color id
    int number;
    struct color_appetite_node *c_head;
    int c_tail;
    int h;
    int t;
} color_node;

typedef struct color_appetite_node{ 
    long long appetite;  // color id
    struct list_node *address;
} color_appetite_node;

int compare (const void * , const void *);

int binarySearch_color(color_node *color_list, long long, int, int);
int binarySearch_color_smaller(color_node *color_list, long long, int, int, int);
int binarySearch_color_bigger(color_node *color_list, long long, int, int, int);
int binarySearch_color_appetite(color_node *color_list, long long, int, int, int);



int main(){
    // initialize variables
    int cat = 0;
    int step = 0;
    long long l_j = 0;
    long long r_j = 0;
    long long c_j = 0;
    long long k_j = 0;
    int s_j = 0;
    int t_j = 0;
    int type = 0;
    long long input = 0;
    long long swap_color = 0;
    long long swap_appetite = 0;
    long long pre_swap_color = 0;
    long long pre_swap_appetite = 0;
    int swap_color_index = 0;
    int pre_swap_color_index = 0;
    int swap_appetite_index = 0;
    int pre_swap_appetite_index = 0;
    long long swap_temp = 0;
    scanf("%d %d", &cat, &step);

    // structure allocation
    node *cat_list = (node *)malloc(sizeof(node) * cat);  // index of cat
    node *appetite_list = (node *)malloc(sizeof(node) * cat);  // appetite
    color_node *color_list = (color_node *)malloc(sizeof(color_node) * cat);  // color

    // initialize index cat & appetite
    for (int i = 0; i < cat; i++){
        scanf("%lld", &input);
        cat_list[i].appetite = input;
        appetite_list[i].appetite = input;
        appetite_list[i].index = 
        i;
    }

    // initialize index cat & color
    for (int i = 0; i < cat; i++){
        scanf("%lld", &input);
        cat_list[i].color = input;
        appetite_list[i].color = input;
        color_list[i].key = input;
    }

    // qsort
    qsort(appetite_list, cat, sizeof(node), compare);
    qsort(color_list, cat, sizeof(color_node), compare);

    // print 
    // for (int i = 0; i < cat; i++){
    //     printf("appetite:%lld, index: %d\n", appetite_list[i].appetite, appetite_list[i].index);
    // }

    // printf("\n");
    // for (int i = 0; i < cat; i++){
    //     printf("%lld ", color_list[i].key);
    // }
    // printf("\n");

    // calculate number in color_list
    int color_tail = 0;
    for (int i = 0; i < cat; i++){
        color_list[i].number = 0;
        if (color_list[i].key == color_list[color_tail].key){
            color_list[color_tail].number += 1;
        }
        else{

            color_tail++;
            color_list[color_tail].key = color_list[i].key;
            color_list[color_tail].number += 1;
        }
    }

    // initialize appetites in color list
    for (int i = 0; i <= color_tail; i++){
        color_list[i].c_head = (color_appetite_node *)malloc(sizeof(color_appetite_node) * color_list[i].number);
        color_list[i].c_tail = -1;
        color_list[i].h = 0;
    }

    // construct appetite linked list
    list_node *appetite_linked_list = NULL;
    list_node *cursor = NULL;
    list_node *tail = NULL;
    for (int i = 0; i < cat; i++){
        list_node *new_node = (list_node *)malloc(sizeof(list_node));
        new_node->appetite = appetite_list[i].appetite;
        new_node->color = appetite_list[i].color;
        new_node->index = appetite_list[i].index;
        new_node->next = NULL;
        cat_list[appetite_list[i].index].address = new_node;
        appetite_list[i].address = new_node;
        if (appetite_linked_list == NULL){
            appetite_linked_list = new_node;
            cursor = new_node;
            cursor->prev = NULL;
        }
        else{
            cursor->next = new_node;
            new_node->prev = cursor;
            cursor = cursor->next;
        }
    }
    tail = cursor;

    // put appetites in color list
    long long color = 0;
    int color_index = 0;
    int color_index_tail = 0;
    for (int i = 0; i < cat; i++){
        color = appetite_list[i].color;
        color_index = binarySearch_color(color_list, color, 0, color_tail);
        color_list[color_index].c_tail += 1;
        color_index_tail = color_list[color_index].c_tail;
        color_list[color_index].c_head[color_index_tail].appetite = appetite_list[i].appetite;
        color_list[color_index].c_head[color_index_tail].address = appetite_list[i].address;
        color_list[color_index].t = color_list[color_index].c_tail;
    }

    int smaller = 0;
    int bigger = 0;
    int temp_bigger = 0;
    for (int i = 0; i < step; i++){
        scanf("%d", &type);
        // questioning
        if (type == 1){
            scanf("%lld %lld %lld", &c_j, &l_j, &r_j);
            color_index = binarySearch_color(color_list, c_j, 0, color_tail);
            if (color_index == -1){
                printf("0\n");
            }
            else{
                smaller = binarySearch_color_smaller(color_list, l_j, color_list[color_index].h, color_list[color_index].t, color_index);
                bigger = binarySearch_color_bigger(color_list, r_j, color_list[color_index].h, color_list[color_index].t, color_index);
                if (smaller == -1 || bigger == -1){
                    printf("0\n");
                }
                else{
                    if (color_list[color_index].h < color_list[color_index].t){
                        printf("%d\n", bigger - smaller + 1);
                    }
                    else{
                        if (smaller >= color_list[color_index].h && bigger >= color_list[color_index].h){
                            if (smaller == color_list[color_index].c_tail+1 && bigger == color_list[color_index].c_tail+1){
                                printf("0\n");
                            }
                            else if (smaller != color_list[color_index].c_tail+1 && bigger == color_list[color_index].c_tail+1){
                                printf("%d\n", bigger - smaller);
                            }
                            else{
                                printf("%d\n", bigger - smaller + 1);
                            }
                        }
                        else if (smaller <= color_list[color_index].t && bigger <= color_list[color_index].t){
                            printf("%d\n", bigger - smaller + 1);
                        }
                        else if (smaller >= color_list[color_index].h && bigger <= color_list[color_index].t){
                            printf("%d\n", bigger + color_list[color_index].c_tail - smaller + 2);
                        }
                    }
                }
            }
        }

        // greedy
        else if (type == 2){
            int cat_list_pre_index = 0;
            int cat_list_index = 0;
            list_node *pre_swap = NULL;
            list_node *swap = NULL;
            scanf("%lld", &k_j);
            if (cat_list[k_j].appetite != tail->appetite){
                cat_list_pre_index = k_j;
                pre_swap = cat_list[k_j].address;
                swap = pre_swap->next;
                cat_list_index = swap->index;

                // pre_swap
                pre_swap_appetite = pre_swap->appetite;
                pre_swap_color = pre_swap->color;
                pre_swap_color_index = binarySearch_color(color_list, pre_swap_color, 0, color_tail);
                pre_swap_appetite_index = binarySearch_color_appetite(color_list, pre_swap_appetite, color_list[pre_swap_color_index].h, color_list[pre_swap_color_index].t, pre_swap_color_index);
                // swap
                swap_appetite = swap->appetite;
                swap_color = swap->color;
                swap_color_index = binarySearch_color(color_list, swap_color, 0, color_tail);
                swap_appetite_index = binarySearch_color_appetite(color_list, swap_appetite, color_list[swap_color_index].h, color_list[swap_color_index].t, swap_color_index);
                // swapping in cat list
                swap_temp = cat_list[cat_list_pre_index].appetite;
                cat_list[cat_list_pre_index].appetite = cat_list[cat_list_index].appetite;
                cat_list[cat_list_index].appetite = swap_temp;
                cat_list[cat_list_pre_index].address = swap;
                swap->index = cat_list_pre_index;
                cat_list[cat_list_index].address = pre_swap;
                pre_swap->index = cat_list_index;
                // swapping in linked list
                swap_temp = pre_swap->color;
                pre_swap->color = swap->color;
                swap->color = swap_temp;
                // swapping in color list
                if (swap->color != pre_swap->color){
                    swap_temp = color_list[pre_swap_color_index].c_head[pre_swap_appetite_index].appetite;
                    color_list[pre_swap_color_index].c_head[pre_swap_appetite_index] = color_list[swap_color_index].c_head[swap_appetite_index];
                    color_list[swap_color_index].c_head[swap_appetite_index].appetite = swap_temp;
                    color_list[pre_swap_color_index].c_head[pre_swap_appetite_index].address = swap;
                    color_list[swap_color_index].c_head[swap_appetite_index].address = pre_swap;
                }
            }
        }

        else if (type == 3){
            scanf("%lld %d %d", &c_j, &s_j, &t_j);
            color_index = binarySearch_color(color_list, c_j, 0, color_tail);
            color_appetite_node* inside_largest = NULL;
            color_appetite_node* inside_smallest = NULL;
            list_node* outside_target = NULL;
            list_node* outside_pre_target = NULL;
            list_node* outside_largest = NULL;
            list_node* outside_smallest = NULL;
            // choose the largest one
            if (s_j == 1){
                inside_largest = &color_list[color_index].c_head[color_list[color_index].t];
                // success
                if (t_j == 1){
                    outside_target = inside_largest->address;
                    outside_largest = tail;
                    if (outside_largest->appetite == outside_target->appetite){
                        outside_target->appetite += 1;
                        inside_largest->appetite = outside_target->appetite;
                        cat_list[outside_target->index].appetite = outside_target->appetite;
                    }
                    else{
                        outside_pre_target = outside_target->prev;
                        if (outside_pre_target == NULL){
                            appetite_linked_list = outside_target->next;
                        }
                        else{
                            outside_pre_target->next = outside_target->next;
                        }
                        outside_target->next->prev = outside_pre_target;
                        // move node to the tail of linked list
                        outside_largest->next = outside_target;
                        outside_target->prev = outside_largest;
                        outside_target->next = NULL;
                        tail = outside_target;
                        outside_target->appetite = outside_largest->appetite + 1;
                        inside_largest->appetite = outside_target->appetite;
                        cat_list[outside_target->index].appetite = outside_target->appetite;
                    }
                }
                // failed
                else{
                    outside_target = inside_largest->address;
                    outside_smallest = appetite_linked_list;
                    outside_largest = tail;
                    if (outside_smallest->appetite == outside_target->appetite){
                        outside_target->appetite -= 1;
                        inside_largest->appetite = outside_target->appetite;
                        cat_list[outside_target->index].appetite = outside_target->appetite;
                    }
                    else{
                        if (outside_largest->appetite == outside_target->appetite){
                            tail = tail->prev;
                            tail->next = NULL;
                        }
                        else{
                            outside_pre_target = outside_target->prev;
                            outside_pre_target->next = outside_target->next;
                            outside_target->next->prev = outside_pre_target;
                        }      
                        // move node to the head of linked list
                        outside_smallest->prev = outside_target;
                        outside_target->next = outside_smallest;
                        outside_target->prev = NULL;
                        appetite_linked_list = outside_target;
                        outside_target->appetite = outside_smallest->appetite - 1;
                        inside_largest->appetite = outside_target->appetite;
                        cat_list[outside_target->index].appetite = outside_target->appetite;
                        // change h and t in color list
                        if (color_list[color_index].h == 0){
                            color_list[color_index].h =color_list[color_index].t;
                            if (color_list[color_index].t != 0){
                                color_list[color_index].t = color_list[color_index].t - 1;
                            }
                        }
                        else{
                            color_list[color_index].h = color_list[color_index].h - 1;
                            if (color_list[color_index].t == 0){
                                color_list[color_index].t = color_list[color_index].c_tail;
                            }
                            else{
                                color_list[color_index].t = color_list[color_index].t - 1;
                            }
                        }
                    }
                }
            }

            // choose the smallest one
            else if (s_j == 0){
                inside_smallest = &color_list[color_index].c_head[color_list[color_index].h];
                // success
                if (t_j == 1){
                    outside_target = inside_smallest->address;
                    outside_largest = tail;
                    outside_smallest = appetite_linked_list;
                    if (outside_smallest->appetite == outside_target->appetite){
                        outside_target->appetite = outside_largest->appetite +1;
                        outside_target->next->prev = NULL;
                        appetite_linked_list = outside_target->next;
                        outside_largest->next = outside_target;
                        outside_target->prev = outside_largest;
                        outside_target->next = NULL;
                        tail = outside_target;
                        inside_smallest->appetite = outside_target->appetite;
                        cat_list[outside_target->index].appetite = outside_target->appetite;
                    }
                    else if (outside_largest->appetite == outside_target->appetite){
                        outside_target->appetite += 1;
                        inside_smallest->appetite = outside_target->appetite;
                        cat_list[outside_target->index].appetite = outside_target->appetite;
                    }
                    else{
                        outside_pre_target = outside_target->prev;
                        outside_pre_target->next = outside_target->next;
                        outside_target->next->prev = outside_pre_target;
                        // move node to the tail of linked list
                        outside_largest->next = outside_target;
                        outside_target->prev = outside_largest;
                        outside_target->next = NULL;
                        tail = outside_target;
                        outside_target->appetite = outside_largest->appetite + 1;
                        inside_smallest->appetite = outside_target->appetite;
                        cat_list[outside_target->index].appetite = outside_target->appetite;
                    }
                    // change h and t in color list
                    if (color_list[color_index].t == color_list[color_index].c_tail){
                        color_list[color_index].t = color_list[color_index].h;
                        if (color_list[color_index].h != color_list[color_index].c_tail){
                            color_list[color_index].h = color_list[color_index].h + 1;
                        }      
                    }
                    else{
                        color_list[color_index].t = color_list[color_index].t + 1;
                        if (color_list[color_index].h == color_list[color_index].c_tail){
                            color_list[color_index].h = 0;
                        }
                        else{
                            color_list[color_index].h = color_list[color_index].h + 1;
                        }
                    }
                }
                // failed
                else{
                    outside_target = inside_smallest->address;
                    outside_smallest = appetite_linked_list;
                    outside_largest = tail;
                    if (outside_smallest->appetite == outside_target->appetite){
                        outside_target->appetite -= 1;
                        inside_smallest->appetite = outside_target->appetite;
                        cat_list[outside_target->index].appetite = outside_target->appetite;
                    }
                    else if (outside_largest->appetite == outside_target->appetite){
                        outside_target->appetite = outside_smallest->appetite - 1;
                        outside_target->prev->next = NULL;
                        tail = outside_target->prev;
                        outside_smallest->prev = outside_target;
                        outside_target->next = outside_smallest;
                        outside_target->prev = NULL;
                        appetite_linked_list = outside_target;
                        inside_smallest->appetite = outside_target->appetite;
                    }
                    else{
                        outside_pre_target = outside_target->prev;
                        outside_pre_target->next = outside_target->next;
                        outside_target->next->prev = outside_pre_target;
                        // move node to the head of linked list
                        outside_smallest->prev = outside_target;
                        outside_target->next = outside_smallest;
                        outside_target->prev = NULL;
                        appetite_linked_list = outside_target;
                        outside_target->appetite = outside_smallest->appetite - 1;
                        inside_smallest->appetite = outside_target->appetite;
                        cat_list[outside_target->index].appetite = outside_target->appetite;
                    }
                }
            }
        }

    }


    return 0;
}

// function
int compare(const void * a, const void * b){
    if( (*(long long int*)a - *(long long int*)b) < 0){
        return -1;
    }
    else if((*(long long int*)a - *(long long int*)b) > 0){
        return 1;
    }
    else{
        return 0;
    }
}

// binary search
int binarySearch_color(color_node *color_list, long long color, int l, int r){
    if (l > r){
        return -1;
    }
    int m = (l + r) / 2;
    if (color_list[m].key == color){
        return m;
    }
    else if (color_list[m].key > color){
        return binarySearch_color(color_list, color, l, m - 1);
    }
    else{
        return binarySearch_color(color_list, color, m + 1, r);
    }
}

int binarySearch_color_smaller(color_node * color_list, long long key, int h, int t, int index){
    if (color_list[index].c_head[color_list[index].t].appetite < key){
        return -1;
    }
    int left = 0;
    int right = color_list[index].c_tail;
    int m = 0;
    int l = 0;
    int r = 0;
    if (h <= t){
        while (h <= t){
            m = (h + t) / 2;
            if (color_list[index].c_head[m].appetite == key){
                return m;
            }
            else if (color_list[index].c_head[m].appetite > key){
                if (m == 0){
                    return 0;
                }
                else{
                    t = m - 1;
                }
            }
            else if (color_list[index].c_head[m].appetite < key){
                if (m == color_list[index].c_tail){
                    return -1;
                }
                else{
                    h = m + 1;
                }  
            }
        }
        return h;
    }
    else{
        if (color_list[index].c_head[left].appetite <= key){
            l = left;
            r = t;
            while (left <= t){
                m = (left + t) / 2;
                if (color_list[index].c_head[m].appetite == key){
                    return m;
                }
                else if (color_list[index].c_head[m].appetite > key){
                    t = m - 1;
                }
                else if (color_list[index].c_head[m].appetite < key){
                    if (m == r){
                        return -1;
                    }
                    else{
                        left = m + 1;
                    }  
                }
            }
            return left;
        }   
        else {
            while (h <= right){
                l = h;
                r = right;
                m = (h + right) / 2;
                if (color_list[index].c_head[m].appetite == key){
                    return m;
                }
                else if (color_list[index].c_head[m].appetite > key){
                    if (m == l){
                        return l;
                    }
                    else{
                        right = m - 1;
                    }
                }
                else if (color_list[index].c_head[m].appetite < key){
                    if (m == r){
                        return r+1;
                    }
                    else{
                        h = m + 1;
                    }  
                }
            }
            return h;
        }

    }
    
}

int binarySearch_color_bigger(color_node * color_list, long long key, int h, int t, int index){
    if (color_list[index].c_head[color_list[index].h].appetite > key){
        return -1;
    }
    int left = 0;
    int right = color_list[index].c_tail;
    int m = 0;
    int l = 0;
    int r = 0;
    if (h <= t){
        while (h <= t){
            m = (h + t) / 2;
            if (color_list[index].c_head[m].appetite == key){
                return m;
            }
            else if (color_list[index].c_head[m].appetite > key){
                if (m == 0){
                    return -1;
                }
                else{
                    t = m - 1;
                }
            }
            else if (color_list[index].c_head[m].appetite < key){
                if (m == color_list[index].c_tail){
                    return m;
                }
                else{
                    h = m + 1;
                }
            }
        }
        return t;
    }
    else{
        if (key <= color_list[index].c_head[right].appetite){
            l = h;
            r = right;
            while (h <= right){
                m = (h + right) / 2;
                if (color_list[index].c_head[m].appetite == key){
                    return m;
                }
                else if (color_list[index].c_head[m].appetite > key){
                    if (m == l){
                        return -1;
                    }
                    else{
                        right = m - 1;
                    }
                }
                else if (color_list[index].c_head[m].appetite < key){
                    h = m + 1;
                }
            }
            return right;
        }
        else{
            l = left;
            r = t;
            while (left <= t){
                m = (left + t) / 2;
                if (color_list[index].c_head[m].appetite == key){
                    return m;
                }
                else if (color_list[index].c_head[m].appetite > key){
                    if (m == l){
                        return right+1;
                    }
                    else{
                        t = m - 1;
                    }
                }
                else if (color_list[index].c_head[m].appetite < key){
                    if (m == r){
                        return m;
                    }
                    else{
                        left = m + 1;
                    }
                }
            }
            return t;
        }
    }
}


// waiting to be rectified
int binarySearch_color_appetite(color_node * color_list, long long key, int h, int t, int index){
    int left = 0;
    int right = color_list[index].c_tail;
    int m = 0;
    if (h <= t){
        while (h <= t){
            m = (h + t) / 2;
            if (color_list[index].c_head[m].appetite == key){
                return m;
            }
            else if (color_list[index].c_head[m].appetite > key){
                t = m - 1;
            }
            else if (color_list[index].c_head[m].appetite < key){
                h = m + 1;
            }
        }
        return -1;
    }
    else{
        if (key <= color_list[index].c_head[right].appetite){
            while (h <= right){
                m = (h + right) / 2;
                if (color_list[index].c_head[m].appetite == key){
                    return m;
                }
                else if (color_list[index].c_head[m].appetite > key){
                    right = m - 1;
                }
                else if (color_list[index].c_head[m].appetite < key){
                    h = m + 1;
                }
            }
            return -1;
        }
        else{
            while (left <= t){
                m = (left + t) / 2;
                if (color_list[index].c_head[m].appetite == key){
                    return m;
                }
                else if (color_list[index].c_head[m].appetite > key){
                    t = m - 1;
                }
                else if (color_list[index].c_head[m].appetite < key){
                    left = m + 1;
                }
            }
            return -1;
        }
    }
}