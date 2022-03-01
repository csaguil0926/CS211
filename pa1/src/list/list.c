#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct Node* front = NULL;
int listsize = 0;

int isEmpty(){
    return front == NULL;
}

int inList(int data){
    struct Node* ptr = front;
    
    if(isEmpty()){
        
        return 0;
    } else{
        while(ptr!=NULL){
            if (ptr->data == data){
                return 1;
            }
            ptr = ptr->next;
        }
        
        return 0;
    }
}

void insert(int data){

    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;

    if(!inList(data)){
        if(isEmpty() || (temp->data < front->data)){
            temp->next=front;
            front=temp;
        } else{
            struct Node *ptr = front;

            while(ptr->next!=NULL && ptr->next->data < temp->data){
                ptr=ptr->next;
            }
            
            temp->next = ptr->next;
            ptr->next = temp;
            
        }
        listsize++;
    }
}

void delete(int data){
    struct Node *ptr = front;
    struct Node *ptrprev = NULL;

    while(ptr!=NULL&&ptr->data!=data){
        ptrprev = ptr;
        ptr = ptr->next;
    }

    if(ptr!=NULL){
        if (ptr==front){
            front = ptr->next;
        }else{
            ptrprev->next = ptr->next;     
        }
        listsize--;
    }

    free(ptr);

}

void printList(){
    struct Node *ptr = front;
    printf("%d :", listsize);
    
    while(ptr!=NULL){
        printf(" ");
        printf("%d", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
    

}

int main(int argc, char**argv){

    char c;
    int num;

    while(scanf(" %c %d", &c, &num)!=EOF){

        if (c == 'i'){
            insert(num);
            printList();
        }else{
            delete(num);
            printList();
        }
    }

    return 0;
}
