#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define QUEUE_SIZE 5

struct queue_t {
	int rear;
	int front;
	int queue_arr[QUEUE_SIZE];
};

void print_queue(struct queue_t *queue)
{
	int i;

	printf("Queue: [ ");
	for (i = 0; i < QUEUE_SIZE; i++) {
		printf("%2d ", queue->queue_arr[i]);
	}
	printf("] rear: %d front: %d\n", queue->rear, queue->front);
}

int enqueue(struct queue_t *queue, int val)
{
	if (queue->rear > (QUEUE_SIZE - 1)) {
		return -1;
	}

	queue->queue_arr[queue->rear++] = val;
	return 0;
}

int dequeue(struct queue_t *queue)
{
	if (queue->rear == queue->front)
		return -1;

	return queue->queue_arr[queue->front++];
}

int main(int argc, char **argv)
{
	int i, flag, num;
	struct queue_t queue;

	/* Initial the queue */
	queue.front = 0;
	queue.rear = 0;
	memset(queue.queue_arr, -1, sizeof(queue.queue_arr));

	srand(time(NULL));

	for (i = 0; i < 10; i++) {
		flag = rand() % 2;
		num = rand() % 100;
		switch (flag) {
		case 0:
			printf("Enqueue: %d\n", num);
			if (enqueue(&queue, num) == -1)
				printf("Queue is full\n");
			break;
		case 1:
			printf("Dequeue: ");
			num = dequeue(&queue);
			if (num == -1)
				printf("Queue is empty\n");
			else
				printf("%d\n", num);
			break;
		}
		print_queue(&queue);
	}
	return 0;
}

