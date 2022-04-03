//
// Created by nikita on 16.03.2022.
//
//#include "hid.h"

#include "usbd_hid.h"
#include "hid.h"

#define SIZE 10

uint32_t items[SIZE];
int front = -1, rear =-1;

extern USBD_HandleTypeDef hUsbDeviceFS;
uint32_t delay = 10;

keycodes keyboardHID = {0,0,0,0,0,0,0,0};

int isFull()
{
    if( (front == rear + 1) || (front == 0 && rear == SIZE-1)) return 1;
    return 0;
}

int isEmpty()
{
    if(front == -1) return 1;
    return 0;
}

void enQueue(uint32_t element)
{
    if(isFull()) return;
    else
    {
        if(front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        items[rear] = element;
//        printf("\n Inserted -> %d", element);
    }
}


void deQueue()
{
    uint32_t element;
    if(isEmpty()) {
//        printf("\n Queue is empty !! \n");
        return;
    } else {
        element = items[front];
        if (front == rear){
            front = -1;
            rear = -1;
        } /* В Q есть только один элемент, поэтому мы сбрасываем очередь после ее удаления. */
        else {
            front = (front + 1) % SIZE;

        }
        HidRaportSender(element);
//        printf("\n Deleted element -> %d \n", element);
        return;
    }
}

void HidRaportSender(uint32_t ui){
        switch (ui) {
            case 240:{
                keyboardHID.KEYCODE1 = 0x27;  // press '0'
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                HAL_Delay (delay);
                keyboardHID.KEYCODE1 = 0x00;  // r
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                break;
            }
            case 225:{
                keyboardHID.KEYCODE1 = 0x1E;  // press '1'
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                HAL_Delay (delay);
                keyboardHID.KEYCODE1 = 0x00;  // r
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                break;
            }
            case 210:{
                keyboardHID.KEYCODE1 = 0x1F;  // press '2'
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                HAL_Delay (delay);
                keyboardHID.KEYCODE1 = 0x00;  // r
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                break;
            }
            case 195:{
                keyboardHID.KEYCODE1 = 0x20;  // press '3'
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                HAL_Delay (delay);
                keyboardHID.KEYCODE1 = 0x00;  // r
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                break;
            }
            case 180:{
                keyboardHID.KEYCODE1 = 0x21;  // press '4'
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                HAL_Delay (delay);
                keyboardHID.KEYCODE1 = 0x00;  // r
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                break;
            }
            case 165:{
                keyboardHID.KEYCODE1 = 0x22;  // press '5'
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                HAL_Delay (delay);
                keyboardHID.KEYCODE1 = 0x00;  // r
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                break;
            }
            case 150:{
                keyboardHID.KEYCODE1 = 0x23;  // press '6'
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                HAL_Delay (delay);
                keyboardHID.KEYCODE1 = 0x00;  // r
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                break;
            }
            case 135:{
                keyboardHID.KEYCODE1 = 0x24;  // press '7'
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                HAL_Delay (delay);
                keyboardHID.KEYCODE1 = 0x00;  // r
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                break;
            }
            case 120:{
                keyboardHID.KEYCODE1 = 0x25;  // press '8'
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                HAL_Delay (delay);
                keyboardHID.KEYCODE1 = 0x00;  // r
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                break;
            }
            case 105:{
                keyboardHID.KEYCODE1 = 0x26;  // press '9'
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                HAL_Delay (delay);
                keyboardHID.KEYCODE1 = 0x00;  // r
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                break;
            }
            case 90:{
                keyboardHID.KEYCODE1 = 0x2A;  // press 'del'
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                HAL_Delay (delay);
                keyboardHID.KEYCODE1 = 0x00;  // r
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                break;
            }
            case 75:{
                keyboardHID.KEYCODE1 = 0x28;  // press 'enter'
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                HAL_Delay (delay);
                keyboardHID.KEYCODE1 = 0x00;  // r
                USBD_HID_SendReport(&hUsbDeviceFS, &keyboardHID, sizeof (keyboardHID));
                break;
            }
        }
    }