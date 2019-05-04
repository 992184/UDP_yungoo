/*
	2019-01-29
	compile: make yungoo
			 make clean
	run: ./yungoo
*/


#include "yungoo.h"

Queue queue;	//bufferQueue
Table *table;	//other info table 


/*client*/
void* sender(void* arg){
	int sockfd = (int)arg; 
	char buffer[MAXLINE]; 
	struct sockaddr_in	 servaddr; 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY;//inet_addr("172.30.1.60");//INADDR_ANY; 
	
	int msg = 1; 	//seq num which send
	int temp = 1;	//seq num
	
	while(1){
										//if sth in the queue
		if(!IsEmpty(&queue)){
			msg = Dequeue(&queue);
			//printf("msg: %d\n", msg);
			printf("[Dequeue]\n");		//Dequeue
		} else{							//if queue is empty
			msg = temp;					//put temp to msg
			temp++;						//sequence number++
			printf("[Sequence]\n");		//use sequence number
		}
		
		//Filling Message information
		Message *send_msg = (Message*)malloc(sizeof(Message));
		send_msg->dev_num = DEVNUM;	//set device number
		send_msg->msg_version= msg;	//set version to seq num

		//send struct Message
		sendto(sockfd, send_msg, sizeof(Message), 
			MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
				sizeof(servaddr)); 
		printf("sender(): [%d] send %d\n\n", send_msg->dev_num, msg); 
		
		sleep(1);	//every 1 second
	}
	close(sockfd);
}

//server
void* receiver(void* arg){
	int sockfd = (int)arg; 
	char buffer[MAXLINE]; 
	//char* hello = "Hello from server"; 
	struct sockaddr_in servaddr, cliaddr; 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 	
			// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	}

	int recv_i, n, len; 
	int name, version;
	
	//Receive struct Message
	while(1){
		Message *recv_msg = (Message*)malloc(sizeof(Message));
		//MAXLINE -> sizeof(Message)
		n = recvfrom(sockfd, (Message*)recv_msg, sizeof(Message), 
					MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
					&len); 
		buffer[n] = '\0';
		//if get sth
		printf("receiver() received: %d\n", recv_msg->msg_version); 
		printf("receive msg from: %d\n", recv_msg->dev_num);
	
		recv_i = (recv_msg->msg_version);
		//int recv_name = atoi(recv_msg->dev_name);

		insert(table, recv_msg);			//key=device number, val=msg_version
		printf("KEY:%d, VAL: %d\n", recv_msg->dev_num, recv_i);
		Enqueue(&queue, recv_msg);			//put buffer to queue
		//printf("QUEUE GETS %s\n\n", buffer);
		printTable(table);
	}
}

// Driver code 
int main() { 

	int send_sock;
	int recv_sock;
	pthread_t	send_thread, recv_thread;
	void *		thread_result;

	InitQueue(&queue);	//init queue-> avoid segment fault
	table = CreateTable(MAXDEV);	//max device num

		// Creating socket file descriptor 
	if ( (send_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

		// Creating socket file descriptor 
	if ( (recv_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	//create thread
	pthread_create(&send_thread, NULL, sender, (void*)send_sock);
	pthread_create(&recv_thread, NULL, receiver, (void*)recv_sock);
	//join
	pthread_join(recv_thread, &thread_result);
	pthread_join(send_thread, &thread_result);

		/* 
		   //Queue Test
	int i;
	Queue queue;

	InitQueue(&queue);
	for(i = 1; i<6; i++){
		Enqueue(&queue, i);
	}
	while(!IsEmpty(&queue)){
		printf("%d", Dequeue(&queue));
	}
	*/
	//sender();
	//receiver();
	return 0;
} 
