//
// Created by nikita on 16.03.2022.
//

#ifndef PROJECT_KURS_WIGAND_H
#define PROJECT_KURS_WIGAND_H

#include "main.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"

struct wiegand{
    uint32_t  D0_Pin;
    uint32_t  D1_Pin;
    uint32_t  last_read_time;
    uint8_t current_index;
    uint32_t uit;
    uint8_t values[32];
};

void WiegandInit(struct wiegand w);   //initialisation wiegand
void WiegandRead(uint16_t GPIO_Pin, struct wiegand w);   //
uint8_t WiegandIsAvaliable(); //
void WiegandGetKey(uint32_t buff[], struct wiegand w); //
uint8_t WiegandCard();

#endif //PROJECT_KURS_WIGAND_H