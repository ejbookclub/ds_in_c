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
	if (stack->top > (STACK_SIZE - 1)) {
		return -1;
	}
	stack->stack_arr[stack->top++] = val;
	return 0;
}

char pop(struct stack_t *stack)
{
	if (stack->top <= 0) {
		return -1;
	}
	return stack->stack_arr[--(stack->top)];
}

int priority(char op)
{
	int pri;

	switch (op) {
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

void in_to_postfix(char *infix, char *postfix)
{
	int i, j;
	struct stack_t stack;

	if (!infix || (strlen(infix) == 0)) {
		printf("infix string is empty\n");
		return;
	}

	if (!postfix) {
		printf("postfix is null\n");
		return;
	}

	stack.top = 0;
	memset(stack.stack_arr, '\0', sizeof(stack.stack_arr));

	for (i = 0, j = 0; i < strlen(infix); i++) {
		switch (infix[i]) {
		case '(':
			(void)push(&stack, infix[i]);
			break;
		case ')':
			if (stack.top > 0) {
				while (stack.stack_arr[stack.top - 1] != '(') {
					postfix[j++] = pop(&stack);
				}
			}
			(void)pop(&stack);
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			if (stack.top > 0) {
				while (priority(stack.stack_arr[stack.top - 1]) >= priority(infix[i])) {
					postfix[j++] = pop(&stack);
				}
			}
			(void)push(&stack, infix[i]);
			break;
		default:
			postfix[j++] = infix[i];
			break;
		}
	}

	while (stack.top > 0) {
		postfix[j++] = pop(&stack);
	}

	return;
}

int op_cal(int num1, int num2, char op)
{
	switch (op) {
	case '+':
		return num1 + num2;
		break;
	case '-':
		return num1 - num2;
		break;
	case '*':
		return num1 * num2;
		break;
	case '/':
		return num1 / num2;
		break;
		break;
	default:
		printf("op is unknown\n");
		return -1;
		break;
	}
}

int cal_postfix(char *postfix)
{
	int i, result, num1, num2;
	struct stack_t stack;

	if (!postfix) {
		printf("postfix is null\n");
		return -1;
	}

	stack.top = 0;
	memset(stack.stack_arr, '\0', sizeof(stack.stack_arr));

	for (i = 0; i < strlen(postfix); i++) {
		switch (postfix[i]) {
		case '+':
		case '-':
		case '*':
		case '/':
			num2 = (int)pop(&stack) - 48;
			num1 = (int)pop(&stack) - 48;
			result = op_cal(num1, num2, postfix[i]);
			(void)push(&stack, (char)(result + 48));
			break;
		default:
			(void)push(&stack, postfix[i]);
			break;
		}
	}
	result = pop(&stack) - 48;

	return result;
}

int main(int argc, char **argv)
{
	int i, len;
	char *postfix;
	char infix[2][STACK_SIZE] = {
		"5/3*(1-4)+3-8",
		"5*8+2*9/3-9"
	};

	len = sizeof(infix) / sizeof(infix[0]);
	for (i = 0; i < len; i++) {
		postfix = (char *)calloc(strlen(infix[i]), sizeof(char));
		printf("infix: %s", infix[i]);
		in_to_postfix(infix[i], postfix);
		printf(", postfix: %s", postfix);
		printf(", result: %d", cal_postfix(postfix));
		printf("\n");
		free(postfix);
	}

	return 0;
}

