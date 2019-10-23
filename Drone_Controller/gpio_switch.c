#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <string.h>

#define Lsw	0	// GPIO.0, BCM_GPIO 17
#define Rsw	2	// GPIO.2, BCM_GPIO 27

char *Switch ()
{
	char *Swresult = malloc(sizeof(char) * 4);

	wiringPiSetup();


	pinMode(Lsw, INPUT);
	pinMode(Rsw, INPUT);

	pullUpDnControl(Lsw, PUD_UP);
	pullUpDnControl(Rsw, PUD_UP);

		strcpy(Swresult, " .");

		if(digitalRead(Lsw) == 0 && digitalRead(Rsw) == 0)
		{
			printf("LRsw\n");
			strcpy(Swresult, " LRsw");            // mS
		}
		else if(digitalRead(Lsw) == 0)
		{
			printf("Lsw\n");
			strcpy(Swresult, " Lsw");             // mS
		}
		else if(digitalRead(Rsw) == 0)
		{
			printf("Rsw\n");
			strcpy(Swresult, " Rsw");             // mS
		}


    printf("Switch : %s\n", Swresult);


	return Swresult;

	free(Swresult);
}