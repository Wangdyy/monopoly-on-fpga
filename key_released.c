#define QUEUE_TYPE KeyReleased

typedef enum key_released {
	ENTER,
	UP,
	LEFT,
	DOWN,
	RIGHT,
	INVALID
} KeyReleased;

///////////////////////////////////////////////////////////////////////////////
// Implementing the Queue data structure //
typedef struct queue {
	unsigned int size, start, end;
	QUEUE_TYPE *elems;
} Queue;

Queue create_queue(unsigned int max_size) {
	Queue q;
	
	q.size = max_size;
	q.start = 0;
	q.end = 0;

	q.elems = (QUEUE_TYPE*) malloc (sizeof(QUEUE_TYPE) * (max_size + 1));
	if (!q.elems) {
		printf("Unable to allocate queue of size %d\n", max_size);
		exit(-1);
	}
	return q;
}

void queue_enqueue(Queue *q, QUEUE_TYPE c) {
	if (q -> start == (q -> end + 1) % (q -> size + 1)) {
		printf("Cannot insert any more elements into queue\n");
		exit(-1);
	}

	q -> elems[q -> end] = c;
	q -> end = (q -> end + 1) % (q -> size + 1);
}

QUEUE_TYPE queue_dequeue(Queue *q) {
	if (q -> start == q -> end) {
		printf("Cannot dequeue element since queue is empty\n");
		exit(-1);
	}

	QUEUE_TYPE ret = q -> elems[q -> start];
	q -> start = (q -> start + 1) % (q -> size + 1);
	return ret;
}

void destroy_queue(Queue *q) {
	free(q -> elems);
}

///////////////////////////////////////////////////////////////////////////////
// Processing PS2 Keyboard Inputs //
KeyReleased map_keycode_to_key(char make_code) {
	/* 	take advantage of the pattern that the two-byte break code of all keys 
		relevant to us are in the form of '<E0> F0 (MAKE_CODE)'
	*/
	switch (make_code)
	{
	case 0x5A:
		return ENTER;
	
	case 0x75:
		return UP;
	
	case 0x6B:
		return LEFT;

	case 0x72:
		return DOWN;
	
	case 0x74:
		return RIGHT;
	
	default:
		return INVALID;
	}
}

void print_key(KeyReleased k) {
	switch (k)
	{
	case ENTER:
		printf("Enter");
		break;
	
	case UP:
		printf("Up");
		break;
	
	case LEFT:
		printf("Left");
		break;

	case DOWN:
		printf("Down");
		break;
	
	case RIGHT:
		printf("Right");
		break;
	
	default:
		printf("Invalid");
		break;
	}
}

void print_key_released_queue(Queue q) {
	int i = q.start;

	while (i != q.end) {
		print_key(q.elems[i]);
		printf(" ");
		i = (i + 1) % (q.size + 1);
	}

	printf("\n");
}

char read_next_char() {
	// base code taken from http://www-ug.eecg.toronto.edu/msl/handouts/DE1-SoC_Computer_Nios.pdf 
	volatile int * PS2_ptr = (int *) 0xFF200100; // PS/2 port address
	int data_row, data_valid;
	char data_char = 0x00;
	
	while (1) {
		data_row = *(PS2_ptr); // read the Data register in the PS/2 port
		data_valid = data_row & 0x8000; // extract the data_valid field
		
		if (data_valid) {
			data_char = data_row & 0xFF;
			return data_char;
		}
	}
}

KeyReleased read_next_key() {
	while (1) {
		char c = read_next_char();
		if (c != 0xF0) continue;

		return map_keycode_to_key(read_next_char());
	}
}

///////////////////////////////////////////////////////////////////////////////
// Demo //
int main(){
	Queue q = create_queue(5);
	int cnt = 0;
	while(cnt < 5) {
		KeyReleased next_key = read_next_key();
		if (next_key == INVALID) continue;

		queue_enqueue(&q, next_key);
		print_key_released_queue(q);
		cnt += 1;
	}

	printf("\nNow pop the objects one by one:\n");

	for (int i = 0; i < 5; i++) {
		print_key(queue_dequeue(&q));
	}
	return 0;
}
