#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc / free

typedef struct { 
    int indices;
    int attack;
} node;

int main(){
    int player = 0;            
    int capacity = 0;
    int size = 0;
    int count = 0;
    int l = 0;
    int m = 0;
    int r = 0;
    int check = 0;
    int preCheck = 0;
    scanf("%d %d", &player, &capacity);

    node *power = (node*)malloc(capacity*sizeof(node));


    int input = 0;
    for (int round = 0; round < player; round++){
        scanf("%d", &input);
        power[size].indices = round+1;
        power[size].attack = input;

        printf("Round %d: ", round+1);

        // skip first round
        if (round == 0){
            size++;
            printf("\n");
            continue;
        }

        // the remaining rounds using binary method
        l = 0;
        r = size;
        while (l <= r){
            m = (l+r)/2;
            if (power[m].attack >= power[size].attack){
                check = 0;
                l = m+1;
            }
            else if (power[m].attack < power[size].attack){
                check = 1;
                r = m-1;
                preCheck = m;

            }
        }
        if (check == 0){
            if (preCheck != 0){
                for (int i = size-1; i >= preCheck; i--){
                printf("%d ", power[i].indices);
                }
                power[preCheck].indices = power[size].indices;
                power[preCheck].attack = power[size].attack;
                size = preCheck+1;
            }
            else{
                size++;
            }
        }
        
        if (check == 1){
            for (int i = size-1; i >= m; i--){
                printf("%d ", power[i].indices);
            }
            power[m].indices = power[size].indices;
            power[m].attack = power[size].attack;
            size = m+1;
        }
        preCheck = 0;
        
        // revolution
        if (size > capacity){
            printf("%d ", power[0].indices);
            // replace iteratively move the index to the left
            memmove(&power[0], &power[1], capacity * sizeof(node));
            size--;
        }
        printf("\n");
    }

    printf("Final: ");
    for (int i = size-1; i >= 0; i--){
        printf("%d ", power[i].indices);
    }
    
    free(power);
    return 0;
}