#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Stack {
	int top;
	int size;
	char* array;
};

struct Stack* newStack(int size){
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	stack->size = size;
	stack->top = -1;
	stack->array= (char*)malloc(stack->size*sizeof(char));
	return stack;
}

int isFull(struct Stack* stack){
	return stack->top == stack->size -1;
}

int isEmpty(struct Stack* stack){
	return stack->top == -1;
}

void push(struct Stack* stack, char item){
	if(isFull(stack)){
		return;
	}else{
		stack->array[++stack->top] = item;
	}
}

int pop(struct Stack* stack){
	if (isEmpty(stack)){
		return 0;
	}else{
		return stack->array[stack->top--];
	}
}

void printStack (struct Stack* stack){

	while(!isEmpty(stack)) {
		char c = pop(stack);
		printf("%c",c);
	}
	return;
}

int isMatchingPair(char char1, char char2);


int main(int argc, char** argv)
{
	char *str = argv[1];

	int len = strlen(str);

	struct Stack* stack = newStack(len);

	for(int i = 0; i < len; i++){
		if (str[i] == '{' || str[i] == '[' || str[i]=='(' ){
			push(stack, str[i]);

		} else if (str[i] == '}' || str[i] == ']' || str[i]==')'){
			if(isEmpty(stack)){
				printf("%d: %c\n", i, str[i]);
				free(stack->array);
				free(stack);
				return EXIT_FAILURE;
			} else if (!(isMatchingPair(pop(stack), str[i]))) {
				printf("%d: %c\n", i, str[i]);
				free(stack->array);
				free(stack);
				return EXIT_FAILURE;
			}
		}
	}

	
	if (!isEmpty(stack)){

		printf("open: ");
		
		while(!isEmpty(stack)){
			char c = pop(stack);
			if (c == '('){
				printf(")");
			} else if (c =='['){
				printf("]");
			} else if (c == '{'){
				printf("}");
			}
		}
		printf("\n");
		
		free(stack->array);
		free(stack);
		return EXIT_FAILURE;
	}

	free(stack->array);
	free(stack);

	return EXIT_SUCCESS;
	
}

int isMatchingPair(char char1, char char2){
	if ( char1 =='(' && char2 ==')'){
		return 1;
	} else if ( char1 =='{' && char2 =='}'){
		return 1;
	} else if ( char1 =='[' && char2 ==']'){
		return 1;
	} else {
		return 0;
	}
}