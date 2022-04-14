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
    wig[0].D1_Pin = D1_1_Pin;
    wig[0].D0_Pin = D0_1_Pin;
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
            if (GPIO_Pin == wig[i].D1_Pin) {
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
    return 100;
};
//30299051
//3029909591


uint8_t WiegandGetKey(char * buff,int i){
     uint8_t lenght = 1;
        if (wig[i].current_index > 8) {
            lenght = 11;
            sprintf(buff, "%010lu\n", wig[i].uit);
        } else {
            buff[0] = WiegandMap(wig[i].uit);
        }
        wig[i].current_index = 0;
        return lenght;
};

 uint8_t WiegandMap(uint8_t key){
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
