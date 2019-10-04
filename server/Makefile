CC = gcc
TARGET = send
OBJECTS = move.o sendDataCurl.o server.o urlwrite.o thread.o send.o 

$(TARGET) : $(OBJECTS)
	$(CC) -o $@ $^ -lcurl -lm -lpthread

move.o : move.c

sendDataCurl.o : sendDataCurl.c

server.o : server.c

urlwrite.o : urlwrite.c

thread.o : thread.c

send.o : send.c

clean : 
	rm *.o $(TARGET)
	
deploy :
	firebase deploy --only functions