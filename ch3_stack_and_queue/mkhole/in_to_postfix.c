#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 32

struct stack_t {
	int top;
	char stack_arr[STACK_SIZE];
};

int push(struct stack_t *stack, int val)
{
	if(stack->top > (STACK_SIZE - 1)) {
		return -1;
	}
	stack->stack_arr[stack->top++] = val;
	return 0;
}

char pop(struct stack_t *stack)
{
	if(stack->top <= 0)
		return -1;

	return stack->stack_arr[--(stack->top)];
}

int priority(char op) {
	int pri;

	switch(op) {
	case '+':
	case '-':
		pri = 1;
		break;
	case '*':
	case '/':
		pri = 2;
		break;
	default:
		pri = -1;
		break;
	}

	return pri;
}

void in_to_postfix(char *infix) {
	int i;
	struct stack_t stack;

	if(!infix || (strlen(infix) == 0)) {
		printf("infix string is empty\n");
		return;
	}

	stack.top = 0;
	memset(stack.stack_arr, '\0', sizeof(stack.stack_arr));

	for(i=0; i<strlen(infix); i++) {
		switch(infix[i]) {
		case '(':
			push(&stack, infix[i]);
			break;
		case ')':
			if(stack.top > 0) {
				while(stack.stack_arr[stack.top - 1] != '(') {
					printf("%c", pop(&stack));
				}
			}
			pop(&stack);
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			if(stack.top > 0) {
				while(priority(stack.stack_arr[stack.top - 1]) >= priority(infix[i])) {
					printf("%c", pop(&stack));
				}
			}
			push(&stack, infix[i]);
			break;
		default:
			printf("%c", infix[i]);
			break;
		}
	}

	while(stack.top > 0) {
		printf("%c", pop(&stack));
	}

	return;
}

int main(int argc, char **argv)
{
	int i, size;
	char infix[2][STACK_SIZE] = {
		"(a+b)*c/(d+e)-8",
		"a+b/c+d/e+f"
	};

	size = sizeof(infix)/sizeof(infix[0]);
	for(i=0; i<size; i++) {
		printf("infix: %s", infix[i]);
		printf(", postfix: ");
		in_to_postfix(infix[i]);
		printf("\n");
	}

	return 0;
}

