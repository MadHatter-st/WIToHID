//
// Created by nikita on 16.03.2022.
//

#ifndef PROJECT_KURS_HID_H
#define PROJECT_KURS_HID_H

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "usbd_hid.h"
#include "usb_hid_keys.h"

#define KEY_QUEUE_SIZE 100


#define KEY_INPUT_STATE_WAIT  0
#define KEY_INPUT_STATE_PRESS  1
#define KEY_INPUT_STATE_RELEASE  2

uint8_t KeyInputQueueIsFull();
uint8_t KeyInputQueueIsEmpty();

uint8_t KeyInputMap(uint8_t key);

void KeyInputLoop();

uint8_t KeyInputQueueEnQueue(uint8_t element);
uint8_t KeyInputQueueDeQueue();
uint8_t KeyInputQueuePeekQueue();

#endif //PROJECT_KURS_HID_H