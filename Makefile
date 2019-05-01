yungoo: yungoo.o bufferControl.o tableControl.o
		gcc -o yungoo yungoo.o bufferControl.o tableControl.o -lpthread 
sender.o: sender.c
	gcc -c yungoo.c
bufferControl.o: bufferControl.c
	gcc -c bufferControl.c
tableControl.o: tableControl.c
	gcc -c tableControl.c
all: yungoo
clean:
	rm -f *.o yungoo
