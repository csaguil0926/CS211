#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* newNode(int data){
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct Node* root = NULL;

void insert(struct Node** root, struct Node* temp){

    if ((*root) ==NULL){
        *root = temp;
        printf("inserted\n");
        return;
    }
    
    if ((*root)->data == temp->data){
        printf("not inserted\n");
        return;
    }else if ((*root)->data > temp->data){
        insert(&(*root)->left, temp);
    }else if ((*root)->data < temp->data){
        insert(&(*root)->right, temp);
    }

    return;
}

void search1(struct Node** root, int data){

    if ((*root)==NULL){
        printf("absent\n");
        return;
    }

    if((*root)->data == data){
        printf("present\n");
        return;
    }else if ((*root)->data > data){
        search1(&(*root)->left, data);
    }else if ((*root)->data < data){
        search1(&(*root)->right, data);
    }

    return;
}

void print(struct Node* root){
    if (root ==NULL){
        return;
    }else{
        printf("(");
        print(root->left);
        printf("%d", root->data);
        print(root->right);
        printf(")");
        return;
    }
   return;
}

void delete(struct Node** root,int data){

    if((*root) == NULL){
        printf("absent\n");
        return;
    }

    if((*root)->data>data){
        delete(&(*root)->left, data);
    }else if ((*root)->data<data){
        delete(&(*root)->right, data);
    }

    if ((*root)->data == data){
        if ((*root)->left == NULL){
            (*root)=(*root)->right;
            printf("deleted\n");
            return;
        } else if ((*root)->right == NULL){
            (*root)=(*root)->left;
            printf("deleted\n");
            return;
        } else {
            struct Node* ptr = (*root)->right;
            struct Node* min = ptr;
            while(min->left != NULL){
                min = ptr->left;
                ptr = ptr->left;
            }
            (*root)->data=min->data;
            delete(&(*root)->right, min->data);

        }
        
    }
}

int main(int argc, char**argv){
    
    char c;
    int num;

    while(scanf(" %c", &c)!=EOF){

        if (c == 'i'){
            scanf(" %d", &num);
            struct Node* node = newNode(num);
            insert(&root, node);
        }else if (c == 's'){
            scanf(" %d", &num);
            search1(&root, num);
        }else if (c == 'p'){
            print(root);
            printf("\n");
        }else{
            scanf(" %d", &num);
            delete(&root,num);
        }
    }

    return 0;
}