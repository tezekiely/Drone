CC = gcc
TARGET = client
OBJECTS = Ads1115.o control.o gpio_switch.o client.o

$(TARGET) : $(OBJECTS)
	$(CC) -o $@ $^ -lwiringPi

Ads1115.o : Ads1115.c

control.o : control.c

gpio_switch.o : gpio_switch.c

client.o: client.c -lcurl