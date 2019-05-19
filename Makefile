yungoo: yungoo.o bufferControl.o tableControl.o dataControl.o
		gcc -o yungoo yungoo.o bufferControl.o tableControl.o dataControl.o -lpthread 
sender.o: sender.c
	gcc -c yungoo.c
bufferControl.o: bufferControl.c
	gcc -c bufferControl.c
tableControl.o: tableControl.c
	gcc -c tableControl.c
dataControl.o: dataControl.c
	gcc -c dataControl.c
all: yungoo
clean:
	rm -f *.o yungoo
