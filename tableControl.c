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

int HashCode(struct Table *table, int key){
	if(key<0){
		return -1;
	}
	return key%table->size;
}

void insert(struct Table *table, int key, Message *val){
	int pos = HashCode(table, key);
	struct Entry *list = table->list[pos];
	struct Entry *newEntry = (struct Entry*)malloc(sizeof(struct Entry));
	struct Entry *temp = list;
	struct Message* temp_msg = val;

	while(temp){
		if(temp->key == key){	//if exist
			temp_msg = temp->val;	//compare version
			if(temp_msg->msg_version < val->msg_version){
				temp->val = val;	//update val
			}
		}
		temp = temp->next;
	} 
	newEntry->key = key;
	newEntry->val = val;
	newEntry->next = list;
	table->list[pos] = newEntry;
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
	return -1;	//can't find
}

//Check Complete
/*
int main(){
	struct Table *t = CreateTable(5);
	insert(t, 2, 3);
	insert(t, 5, 4);
	printf("%d", Search(t, 5));
	return 0;
}
*/

