//
// Created by nikita on 16.03.2022.
//
//#include "hid.h"

#include "hid.h"

uint8_t items[KEY_QUEUE_SIZE];
int key_queue_front = -1, key_queue_rear =-1;


extern USBD_HandleTypeDef hUsbDeviceFS;

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
} keyboardHID;

keyboardHID keyboardhid = {0,0,0,0,0,0,0,0};

uint32_t key_input_time = 0;
uint8_t key_input_state = KEY_INPUT_STATE_WAIT;

void KeyInputLoop() {
    uint32_t time = HAL_GetTick();
    switch(key_input_state) {
        case KEY_INPUT_STATE_WAIT: {
            if(!KeyInputQueueIsEmpty()) {
                uint8_t before = 0;
                for(int i=1; i <= 1 && !KeyInputQueueIsEmpty() && (i==0 || before != KeyInputQueuePeekQueue()); i++) {
                    switch (i) {
                        case 1: before = KeyInputQueueDeQueue(); keyboardhid.KEYCODE1 = KeyInputMap(before); break;
                        case 2: before = KeyInputQueueDeQueue(); keyboardhid.KEYCODE2 = KeyInputMap(before); break;
                        case 3: before = KeyInputQueueDeQueue(); keyboardhid.KEYCODE3 = KeyInputMap(before); break;
                        case 4: before = KeyInputQueueDeQueue(); keyboardhid.KEYCODE4 = KeyInputMap(before); break;
                        case 5: before = KeyInputQueueDeQueue(); keyboardhid.KEYCODE5 = KeyInputMap(before); break;
                        case 6: keyboardhid.KEYCODE6 = KeyInputMap(KeyInputQueueDeQueue()); break;
                    }
                }
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
                key_input_time = time + 15;
                key_input_state = KEY_INPUT_STATE_PRESS;
            }
            break;
        }
        case KEY_INPUT_STATE_PRESS: {
            if(time > key_input_time) {
                for(int i=1; i <= 1; i++) {
                    switch (i) {
                        case 1: keyboardhid.KEYCODE1 = 0; break;
                        case 2: keyboardhid.KEYCODE2 = 0; break;
                        case 3: keyboardhid.KEYCODE3 = 0; break;
                        case 4: keyboardhid.KEYCODE4 = 0; break;
                        case 5: keyboardhid.KEYCODE5 = 0; break;
                        case 6: keyboardhid.KEYCODE6 = 0; break;
                    }
                }
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
                key_input_time = time + 15;
                key_input_state = KEY_INPUT_STATE_RELEASE;
            }
            break;
        }
        case KEY_INPUT_STATE_RELEASE: {
            if(time > key_input_time) {
                key_input_state = KEY_INPUT_STATE_WAIT;
            }
        }
    }
}


uint8_t KeyInputQueueIsFull() {
    if((key_queue_front == key_queue_rear + 1) || (key_queue_front == 0 && key_queue_rear == KEY_QUEUE_SIZE - 1)) {
        return 1;
    }
    return 0;
}

uint8_t KeyInputQueueIsEmpty() {
    if(key_queue_front == -1) {
        return 1;
    }
    return 0;
}

uint8_t KeyInputQueueEnQueue(uint8_t element) {
    if(!KeyInputQueueIsFull()) {
        if(key_queue_front == -1) key_queue_front = 0;
        key_queue_rear = (key_queue_rear + 1) % KEY_QUEUE_SIZE;
        items[key_queue_rear] = element;
        return 1;
    }
    return 0;
}

uint8_t KeyInputQueueDeQueue() {
    char element;
    if(KeyInputQueueIsEmpty()) {
        return(0);
    } else {
        element = items[key_queue_front];
        if (key_queue_front == key_queue_rear){
            key_queue_front = -1;
            key_queue_rear = -1;
        }
        else {
            key_queue_front = (key_queue_front + 1) % KEY_QUEUE_SIZE;
        }
        return(element);
    }
}

uint8_t KeyInputQueuePeekQueue() {
    if(KeyInputQueueIsEmpty()) {
        return(0);
    } else {
        return(items[key_queue_front]);
    }
}

uint8_t KeyInputMap(uint8_t key) {
    switch (key) {
        case '0' : return KEY_0;
        case '1' : return KEY_1;
        case '2' : return KEY_2;
        case '3' : return KEY_3;
        case '4' : return KEY_4;
        case '5' : return KEY_5;
        case '6' : return KEY_6;
        case '7' : return KEY_7;
        case '8' : return KEY_8;
        case '9' : return KEY_9;
        case 'a' : return KEY_A;
        case 'b' : return KEY_B;
        case 'c' : return KEY_C;
        case 'd' : return KEY_D;
        case 'e' : return KEY_E;
        case 'f' : return KEY_F;
        case 'g' : return KEY_G;
        case 'h' : return KEY_H;
        case 'i' : return KEY_I;
        case 'j' : return KEY_J;
        case 'k' : return KEY_K;
        case 'l' : return KEY_L;
        case 'm' : return KEY_M;
        case 'n' : return KEY_N;
        case 'o' : return KEY_O;
        case 'p' : return KEY_P;
        case 'q' : return KEY_Q;
        case 'r' : return KEY_R;
        case 's' : return KEY_S;
        case 't' : return KEY_T;
        case 'u' : return KEY_U;
        case 'v' : return KEY_V;
        case 'w' : return KEY_W;
        case 'x' : return KEY_X;
        case 'y' : return KEY_Y;
        case 'z' : return KEY_Z;
        case '\n' : return KEY_ENTER;
        default: return 0x00;
    }
}
