//
// Created by nikita on 30.03.2022.
//

#include "wiegand.h"

struct wiegand wig;
void WiegandInit(struct wiegand w){//initialisation wiegand
    wig.D0_Pin = D0_1_Pin;
    wig.D1_Pin = D1_1_Pin;
    w = wig;
};

void WiegandRead(uint16_t GPIO_Pin, struct wiegand w){

    if((GPIO_Pin == wig.D1_Pin || GPIO_Pin == wig.D0_Pin)&&wig.current_index<33) {
        wig.values[wig.current_index++] = GPIO_Pin == wig.D0_Pin ? 1 : 0;
        wig.uit=wig.uit<<1;
        if(GPIO_Pin==wig.D0_Pin){
            wig.uit|=1;
        }
        wig.last_read_time = HAL_GetTick();
    }
    w = wig;
};

uint8_t WiegandIsAvaliable(){
    return wig.current_index>0 && HAL_GetTick()-wig.last_read_time>100;
};

void WiegandGetKey(uint32_t buff[], struct wiegand w){
    if(wig.current_index>8){
        wig.last_read_time = HAL_GetTick();
        for (int i = 0, j=10; i < 10 ; ++i) {
            buff[i]=wig.uit%10;
            wig.uit/=j;
        }
    for (int i = 0; i < 10; ++i) {
        switch (buff[i]) {
            case 0:{
                buff[i]=240;
                continue;
            }
            case 1:{
                buff[i]=225;  // press '1'
                continue;
            }
            case 2:{
                buff[i]=210;  // press '2'
                continue;
            }
            case 3:{
                buff[i]=195;  // press '3'
                continue;
            }
            case 4:{
                buff[i]=180;  // press '4'
                continue;
            }
            case 5:{
                buff[i]=165;  // press '5'
                continue;
            }
            case 6:{
                buff[i]=150;  // press '6'
                continue;
            }
            case 7:{
                buff[i]=135;  // press '7'
                continue;
            }
            case 8:{
                buff[i]=120;  // press '8'
                continue;
            }
            case 9:{
                buff[i]=105;  // press '9'
                continue;
                }
                default:continue;
        }
    }
    }
    else{
        wig.last_read_time = HAL_GetTick();
        buff[0]=wig.uit;
    }
    w = wig;
};

