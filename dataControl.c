#include "yungoo.h"

int version = 1;
LI* current_li;

void msg_initiate(Message* newMessage){
	
	LI* new_li = (LI*)malloc(sizeof(LI));
	//get_location();
	//if new_li != current_li
	//dataGenerator_newLocation(new_li);
	newMessage->dev_num = DEVNUM;
	newMessage->msg_version = version;
	newMessage->loc_info = new_li;
	printf("\n\n version++!!!! \n\n");
	version++;
}

struct Message* newMessage(){
	Message* new_msg = (Message*)malloc(sizeof(Message));
	msg_initiate(new_msg);	//set msg
	return new_msg;
}


void dataGenerator_newLocation(LI* new_li){
	version = 1;
	current_li = new_li;
}
