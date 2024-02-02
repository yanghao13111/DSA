#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc / free
#define MAX_SIZE 500

int *toInt(char[]);
int checkSize(char[], char[]);
int checkIntSize(int *, int *);
int calLength(int *);
void divide(int *);
void multiply(int *, int); 
void subtraction(int *, int *);
void gcd(int *, int *);
int checkEnd(int *);
void swap(int *, int *, int);

int main(){
    char a[MAX_SIZE] = {0};
    char b[MAX_SIZE] = {0};
    char smaller[MAX_SIZE] = {0};
    char bigger[MAX_SIZE] = {0};

    scanf("%s", a);
    scanf("%s", b);

    int check = checkSize(a, b);
    if (check){
        strcpy(smaller, a);
        strcpy(bigger, b);
    }
    else{
        strcpy(smaller, b);
        strcpy(bigger, a);
    }

    int *smallerInt = toInt(smaller);
    int *biggerInt = toInt(bigger);

    gcd(smallerInt, biggerInt);

    return 0;
}

// function
int checkSize(char a[], char b[]){
    if (strlen(a) > strlen(b)){
        return 0;
    }
    else if (strlen(a) == strlen(b)){
        for (int i = 0; i < strlen(a); i++){
            if (a[i] > b[i]){
                return 0;
            }
            else if (a[i] < b[i]){
                return 1;
            }
        }
        return 0;
    }
    return 1;
}

int *toInt(char word[]){
    int length = strlen(word);
    int *num = (int*)malloc(MAX_SIZE * sizeof(int));

    for (int i = 0, j = length-1; j >= 0; i++, j--){
        num[i] = word[j]-'0';
    }
    for ( int i = length; i < MAX_SIZE; i++){
        num[i] = -1;
    }
    
    return num;
}

int calLength(int *a){
    int count = 0;
    int check = 0;
    for (int i = MAX_SIZE-1; i >= 0 ; i--){
        if (a[i] > 0){
            check++;
        }
        if (a[i]!=-1 && check > 0){
            count++;
        }
    }
    return count;
}

void swap(int *a, int *b, int length){
    for(int i = 0; i< length; i++){
        int temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

void divide(int *a){
    if (a[calLength(a)-1] == 1){
        a[calLength(a)-2] += 10;
        a[calLength(a)-1] = -1;
    }
    int temp = 0;
    int carry = 0;
    for (int i = calLength(a)-1; i >= 0; i--){
        temp = a[i];
        a[i] = (temp + carry*10)/2;
        carry = (temp + carry*10) % 2;
    }
}

void multiply(int *a, int ans){
    int temp = 0;
    int carry = 0;
    for (int i = 0; (a[i] + carry) != -1; i++){
        if (a[i] == -1){
            a[i] = carry % 10;
            carry /= 10;
        }
        else{
            temp =a[i];
            a[i] = (temp * ans + carry) % 10;
            carry = (temp * ans + carry) / 10;
        }
    }
}

void subtraction(int *smaller, int *bigger){
    for (int i = 0; i < calLength(smaller); i++){
        if (bigger[i] > smaller[i]){
            bigger[i] -= smaller[i];
        }
        else if (bigger[i] == smaller[i]){
            if (bigger[i+1]==-1){
                bigger[i] = -1;
            }
            else{
                bigger[i] -= smaller[i];
            }
        }
        
        else{
            bigger[i] =  bigger[i]+10 - smaller[i];
            int count = 1;
            while (bigger[i+count] == 0){
                bigger[i+count] = 9;
                count++;
            }
            bigger[i+count] -= 1;
            if (bigger[i+count]==0 && bigger[i+count+1]==-1){
                bigger[i+count] = -1;
            }
        } 
    }
}

void gcd(int* smaller, int* bigger){
    int ans = 1;
    while (checkEnd(smaller) && checkEnd(bigger) ){
        if (smaller[0] % 2 == 0 && bigger[0] % 2 == 0){
            ans *= 2;
            divide(smaller);
            divide(bigger);
        }
        else if (smaller[0] % 2 == 0){
            divide(smaller);
        }
        else if (bigger[0] % 2 == 0){
            divide(bigger);
        }
        
        if (checkIntSize(bigger, smaller)){
            swap(smaller, bigger, calLength(smaller));
        }
        
        subtraction(smaller, bigger);
    }

    multiply(smaller, ans);

    for (int i = calLength(smaller)-1; i >= 0; i--){
        printf("%d", smaller[i]);
    }
    
}

int checkEnd(int *a){
    int temp = 0;
    for (int i = 0; i < calLength(a); i++){
        if (a[i]!=0){
            temp = 1;
        }
    }
    return temp;
}

int checkIntSize(int *a, int *b){
    if (calLength(a) > calLength(b)){
        return 0;
    }
    else if (calLength(a) == calLength(b)){
        for (int i = calLength(a) - 1; i >= 0 ; i--){
            if (a[i] > b[i]){
                return 0;
            }
            else if (a[i] < b[i]){
                return 1;
            }
        }
        return 0;
    }
    return 1;
}