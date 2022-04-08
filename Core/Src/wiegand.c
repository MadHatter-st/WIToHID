//
// Created by nikita on 30.03.2022.
//

#include <stdio.h>
#include "wiegand.h"

struct wiegand* wig;
int wiegand_count;

void WiegandInit(struct wiegand * w, int lenght){
    wiegand_count = lenght;
    wig = w;
    for(int i = 0; i<lenght; i++){
        wig[i].current_index = 0;
        wig[i].uit = 0;
        wig[i].last_read_time = 0;
    }
};

void WiegandRead(uint16_t GPIO_Pin){
    for(int i=0;i<wiegand_count;i++) {
        if ((GPIO_Pin == wig[i].D1_Pin || GPIO_Pin == wig[i].D0_Pin) && wig[i].current_index < 33) {
            wig[i].values[wig[i].current_index++] = GPIO_Pin == wig[i].D0_Pin ? 1 : 0;                                  //можно будет переделать
            wig[i].uit = wig[i].uit << 1;
            if (GPIO_Pin == wig[i].D0_Pin) {
                wig[i].uit |= 1;
            }
            wig[i].last_read_time = HAL_GetTick();
        }
    }
};

uint8_t WiegandIsAvaliable(){
    for(int i=0; i<wiegand_count; i++) {
        if (wig[i].current_index > 0 && HAL_GetTick() - wig[i].last_read_time > 100) {
            return i;
        }
    }
    return -1;
};

 uint8_t WiegandCard(){
    return wig[0].current_index>8?1:0;
}


uint8_t WiegandGetKey(char * buff,int i){
     uint8_t lenght = 1;
        if (wig[i].current_index > 8) {
            lenght = 11;
            sprintf(buff, "%010d\n", wig[i].uit);
        } else {
            buff[0] = WiegandMap(wig[i].uit);
//            char stringNum[10];
//            int digits[10] = {1,2,3,4,5,6,7,8,9,0};
//            sprintf(stringNum,"%d%d%d%d%d%d%d%d%d%d",digits[0],digits[1],digits[2],digits[3],digits[4],digits[5],
//                    digits[6],digits[7],digits[8],digits[9]);
        }
        wig[i].current_index = 0;
        return lenght;
};

 char WiegandMap(uint8_t key){
     switch (key) {
         case 240: return '0';
         case 225: return '1';
         case 210: return '2';
         case 195: return '3';
         case 180: return '4';
         case 165: return '5';
         case 150: return '6';
         case 135: return '7';
         case 120: return '8';
         case 105: return '9';
         case 90: return '\n';
         case 75: return '\n';
     }
 }
