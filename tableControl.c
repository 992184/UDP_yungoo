#include "yungoo.h"

/*
	table : HASH

	search
	duplicate->discard new
	update -> delete old -> insert new
*/

struct Table *CreateTable(int size){
	struct Table *table = (struct Table*)malloc(sizeof(struct Table));
	table->size = size;
	table->list = (struct Entry**)malloc(sizeof(struct Entry)*size);
	int i;
	for(i = 0; i < size; i++){
		table->list[i] = NULL;
	}
	return table;
}

//key into position
int HashCode(struct Table *table, int key){
	if(key<0){
		return -1;
	}
	return key;
	//return key%table->size;
}


void insert(struct Table *table, Message *val){
	
	bool isExist = false;
	//set key
	int key = val->dev_num;
	int pos = HashCode(table, key);

	//get entry
	struct Entry *list = table->list[pos];
	struct Entry *newEntry = (struct Entry*)malloc(sizeof(struct Entry));
	struct Entry *temp = list;
	struct Message* temp_msg;
	//printf("list->key: %d\n", list->key);		
	while(temp){
		if(temp->key == key){	//if exist
			temp_msg = temp->val;	//compare version
			if(temp_msg->msg_version <= val->msg_version){
				temp->val = val;	//update val
			}
			isExist = true;
		}
		temp = temp->next;
	}
	
	//if not exist
	if(!isExist){
		newEntry->key = key;
		newEntry->val = val;
		newEntry->next = list;
		table->list[pos] = newEntry;
	}
}

//search by key -> return val
int Search(struct Table *table, int key){
	int pos = HashCode(table, key);
	struct Entry *list = table->list[pos];
	struct Entry *temp = list;
	while(temp){
		if(temp->key == key){
			return temp->val;
		}
		temp = temp->next;
	}
	return -1;	//can
}

//print all the table item
void printTable(Table *table){
	struct Entry *temp = table->list[1];//from first DEVNUM
	struct Message *temp_msg;
	printf("==========TABLE==========\n");
	while(temp){
		temp_msg = temp->val;
		printf("FROM: %2d, MSG: %2d\n", temp_msg->dev_num, temp_msg->msg_version);
		temp = temp->next;
	}
	printf("===========END===========\n\n");
}
