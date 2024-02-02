#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <math.h>

#define MAX 1000010
#define CHARACTER 26
#define PRIME1 20000003
#define PRIME2 10000019

typedef struct hash_table{
    int index;
    int check;
} hash_table;

typedef struct result_table{
    long long size;
    long long min1;
    long long min2;
} result_table;

void build_hash(hash_table *, hash_table *, result_table *, char *, int, int, int, int *);
int insert_hash(hash_table *, hash_table *, result_table *, char *, int, int, int, int *);
int delete_hash(hash_table *, hash_table *, result_table *, char *, int, int, int);

int main(){
    int number = 0;  // original set
    int operation = 0;
    int type = 0;
    int length = 0;  // length of stings
    long long pair = 0;    // number of pairs
    int count = 0;   // number of possible sets
    char *input = (char *)malloc(sizeof(char) * MAX);

    hash_table *table1 = (hash_table *)malloc(sizeof(hash_table) * PRIME1);
    hash_table *table2 = (hash_table *)malloc(sizeof(hash_table) * PRIME2);
    result_table *result = (result_table *)malloc(sizeof(result_table) * MAX);

    scanf("%d %d", &number, &operation);

    // first round
    for (int i = 0; i < number; i++){
        scanf("%s", input);
        if (i == 0){
            length = strlen(input);
            for (int j = 0; j < length; j++){
                input[j] = input[j] - 'a';
            }

            build_hash(table1, table2, result, input, length, PRIME1, PRIME2, &count); 
        }
        else{
            // change the input to number
            for (int j = 0; j < length; j++){
                input[j] = input[j] - 'a';
            }

            build_hash(table1, table2, result, input, length, PRIME1, PRIME2, &count); 
        }
    }

    // calculate pair and print
    for (int i = 0; i < count; i++){
        pair += (result[i].size * (result[i].size - 1))/2;
    }
    printf("%lld\n", pair);

    // second round
    int index = 0;
    for (int i = 0; i < operation; i++){
        scanf("%d", &type);
        scanf("%s", input);
        for (int j = 0; j < length; j++){
            input[j] = input[j] - 'a';
        }

        if (type == 1){
            index = insert_hash(table1, table2, result, input, length, PRIME1, PRIME2, &count);
            if (index != -1){
                pair -= (result[index].size * (result[index].size - 1))/2;
                result[index].size += 1;
                pair += (result[index].size * (result[index].size - 1))/2;
            }
        }
        else{
            index = delete_hash(table1, table2, result, input, length, PRIME1, PRIME2);
            if (index != -1){
                pair -= (result[index].size * (result[index].size - 1))/2;
                result[index].size -= 1;
                pair += (result[index].size * (result[index].size - 1))/2;
            }
        }
        printf("%lld\n", pair);
    }



    return 0;
}

//function
void build_hash(hash_table* table1, hash_table* table2, result_table* result, char *input, int length, int prime1, int prime2, int *count){
    long long h1 = 1;
    for (int i = 0; i < length-1; i++){
        h1 = (CHARACTER*h1)%prime1;
    }

    long long h2 = 1;
    for (int i = 0; i < length-1; i++){
        h2 = (CHARACTER*h2)%prime2;
    }


    int test = 0;
    long long sum1 = 0;
    long long sum2 = 0;
    long long min_sum1 = 0;
    long long min_sum2 = 0;



    for(int i = 0; i < length; i++){
        if (i == 0){
            // first rabin-karp algorithm
            for(int j = 0; j < length; j++){
                sum1 = ((CHARACTER*sum1)%prime1 + input[j])%prime1;
            }
            for(int j = 0; j < length; j++){
                sum2 = ((CHARACTER*sum2)%prime2 + input[j])%prime2;
            }

            min_sum1 = sum1;
            min_sum2 = sum2;
        }

        else{
            sum1 = (CHARACTER*(sum1 - ((input[i-1])*h1)%prime1 + prime1)%prime1 + input[i-1])%prime1;
            sum2 = (CHARACTER*(sum2 - ((input[i-1])*h2)%prime2 + prime2)%prime2 + input[i-1])%prime2;
            if (sum1 < min_sum1){
                min_sum1 = sum1;
            }
            if (sum2 < min_sum2){
                min_sum2 = sum2;
            }
        }
    }

    if (table1[min_sum1].check == 1 && table2[min_sum2].check == 1){
        // only one set
        if (table1[min_sum1].index == table2[min_sum2].index){
            result[table1[min_sum1].index].size += 1;
        }
        // two different set
        else{
            if (result[table1[min_sum1].index].min1 == min_sum1 && result[table1[min_sum1].index].min2 == min_sum2){
                result[table1[min_sum1].index].size += 1;
            }
            else if (result[table2[min_sum2].index].min1 == min_sum1 && result[table2[min_sum2].index].min2 == min_sum2){
                result[table2[min_sum2].index].size += 1;
            }   
        }
    }
    else if (table1[min_sum1].check == 1 && table2[min_sum2].check == 0){
        table2[min_sum2].check = 1;
        table2[min_sum2].index = *count;
        result[*count].size = 1;
        result[*count].min1 = min_sum1;
        result[*count].min2 = min_sum2;
        *count += 1;
    }
    else if (table1[min_sum1].check == 0 && table2[min_sum2].check == 1){
        table1[min_sum1].check = 1;
        table1[min_sum1].index = *count;
        result[*count].size = 1;
        result[*count].min1 = min_sum1;
        result[*count].min2 = min_sum2;
        *count += 1; 
    }

    else {
        table1[min_sum1].check = 1;
        table2[min_sum2].check = 1;
        table1[min_sum1].index = *count;
        table2[min_sum2].index = *count;
        result[*count].size = 1;
        result[*count].min1 = min_sum1;
        result[*count].min2 = min_sum2;
        *count += 1; 
    }
}

int insert_hash(hash_table* table1, hash_table* table2, result_table* result, char *input, int length, int prime1, int prime2, int *count){
    long long h1 = 1;
    for (int i = 0; i < length-1; i++){
        h1 = (CHARACTER*h1)%prime1;
    }

    long long h2 = 1;
    for (int i = 0; i < length-1; i++){
        h2 = (CHARACTER*h2)%prime2;
    }

    long long sum1 = 0;
    long long sum2 = 0;
    long long min_sum1 = 0;
    long long min_sum2 = 0;

    for(int i = 0; i < length; i++){
        if (i == 0){
            for(int j = 0; j < length; j++){
                sum1 = ((CHARACTER*sum1)%prime1 + input[j])%prime1;
            }
            for(int j = 0; j < length; j++){
                sum2 = ((CHARACTER*sum2)%prime2 + input[j])%prime2;
            }

            min_sum1 = sum1;
            min_sum2 = sum2;
        }

        else{
            sum1 = (CHARACTER*(sum1 - ((input[i-1])*h1)%prime1 + prime1)%prime1 + input[i-1])%prime1;
            sum2 = (CHARACTER*(sum2 - ((input[i-1])*h2)%prime2 + prime2)%prime2 + input[i-1])%prime2;
            if (sum1 < min_sum1){
                min_sum1 = sum1;
            }
            if (sum2 < min_sum2){
                min_sum2 = sum2;
            }
        }
    }

    if (table1[min_sum1].check == 1 && table2[min_sum2].check == 1){
        // only one set
        if (table1[min_sum1].index == table2[min_sum2].index){
            return table1[min_sum1].index;
        }
        // two different set
        else{
            if (result[table1[min_sum1].index].min1 == min_sum1 && result[table1[min_sum1].index].min2 == min_sum2){
                return table1[min_sum1].index;
            }
            else if (result[table2[min_sum2].index].min1 == min_sum1 && result[table2[min_sum2].index].min2 == min_sum2){
                return table2[min_sum2].index;
            }   
        }
    }
    else if (table1[min_sum1].check == 1 && table2[min_sum2].check == 0){
        table2[min_sum2].check = 1;
        table2[min_sum2].index = *count;
        result[*count].size = 1;
        result[*count].min1 = min_sum1;
        result[*count].min2 = min_sum2;
        *count += 1;
    }
    else if (table1[min_sum1].check == 0 && table2[min_sum2].check == 1){
        table1[min_sum1].check = 1;
        table1[min_sum1].index = *count;
        result[*count].size = 1;
        result[*count].min1 = min_sum1;
        result[*count].min2 = min_sum2;
        *count += 1; 
    }

    else {
        table1[min_sum1].check = 1;
        table2[min_sum2].check = 1;
        table1[min_sum1].index = *count;
        table2[min_sum2].index = *count;
        result[*count].size = 1;
        result[*count].min1 = min_sum1;
        result[*count].min2 = min_sum2;
        *count += 1; 
    }

    return -1;
}

int delete_hash(hash_table* table1, hash_table* table2, result_table* result, char *input, int length, int prime1, int prime2){
    long long h1 = 1;
    for (int i = 0; i < length-1; i++){
        h1 = (CHARACTER*h1)%prime1;
    }
    long long h2 = 1;
    for (int i = 0; i < length-1; i++){
        h2 = (CHARACTER*h2)%prime2;
    }

    long long sum1 = 0;
    long long sum2 = 0;
    long long min_sum1 = 0;
    long long min_sum2 = 0;

    for(int i = 0; i < length; i++){
        if (i == 0){
            for(int j = 0; j < length; j++){
                sum1 = ((CHARACTER*sum1)%prime1 + input[j])%prime1;
                sum2 = ((CHARACTER*sum2)%prime2 + input[j])%prime2;
            }

            min_sum1 = sum1;
            min_sum2 = sum2;
        }
        else{
            sum1 = (CHARACTER*(sum1 - ((input[i-1])*h1)%prime1 + prime1)%prime1 + input[i-1])%prime1;
            sum2 = (CHARACTER*(sum2 - ((input[i-1])*h2)%prime2 + prime2)%prime2 + input[i-1])%prime2;
            if (sum1 < min_sum1){
                min_sum1 = sum1;
            }
            if (sum2 < min_sum2){
                min_sum2 = sum2;
            }
        }
    }

    if (table1[min_sum1].index == table2[min_sum2].index){
        return table1[min_sum1].index;
    }
    // two different set
    else{
        if (result[table1[min_sum1].index].min1 == min_sum1 && result[table1[min_sum1].index].min2 == min_sum2){
            return table1[min_sum1].index;
        }
        else if (result[table2[min_sum2].index].min1 == min_sum1 && result[table2[min_sum2].index].min2 == min_sum2){
            return table2[min_sum2].index;
        }   
    }

    return -1;
}