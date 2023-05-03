#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

// the parent of each company
typedef struct node{ 
    int parent;
} node;

typedef struct discount_node{
    long long cost; // the cost of the discount
    int time; // the time span of the discount
    int date; // the date when discount is available
} discount_node;

typedef struct tree_node {
    int data;
    int tail;
    long long sum;
    int count;
    struct tree_node *left_child;
    struct tree_node *right_sibling;
    struct discount_node *discount;
} tree_node;

void creat_discount (tree_node* root, long long d_cost, int, int);
int compare(int, int, int, tree_node* root);
void calculate(tree_node* root);
long long cal_cost (tree_node* node);
int cal_count (tree_node* node);

int main(){
    int company = 0;
    int day = 0;
    long long money = 0;
    int input = 0;
    int check = 0;
    scanf("%d %d %lld", &company, &day, &money);

    // store the parent of each company
    node *company_parent_list = (node *)malloc(sizeof(node) * (company-1));
    for (int i = 0; i < company-1; i++){
        scanf("%d", &input);
        company_parent_list[i].parent = input;
    }


    //--------------------------------------construct the tree----------------------------------------

    // construct the tree node
    tree_node *root = (tree_node *)malloc(sizeof(tree_node) * company);
    for (int i = 0; i < company; i++){
        root[i].data = i+1;
        root[i].tail = 0;
        root[i].sum = 0;
        root[i].count = 0;
        root[i].left_child = NULL;
        root[i].right_sibling = NULL;
    }

    // construct the relationship
    tree_node *current = root;
    int index = 0;
    for (int i = 0; i < company-1; i++){
        index = company_parent_list[i].parent - 1;
        if (root[index].left_child == NULL){
            root[index].left_child = &root[i+1];
        }
        else{
            current = root[index].left_child;
            while (current->right_sibling != NULL){
                current = current->right_sibling;
            }
            current->right_sibling = &root[i+1];
        }
    }

    // add discount of each company
    long long d_cost = 0;
    int d_time = 0;
    for (int i = 0; i < day; i++){
        for (int j = 0; j < company; j++){
            scanf("%lld %d", &d_cost, &d_time);
            if (i == 0){
                root[j].discount = (discount_node *)malloc(sizeof(discount_node)*(day+10));
                root[j].discount[i].cost = d_cost;
                root[j].discount[i].time = d_time;
                root[j].discount[i].date = i+1;
                root[j].tail = i;
            }
            else{
                creat_discount(&root[j], d_cost, d_time, i+1);
            }
        }


        // calculate the sum of the subtree and the count
        calculate(root);
        int count_result = 0;
        for (int i = 0; i < company; i++){
            if (root[i].sum <= money && root[i].count > count_result){
                count_result = root[i].count;
            } 
        }

        printf("%d\n", count_result);
    }

    return 0;
}

void calculate(tree_node* root){
    long long result = 0;
    int count = 0;

    if (root->left_child != NULL){
        result = root->discount->cost + cal_cost(root -> left_child);
        count = 1 + cal_count(root -> left_child);
    }
    else{
        result = root->discount->cost;
        count = 1;
    }

    root->sum = result;
    root->count = count;
}

long long cal_cost (tree_node* node){
    if (node == NULL){
        return 0;
    }
    long long temp_cost = 0;

    if (node->left_child != NULL){
        temp_cost = node->discount->cost + cal_cost(node -> left_child);
    }
    else{
        temp_cost = node->discount->cost;
    }
    
    node->sum = temp_cost;

    return temp_cost + cal_cost(node->right_sibling);
}

int cal_count (tree_node* node){
    if (node == NULL){
        return 0;
    }
    int temp_count = 0;

    if (node->left_child != NULL){
        temp_count = 1 + cal_count(node -> left_child);
    }
    else{
        temp_count = 1;
    }

    node->count = temp_count;

    return temp_count + cal_count(node->right_sibling);
}

void creat_discount (tree_node* node, long long d_cost, int d_time, int now){
    // add new discount
    node->discount[node->tail+1].cost = d_cost;
    node->discount[node->tail+1].time = d_time;
    node->discount[node->tail+1].date = now;
    node->tail++;

    int i = node->tail;
    while (i > 0){
        if (node->discount[i].cost < node->discount[(i-1)/2].cost){
            long long temp_cost = 0;
            int temp = 0;
            temp_cost = node->discount[i].cost;
            node->discount[i].cost = node->discount[(i-1)/2].cost;
            node->discount[(i-1)/2].cost = temp_cost;
            temp = node->discount[i].time;
            node->discount[i].time = node->discount[(i-1)/2].time;
            node->discount[(i-1)/2].time = temp;
            temp = node->discount[i].date;
            node->discount[i].date = node->discount[(i-1)/2].date;
            node->discount[(i-1)/2].date = temp;
            i = (i-1)/2;
        }
        else{
            break;
        }
    }

    // ------------------------------------------to be continued-------------------------------------


    // remove smallest when discount date is expired
    while (now - node->discount->date > node->discount->time){
        node->discount[0].cost = node->discount[node->tail].cost;
        node->discount[0].time = node->discount[node->tail].time;
        node->discount[0].date = node->discount[node->tail].date;
        node->tail--;


        //  ------------------------------------------to be continued-------------------------------------c



        int i = 0;
        int smaller = 0;
        while (i <= node->tail){
            smaller = compare(i , (2*i)+1, (2*i)+2, node);
            if (smaller == i){
                break;
            }
            else{
                long long temp_cost = 0;
                int temp = 0;
                temp_cost = node->discount[i].cost;
                node->discount[i].cost = node->discount[smaller].cost;
                node->discount[smaller].cost = temp_cost;
                temp = node->discount[i].time;
                node->discount[i].time = node->discount[smaller].time;
                node->discount[smaller].time = temp;
                temp = node->discount[i].date;
                node->discount[i].date = node->discount[smaller].date;
                node->discount[smaller].date = temp;
                i = smaller;
            }
        }
    }
}

int compare(int parent , int left_child, int right_child, tree_node* node){
    if (left_child > node->tail && right_child > node->tail){
        return parent;
    }

    else if (right_child > node->tail && left_child <= node->tail){
        if (node->discount[parent].cost <= node->discount[left_child].cost){
            return parent;
        }
        else{
            return left_child;
        }
    }

    else if (right_child <= node->tail && left_child < node->tail){
        if (node->discount[left_child].cost <= node->discount[right_child].cost){
            if (node->discount[parent].cost <= node->discount[left_child].cost){
                return parent;
            }
            else{
                return left_child;
            }
        }
        else{
            if (node->discount[parent].cost <= node->discount[right_child].cost){
                return parent;
            }
            else{
                return right_child;
            }
        }
    }
    return 0;
}