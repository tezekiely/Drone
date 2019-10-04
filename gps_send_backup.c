/* <DESC>
 * Simple HTTPS GET
 * </DESC>
 */ 
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	FILE *t1,*t2,*t3;
	t1 = fopen("test_drone1_gps.txt", "r");
	t2 = fopen("test_drone2_gps.txt", "r");
	t3 = fopen("test_drone3_gps.txt", "r");

	char buffer1[50];
	char buffer2[50];
	char buffer3[50];

	char *format="https://us-central1-droneserverdev.cloudfunctions.net/addMessage?lat1=%f&lng1=%f&alt1=%f&lat2=%f&lng2=%f&alt2=%f&lat3=%f&lng3=%f&alt3=%f";
	
	while(!feof(t1) && !feof(t2) && !feof(t3)){
		fgets(buffer1, sizeof(buffer1), t1);
		fgets(buffer2, sizeof(buffer2), t2);
		fgets(buffer3, sizeof(buffer3), t3);
		
		float lat1,lng1,alt1;
		float lat2,lng2,alt2;
		float lat3,lng3,alt3;

		sscanf(buffer1,"%f,%f,%f",&lat1,&lng1,&alt1);
		sscanf(buffer2,"%f,%f,%f",&lat2,&lng2,&alt2);
		sscanf(buffer3,"%f,%f,%f",&lat3,&lng3,&alt3);

		char *addr = malloc(1024);

		sprintf(addr,format,lat1,lng1,alt1,lat2,lng2,alt2,lat3,lng3,alt3);

		printf("%s\n", addr);

		CURL *curl;
		CURLcode res;
	
		curl_global_init(CURL_GLOBAL_DEFAULT);

		curl = curl_easy_init();
		if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, addr);
 
		#ifdef SKIP_PEER_VERIFICATION
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
 
#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you're connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure.
     */ 
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
 
    /* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);
    /* Check for errors */ 
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
	
		printf("\n");

    /* always cleanup */ 
		curl_easy_cleanup(curl);
		}
		curl_global_cleanup();

		sleep(0.05);
		free(addr);
	}
	
	fclose(t1);
	fclose(t2);
	fclose(t3);

	return 0;
}
