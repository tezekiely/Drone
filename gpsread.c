#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){

	FILE *fp;
	fp = fopen("gps.txt", "r");
	
	char buffer[20];

	while(!feof(fp)){
		char addr[100]="https://us-central1-my-drone-project-250402.cloudfunctions.net/addMessage?";
		fgets(buffer, sizeof(buffer), fp);
		strcat(addr,buffer); 

		printf("%s\n", addr);
		sleep(1);
	}
	
	fclose(fp);

	return 0;
}
