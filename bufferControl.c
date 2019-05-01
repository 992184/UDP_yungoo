/*
	Control buffer
 */

#include "yungoo.h"

void InitQueue(Queue *queue){
	queue->front = queue->rear = NULL;
	queue->count = 0;
}

int IsEmpty(Queue *queue){
	return queue->count == 0;	//if empty, true
}	

void Enqueue(Queue *queue, Message *newMessage){
	Node *newNode = (Node*)malloc(sizeof(Node));
	//Message *newMessage = (Message*)malloc(sizeof(Message));
	
	//newMessage->msg_version = data;

	newNode->data = newMessage;
	newNode->next = NULL;

	if(IsEmpty(queue)){	//if isEmpty
		queue->front = newNode;
	} else {
		queue->rear->next = newNode;
	}

	queue->rear = newNode;	//end = newNode
	queue->count++;
}

int Dequeue(Queue *queue){
	int re = 0;
	Node *delNode;
	if(IsEmpty(queue)){
		return re;
	}

	delNode = queue->front;	//delete front
	re = delNode->data->msg_version;	//return delNode data
	queue->front = delNode->next;
	free(delNode);
	queue->count--;
	return re;
}
/*
int main(){
	int i;
	Queue queue;

	InitQueue(&queue);
	for(i = 1; i<6; i++){
		Enqueue(&queue, i);
	}
	while(!IsEmpty(&queue)){
		printf("%d", Dequeue(&queue));
	}
	printf("/n");

	return 0;
}

*/

