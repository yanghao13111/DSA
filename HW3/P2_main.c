#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

typedef struct Knight{ 
    int attack;
    int health;
    int success;
    int attack_count;
    int death;
} Knight;

typedef struct Heap{ 
    int id;
    int health;
    int attack;
    int attack_count;
    long long resistance;
} Heap;

typedef struct Set{ 
    int parent;
    int size;
    int capacity;
    int attack_count;
    long long cumulative_attack;
    long long cumulative_been_attacked;
    Heap *knight_heap;
} Set;

int find_set(Set *set_list, int index);
void union_set(Knight *, Set *set_list, int index1, int index2);
int compare(int, int, int, Set *, int);

int main(){
    // variable declaration
    int knight = 0;
    int round = 0;
    int attacker = 0;
    int defender = 0;
    scanf("%d %d", &knight, &round);
    Knight *knight_list = (Knight*)malloc(sizeof(Knight)*knight);
    Set *set_list = (Set*)malloc(sizeof(Set)*knight);

    // initialize knight's health
    for(int i = 0; i < knight; i++){
        scanf("%d",&knight_list[i].health);
    }
    // initialize knight's attack
    for(int i = 0; i < knight; i++){
        scanf("%d",&knight_list[i].attack);
    }
    // initialize set
    for(int i = 0; i < knight; i++){
        set_list[i].cumulative_attack = knight_list[i].attack;
        set_list[i].size = 1;
        set_list[i].capacity = 1;
        set_list[i].parent = i;
        set_list[i].cumulative_been_attacked = 0;
        set_list[i].knight_heap = (Heap*)malloc(sizeof(Heap));
        set_list[i].knight_heap[0].id = i;
        set_list[i].knight_heap[0].health = knight_list[i].health;
        set_list[i].knight_heap[0].attack = knight_list[i].attack;
    }

    for (int i = 0; i < round; i++){
        scanf("%d %d", &attacker, &defender);
        attacker--;
        defender--;
        if (knight_list[attacker].death == 1 || knight_list[defender].death == 1){
            continue;
        }
        union_set(knight_list, set_list, attacker, defender);
    }

    // update success number
    for (int i = 0; i < knight; i++){
        if (knight_list[i].death != 1){
            knight_list[i].success = set_list[find_set(set_list, i)].attack_count + knight_list[i].attack_count;
        }
    }
    

    // print knight_list
    for(int i = 0; i < knight; i++){
        printf("%d ", knight_list[i].success);
    }
    
    return 0;
}

// function
int find_set(Set *set_list, int index){
    if(set_list[index].parent != index){
        set_list[index].parent = find_set(set_list, set_list[index].parent);
    }
    return set_list[index].parent;
}

void union_set(Knight* knight_list, Set *set_list, int index1, int index2){
    int check = 0;
    int root1 = find_set(set_list, index1);
    int root2 = find_set(set_list, index2);
    if(root1 == root2){
        return;
    }

    // roots are different
    set_list[root1].attack_count++;
    set_list[root2].cumulative_been_attacked = set_list[root2].cumulative_been_attacked + set_list[root1].cumulative_attack;  // update new been attacked

    // remove smallest element
    while (set_list[root2].cumulative_been_attacked >= set_list[root2].knight_heap[0].health){
        knight_list[set_list[root2].knight_heap[0].id].death = 1; // update death
        knight_list[set_list[root2].knight_heap[0].id].success = set_list[root2].knight_heap[0].attack_count + set_list[root2].attack_count; // update success number

        // check if element going to be removed is the last one
        if (set_list[root2].size == 1){
            check = 1;
            set_list[root2].cumulative_attack = 0;
            set_list[root2].size--;
            break;
        }

        // remove smallest element
        set_list[root2].cumulative_attack = set_list[root2].cumulative_attack - set_list[root2].knight_heap[0].attack;
        set_list[root2].knight_heap[0].id = set_list[root2].knight_heap[set_list[root2].size-1].id;
        set_list[root2].knight_heap[0].health = set_list[root2].knight_heap[set_list[root2].size-1].health;
        set_list[root2].knight_heap[0].attack = set_list[root2].knight_heap[set_list[root2].size-1].attack;
        set_list[root2].knight_heap[0].attack_count = set_list[root2].knight_heap[set_list[root2].size-1].attack_count;
        set_list[root2].size--;

        // heapify
        int i = 0;
        int smaller = 0;
        while (i <= set_list[root2].size - 1){
            smaller = compare(i, (2*i)+1, (2*i)+2, set_list, root2);
            if (smaller == i){
                break;
            }
            else{
                int temp = 0;
                // id
                temp = set_list[root2].knight_heap[i].id;
                set_list[root2].knight_heap[i].id = set_list[root2].knight_heap[smaller].id;
                set_list[root2].knight_heap[smaller].id = temp;
                // health
                temp = set_list[root2].knight_heap[i].health;
                set_list[root2].knight_heap[i].health = set_list[root2].knight_heap[smaller].health;
                set_list[root2].knight_heap[smaller].health = temp;
                // attack
                temp = set_list[root2].knight_heap[i].attack;
                set_list[root2].knight_heap[i].attack = set_list[root2].knight_heap[smaller].attack;
                set_list[root2].knight_heap[smaller].attack = temp;
                // attack count
                temp = set_list[root2].knight_heap[i].attack_count;
                set_list[root2].knight_heap[i].attack_count = set_list[root2].knight_heap[smaller].attack_count;
                set_list[root2].knight_heap[smaller].attack_count = temp;
                i = smaller;
            }
        }
    }

    if (check != 1){  // there still have element in heap of Set2
        // union by size
        if (set_list[root1].size >= set_list[root2].size){ // heap of Set2 merge to Set1
            // check if needed to realloc
            if (set_list[root1].capacity < set_list[root1].size + set_list[root2].size){
                set_list[root1].capacity = 2 * set_list[root1].capacity;
                set_list[root1].knight_heap = realloc(set_list[root1].knight_heap, set_list[root1].capacity  * sizeof(Heap));
            }

            // merge
            set_list[root2].parent = root1;
            set_list[root1].cumulative_attack = set_list[root1].cumulative_attack + set_list[root2].cumulative_attack;

            for (int i = set_list[root1].size; i < set_list[root1].size + set_list[root2].size; i++){
                set_list[root1].knight_heap[i].id = set_list[root2].knight_heap[i - set_list[root1].size].id;
                set_list[root1].knight_heap[i].health = set_list[root2].knight_heap[i - set_list[root1].size].health - set_list[root2].cumulative_been_attacked + set_list[root1].cumulative_been_attacked;
                set_list[root1].knight_heap[i].attack = set_list[root2].knight_heap[i - set_list[root1].size].attack;
                set_list[root1].knight_heap[i].attack_count = set_list[root2].knight_heap[i - set_list[root1].size].attack_count + set_list[root2].attack_count - set_list[root1].attack_count;
                knight_list[set_list[root1].knight_heap[i].id].attack_count = set_list[root1].knight_heap[i].attack_count;

                // build heap
                int index = i;
                while (index > 0){
                    if (set_list[root1].knight_heap[index].health < set_list[root1].knight_heap[(index-1)/2].health){
                        int temp = 0;
                        // id
                        temp = set_list[root1].knight_heap[index].id;
                        set_list[root1].knight_heap[index].id = set_list[root1].knight_heap[(index-1)/2].id;
                        set_list[root1].knight_heap[(index-1)/2].id = temp;
                        // health
                        temp = set_list[root1].knight_heap[index].health;
                        set_list[root1].knight_heap[index].health = set_list[root1].knight_heap[(index-1)/2].health;
                        set_list[root1].knight_heap[(index-1)/2].health = temp;
                        // attack
                        temp = set_list[root1].knight_heap[index].attack;
                        set_list[root1].knight_heap[index].attack = set_list[root1].knight_heap[(index-1)/2].attack;
                        set_list[root1].knight_heap[(index-1)/2].attack = temp;
                        // attack count
                        temp = set_list[root1].knight_heap[index].attack_count;
                        set_list[root1].knight_heap[index].attack_count = set_list[root1].knight_heap[(index-1)/2].attack_count;
                        set_list[root1].knight_heap[(index-1)/2].attack_count = temp;
                        index = (index-1)/2;
                    }
                    else{
                        break;
                    }
                }
            }
            set_list[root1].size = set_list[root1].size + set_list[root2].size;
            free(set_list[root2].knight_heap);  
        }
        else{
            // check if needed to realloc
            if (set_list[root2].capacity < set_list[root1].size + set_list[root2].size){
                set_list[root2].capacity = 2 * set_list[root2].capacity;
                set_list[root2].knight_heap = realloc(set_list[root2].knight_heap, set_list[root2].capacity  * sizeof(Heap));
            }

            // merge
            set_list[root1].parent = root2;
            set_list[root2].cumulative_attack = set_list[root2].cumulative_attack + set_list[root1].cumulative_attack;

            for (int i = set_list[root2].size; i < set_list[root1].size + set_list[root2].size; i++){
                set_list[root2].knight_heap[i].id = set_list[root1].knight_heap[i - set_list[root2].size].id;
                set_list[root2].knight_heap[i].health = set_list[root1].knight_heap[i - set_list[root2].size].health - set_list[root1].cumulative_been_attacked + set_list[root2].cumulative_been_attacked;
                set_list[root2].knight_heap[i].attack = set_list[root1].knight_heap[i - set_list[root2].size].attack;
                set_list[root2].knight_heap[i].attack_count = set_list[root1].knight_heap[i - set_list[root2].size].attack_count + set_list[root1].attack_count - set_list[root2].attack_count;
                knight_list[set_list[root2].knight_heap[i].id].attack_count = set_list[root2].knight_heap[i].attack_count;

                // build heap
                int index = i;
                while (index > 0){
                    if (set_list[root2].knight_heap[index].health < set_list[root2].knight_heap[(index-1)/2].health){
                        int temp = 0;
                        // id
                        temp = set_list[root2].knight_heap[index].id;
                        set_list[root2].knight_heap[index].id = set_list[root2].knight_heap[(index-1)/2].id;
                        set_list[root2].knight_heap[(index-1)/2].id = temp;
                        // health
                        temp = set_list[root2].knight_heap[index].health;
                        set_list[root2].knight_heap[index].health = set_list[root2].knight_heap[(index-1)/2].health;
                        set_list[root2].knight_heap[(index-1)/2].health = temp;
                        // attack
                        temp = set_list[root2].knight_heap[index].attack;
                        set_list[root2].knight_heap[index].attack = set_list[root2].knight_heap[(index-1)/2].attack;
                        set_list[root2].knight_heap[(index-1)/2].attack = temp;
                        // attack count
                        temp = set_list[root2].knight_heap[index].attack_count;
                        set_list[root2].knight_heap[index].attack_count = set_list[root2].knight_heap[(index-1)/2].attack_count;
                        set_list[root2].knight_heap[(index-1)/2].attack_count = temp;
                        index = (index-1)/2;
                    }
                    else{
                        break;
                    }
                }
            }
            set_list[root2].size = set_list[root1].size + set_list[root2].size;
            free(set_list[root1].knight_heap);  
        }
    }
}

int compare(int parent, int left_child, int right_child, Set *set_list, int index){
    if (left_child > set_list[index].size - 1 && right_child > set_list[index].size - 1){
        return parent;
    }

    else if (right_child > set_list[index].size - 1 && left_child <= set_list[index].size - 1){
        if (set_list[index].knight_heap[parent].health <= set_list[index].knight_heap[left_child].health){
            return parent;
        }
        else{
            return left_child;
        }
        
    }
    
    else{
        if (set_list[index].knight_heap[parent].health <= set_list[index].knight_heap[left_child].health && set_list[index].knight_heap[parent].health <= set_list[index].knight_heap[right_child].health){
            return parent;
        }
        else if (set_list[index].knight_heap[left_child].health <= set_list[index].knight_heap[parent].health && set_list[index].knight_heap[left_child].health <= set_list[index].knight_heap[right_child].health){
            return left_child;
        }
        else{
            return right_child;
        }
    }
}