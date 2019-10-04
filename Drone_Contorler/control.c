#include <stdio.h>
#include <unistd.h>    // read/write usleep
#include <string.h>
#include <stdlib.h>
#include "Ads1115.h"

char *control()
{
        uint8_t L_vrx[3] = {1, 0b11000011, 0b10000101};
        uint8_t L_vry[3] = {1, 0b11010011, 0b10000101};
        uint8_t R_vrx[3] = {1, 0b11100011, 0b10000101};
        uint8_t R_vry[3] = {1, 0b11110011, 0b10000101};
        
        float Lx = Ads1115(L_vrx);
        float Ly = Ads1115(L_vry);
        float Rx = Ads1115(R_vrx);
        float Ry = Ads1115(R_vry);
        
        printf("Lx : %4.3f\n", Lx);
        printf("Ly : %4.3f\n", Ly);
        printf("Rx : %4.3f\n", Rx);
        printf("Ry : %4.3f\n", Ry);
        
        printf("\n");

        char *Lresult = malloc(sizeof(char) * 10);
        char *Rresult = malloc(sizeof(char) * 3);

//바닥에 테이프 붙여놓은게 왼쪽

//왼쪽 (제자리에서 움직임)        
        if(Lx>=3.0){
            if(Ly<=2.0){
                strcpy(Lresult, "U Rr ");
            }
            else if(Ly>=3.0){
                strcpy(Lresult, "D Rr ");
            }
            else if(2.0<Ly<3.0){
                strcpy(Lresult, ". Rr ");
            }
        }
        else if(Lx<=2.0){
            if(Ly<=2.0){
                strcpy(Lresult, "U Lr ");
            }
            else if(Ly>=3.0){
                strcpy(Lresult, "D Lr ");
            }
            else if(2.0<Ly<3.0){
                strcpy(Lresult, ". Lr ");
            }
        }
        else if(2.0<Lx<3.0){
            if(Ly<=2.0){
                strcpy(Lresult, "U . ");
            }
            else if(Ly>=3.0){
                strcpy(Lresult, "D . ");
            }
            else if(2.0<Ly<3.0){
                strcpy(Lresult, ". . ");
            }
        }

        

//오른쪽 (전후좌우))
        if(Rx>=3.0){
            if(Ry<=2.0){
                strcpy(Rresult, "FR");
            }
            else if(Ry>=3.0){
                strcpy(Rresult, "BR");
            }
            else if(2.0<Ry<3.0){
                strcpy(Rresult, "R");
            }
        }
        else if(Rx<=2.0){
            if(Ry<=2.0){
                strcpy(Rresult, "FL");
            }
            else if(Ry>=3.0){
                strcpy(Rresult, "BL");
            }
            else if(2.0<Ry<3.0){
                strcpy(Rresult, "L");
            }
        }
        else if(2.0<Rx<3.0){
            if(Ry<=2.0){
                strcpy(Rresult, "F");
            }
            else if(Ry>=3.0){
                strcpy(Rresult, "B");
            }
            else if(2.0<Ry<3.0){
                strcpy(Rresult, ".");
            }
        }

        printf("Lresult : %s\n", Lresult);
        printf("Rresult : %s\n", Rresult);

        strcat(Lresult, Rresult);

        printf("result : %s", Lresult);

        printf("\n");
        free(Rresult);

    return Lresult;

    free(Lresult);
}
