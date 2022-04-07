//
// Created by nikita on 30.03.2022.
//

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
        } else{
            return -1;
        }
    }
};

 uint8_t WiegandCard(){
    return wig[0].current_index>8?1:0;
}


uint8_t WiegandGetKey(uint8_t buff[],int i){
     uint8_t lenght = 0;
        if (wig[i].current_index > 8) {
            wig[i].last_read_time = HAL_GetTick();
            for (int i = 0, j = 10; i < 10;lenght++, ++i) {
                buff[i] = wig[i].uit % 10;
                wig[i].uit /= j;
            }
        } else {
            wig[i].last_read_time = HAL_GetTick();
            buff[0] = wig[i].uit;
            lenght++;
        }
        return lenght;
};
