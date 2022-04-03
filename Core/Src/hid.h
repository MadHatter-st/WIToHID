//
// Created by nikita on 16.03.2022.
//

#ifndef PROJECT_KURS_HID_H
#define PROJECT_KURS_HID_H

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "usb_device.h"

typedef struct
{
    uint8_t MODIFIER;
    uint8_t RESERVED;
    uint8_t KEYCODE1;
    uint8_t KEYCODE2;
    uint8_t KEYCODE3;
    uint8_t KEYCODE4;
    uint8_t KEYCODE5;
    uint8_t KEYCODE6;
}keycodes;

int isFull();
int isEmpty();
void enQueue(uint32_t element);
void deQueue();
//void display();
void HidRaportSender(uint32_t ui);

#endif //PROJECT_KURS_HID_H