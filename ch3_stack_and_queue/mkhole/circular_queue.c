#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RING_SIZE 8

struct ring_t {
	int head;
	int tail;
	int full_tag;
	int queue_arr[RING_SIZE];
};

void print_queue(struct ring_t *ring)
{
	int i;

	printf("Queue: [ ");
	for (i = 0; i < RING_SIZE; i++) {
		printf("%2d ", ring->queue_arr[i]);
	}
	printf("] head: %d tail: %d\n", ring->head, ring->tail);
}

int enqueue(struct ring_t *ring, int val)
{

	if((ring->head == ring->tail) && (ring->full_tag == 1))
		return -1;

	ring->head = (ring->head + 1) % RING_SIZE;
	if(ring->head == ring->tail)
		ring->full_tag = 1;

	ring->queue_arr[ring->head] = val;

	return 0;
}

int dequeue(struct ring_t *ring)
{
	if ((ring->tail == ring->head) && (ring->full_tag ==0))
		return -1;

	ring->tail = (ring->tail + 1) % RING_SIZE;
	if(ring->tail == ring->head)
		ring->full_tag = 0;

	return ring->queue_arr[ring->tail];
}

int main(int argc, char **argv)
{
	int i, flag, num;
	struct ring_t ring = {
		.tail = RING_SIZE - 1,
		.head = RING_SIZE - 1
	};

	/* Initial the queue */
	memset(ring.queue_arr, -1, sizeof(ring.queue_arr));

	srand(time(NULL));

	for (i = 0; i < 20; i++) {
		flag = rand() % 2;
		num = rand() % 100;
		switch (flag) {
		case 0:
			printf("Enqueue: %d\n", num);
			if (enqueue(&ring, num) == -1)
				printf("Queue is full\n");
			break;
		case 1:
			printf("Dequeue: ");
			num = dequeue(&ring);
			if (num == -1)
				printf("Queue is empty\n");
			else
				printf("%d\n", num);
			break;
		}
		print_queue(&ring);
	}
	return 0;
}

