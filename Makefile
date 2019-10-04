gps_send: gps_send.o
	gcc -o gps_send gps_send.o -lcurl

deploy :
	firebase deploy --only functions
