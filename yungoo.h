#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLINE		511
#define BLOCK		255
#define PORT		2000
#define MAXDEV		10

#define DEVNUM		1

/*location struct*/
typedef struct LI{
	double	loc_x;
	double	loc_y;
	double	loc_z;
}GI;

/*Message struct*/
typedef struct Message{
	int			dev_num;	
	int 		msg_version;	
	struct LI	loc_info;
}Message;

/*table*/
typedef struct Entry{
	int 			key;
	struct Message	*val;
	struct Entry	*next;
}Entry;

typedef struct Table{
	int 	size;
	struct 	Entry **list;
}Table;

struct Table *CreateTable(int size);
int HashCode(struct Table *table, int key);
void insert(struct Table *table, int key, Message* val);
int Search(struct Table *table, int key);

/*Queue*/
typedef struct Node{
	struct Message	*data;
	struct Node 	*next;
}Node;

typedef struct Queue{
	Node	*front;
	Node	*rear;
	int		count;
}Queue;

void InitQueue(Queue *queue);
int IsEmpty(Queue *queue);
void Enqueue(Queue *queue, Message *newMessage);
int Dequeue(Queue *queue);


