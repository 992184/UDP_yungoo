#include "yungoo.h"

int version = 1;

//return struct msg
//for sender

Message* newMessage(){
	struct Message* new_msg = (Message*)sizeof(Message);
	struct LI*		new_li = (LI*)sizeof(LI);
	
	//if location changed, version reset to 0

	//set struct LI
	new_li->loc_x = version;
	new_li->loc_y = version;
	new_li->loc_z = version;

	//set Struct Message
	new_msg->dev_num = DEVNUM;
	new_msg->msg_version = version;
	new_msg->loc_info = new_li;

	version++;	//version

	return new_msg;
}
