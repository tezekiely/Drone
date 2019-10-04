#include <stdio.h>
#include <unistd.h>    // read/write usleep
#include "Ads1115.h"

int main()
{
    while(1){

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

//바닥에 테이프 붙여놓은게 왼쪽

//왼쪽 (제자리에서 움직임)        
        if(Lx>=3.0){
            if(Ly<=2.0){
                printf("URr\n");
            }
            else if(Ly>=3.0){
                printf("DRr\n");
            }
            else if(2.0<Ly<3.0){
                printf("Rr\n");
            }
        }
        else if(Lx<=2.0){
            if(Ly<=2.0){
                printf("ULr\n");
            }
            else if(Ly>=3.0){
                printf("DLr\n");
            }
            else if(2.0<Ly<3.0){
                printf("Lr\n");
            }
        }
        else if(2.0<Lx<3.0){
            if(Ly<=2.0){
                printf("U\n");
            }
            else if(Ly>=3.0){
                printf("D\n");
            }
            else if(2.0<Ly<3.0){
                printf("...\n");
            }
        }

//오른쪽 (전후좌우))
        if(Rx>=3.0){
            if(Ry<=2.0){
                printf("FR\n");
            }
            else if(Ry>=3.0){
                printf("BR\n");
            }
            else if(2.0<Ry<3.0){
                printf("R\n");
            }
        }
        else if(Rx<=2.0){
            if(Ry<=2.0){
                printf("FL\n");
            }
            else if(Ry>=3.0){
                printf("BL\n");
            }
            else if(2.0<Ry<3.0){
                printf("L\n");
            }
        }
        else if(2.0<Rx<3.0){
            if(Ry<=2.0){
                printf("F\n");
            }
            else if(Ry>=3.0){
                printf("B\n");
            }
            else if(2.0<Ry<3.0){
                printf("...\n");
            }
        }

        printf("\n");

    sleep(1);
    }
}
