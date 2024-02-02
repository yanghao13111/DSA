#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#define MAX 100000000
#define CHARACTER 26
#define PRIME1 30000001
#define PRIME2 20000003
#define PRIME3 10000019
#define PRIME4 40000061
#define TEST 113

typedef struct hash_table{
    int check;
}hash_table;

void build_hash(hash_table *, char *, int, int);
void print_table(hash_table *);

int main(){
    // first initialize
    int n = 0;
    int m = 0;
    char *spell = (char *)malloc(sizeof(char) * MAX);
    char *pattern = (char *)malloc(sizeof(char) * MAX);
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%s", spell);
    scanf("%s", pattern);

    // create pattern_for_hash for further hash calculation
    int pattern_length = strlen(pattern);
    char *pattern_for_hash = (char *)malloc(sizeof(char) * 2 * strlen(pattern));
    char *pattern_for_hash_num = (char *)malloc(sizeof(char) * 2 * strlen(pattern));
    strcpy(pattern_for_hash, pattern);
    strcat(&pattern_for_hash[pattern_length], pattern);
    // create spell_for_hash_num for further hash calculation
    int spell_length = strlen(spell);
    char *spell_for_hash_num = (char *)malloc(sizeof(char) * strlen(spell));

    // initialize pattern_for_hash_num
    for (int i = 0; i < 2*pattern_length; i++){
        pattern_for_hash_num[i] = pattern_for_hash[i] - 'A';
    }
    // initialize spell_for_hash_num
    for (int i = 0; i < n; i++){
        spell_for_hash_num[i] = spell[i] - 'A';
    }

    // create hash table
    hash_table *table1 = (hash_table *)malloc(sizeof(hash_table) * PRIME1);
    build_hash(table1, pattern_for_hash_num, pattern_length, PRIME1);
    hash_table *table2 = (hash_table *)malloc(sizeof(hash_table) * PRIME2);
    build_hash(table2, pattern_for_hash_num, pattern_length, PRIME2);
    hash_table *table3 = (hash_table *)malloc(sizeof(hash_table) * PRIME3);
    build_hash(table3, pattern_for_hash_num, pattern_length, PRIME3);
    hash_table *table4 = (hash_table *)malloc(sizeof(hash_table) * PRIME4);
    build_hash(table4, pattern_for_hash_num, pattern_length, PRIME4);

    // rabin-karp algorithm
    int count = 0;
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;
    int sum4 = 0;
    int h1 = 1;
    int h2 = 1;
    int h3 = 1;
    int h4 = 1;
    for (int i = 0; i < pattern_length; i++){
        h1 = (CHARACTER*h1)%PRIME1;
    }
    for (int i = 0; i < pattern_length; i++){
        h2= (CHARACTER*h2)%PRIME2;
    }
    for (int i = 0; i < pattern_length; i++){
        h3= (CHARACTER*h3)%PRIME3;
    }
    for (int i = 0; i < pattern_length; i++){
        h4= (CHARACTER*h4)%PRIME4;
    }
    for (int i = 0; i < spell_length - pattern_length + 1; i++){
        if (i == 0){
            for(int j = 0; j < pattern_length; j++){
                sum1 = (CHARACTER*(sum1 + spell_for_hash_num[j]))%PRIME1;
                sum2 = (CHARACTER*(sum2 + spell_for_hash_num[j]))%PRIME2;
                sum3 = (CHARACTER*(sum3 + spell_for_hash_num[j]))%PRIME3;
                sum4 = (CHARACTER*(sum4 + spell_for_hash_num[j]))%PRIME4;
            }
            if (table1[sum1].check == 1 && table2[sum2].check == 1 && table3[sum3].check == 1 && table4[sum4].check == 1){
                count += 1;
            }
            
        }
        else{
            sum1 = (CHARACTER*(sum1 - ((spell_for_hash_num[i-1])*h1)%PRIME1 + PRIME1 + spell_for_hash_num[i + pattern_length - 1]))%PRIME1;
            sum2 = (CHARACTER*(sum2 - ((spell_for_hash_num[i-1])*h2)%PRIME2 + PRIME2 + spell_for_hash_num[i + pattern_length - 1]))%PRIME2;
            sum3 = (CHARACTER*(sum3 - ((spell_for_hash_num[i-1])*h3)%PRIME3 + PRIME3 + spell_for_hash_num[i + pattern_length - 1]))%PRIME3;
            sum4 = (CHARACTER*(sum4 - ((spell_for_hash_num[i-1])*h4)%PRIME4 + PRIME4 + spell_for_hash_num[i + pattern_length - 1]))%PRIME4;
            if (table1[sum1].check == 1 && table2[sum2].check == 1 && table3[sum3].check == 1 && table4[sum4].check == 1){
                count += 1;
            }
        }
    }
    printf("%d\n", count);

    return 0;
}

// function
void build_hash(hash_table* table, char *pattern_for_hash_num, int pattern_length, int prime){
    int h = 1;
    for (int i = 0; i < pattern_length; i++){
        h = (CHARACTER*h)%prime;
    }
    // strncpy(hash_pattern, &pattern_for_hash[1], pattern_length);
    int sum = 0;
    for(int i = 0; i < pattern_length; i++){
        if (i == 0){
            for(int j = 0; j < pattern_length; j++){
                sum = (CHARACTER*(sum + pattern_for_hash_num[j]))%prime;
            }
            if (table[sum].check == 0){
                table[sum].check = 1;
            }
        }
        else{
            sum = (CHARACTER*(sum - ((pattern_for_hash_num[i-1])*h)%prime + prime + pattern_for_hash_num[i + pattern_length - 1]))%prime;
            if (table[sum].check == 0){
                table[sum].check = 1;
            }
        }
    }
}

// void print_table(hash_table *table){
//     printf("---Start---\n");
//     for(int i=0;i<TEST;i++){
//         //nothing in the hash table
//         if(table[i].check==0) printf("\t%d\t---\n",i);
//         //something in the hash table
//         else printf("\t%d\t%d\n",i,table[i].collision);
//     }
//     printf("---End-----\n");
// }