#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define STACK_SIZE 5


struct stack_t {
	int top;
	int stack_arr[STACK_SIZE];
};


void print_stack(struct stack_t *stack)
{
	int i;

	printf("Stack: [");
	for(i=0; i<STACK_SIZE; i++) {
		printf("%2d ", stack->stack_arr[i]);
	}
	printf("] top at: %d\n", stack->top);


}

int push(struct stack_t *stack, int val)
{
	if(stack->top > (STACK_SIZE - 1)) {
		return -1;
	}

	stack->stack_arr[stack->top++] = val;
	return 0;
}

int pop(struct stack_t *stack)
{

	if(stack->top <= 0)
		return -1;

	return stack->stack_arr[--(stack->top)];
}

int main(int argc, char **argv)
{
	int i, flag, num;
	struct stack_t stack;

	/* Initial the stack */
	stack.top = 0;
	memset(stack.stack_arr, -1, sizeof(stack.stack_arr));

	srand(time(NULL));


	for(i=0; i<10; i++) {
		flag = rand() % 2;
		num = rand() % 100;
		switch(flag) {
		case 0:
			printf("Push: %d\n", num);
			if(push(&stack, num) == -1)
				printf("Stack is full\n");

			break;
		case 1:
			printf("Pop: ");
			num = pop(&stack);
			if(num == -1)
				printf("Stack is empty\n");
			else
				printf(" %d\n", num);

			break;
		}
		print_stack(&stack);
	}
	return 0;
}

