/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_hid.h"
#include "wiegand.h"
#include "hid.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//extern USBD_HandleTypeDef hUsbDeviceFS;
//
//typedef struct
//{
//    uint8_t MODIFIER;
//    uint8_t RESERVED;
//    uint8_t KEYCODE1;
//    uint8_t KEYCODE2;
//    uint8_t KEYCODE3;
//    uint8_t KEYCODE4;
//    uint8_t KEYCODE5;
//    uint8_t KEYCODE6;
//} keyboardHID;
//
//keyboardHID keyboardhid = {0,0,0,0,0,0,0,0};
//
//
uint32_t uit=0;
uint8_t values[32];
uint32_t digits[10];
//uint32_t revdigits[10];
uint8_t current_index = 0;
uint32_t last_read_time = 0;
//uint32_t n1=0;
//
//void raportsender(uint32_t ui){
//    switch (ui) {
//        case 240:{
//            keyboardhid.KEYCODE1 = 0x27;  // press '0'
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            HAL_Delay (50);
//            keyboardhid.KEYCODE1 = 0x00;  // r
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            break;
//        }
//        case 225:{
//            keyboardhid.KEYCODE1 = 0x1E;  // press '1'
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            HAL_Delay (50);
//            keyboardhid.KEYCODE1 = 0x00;  // r
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            break;
//        }
//        case 210:{
//            keyboardhid.KEYCODE1 = 0x1F;  // press '2'
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            HAL_Delay (50);
//            keyboardhid.KEYCODE1 = 0x00;  // r
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            break;
//        }
//        case 195:{
//            keyboardhid.KEYCODE1 = 0x20;  // press '3'
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            HAL_Delay (50);
//            keyboardhid.KEYCODE1 = 0x00;  // r
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            break;
//        }
//        case 180:{
//            keyboardhid.KEYCODE1 = 0x21;  // press '4'
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            HAL_Delay (50);
//            keyboardhid.KEYCODE1 = 0x00;  // r
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            break;
//        }
//        case 165:{
//            keyboardhid.KEYCODE1 = 0x22;  // press '5'
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            HAL_Delay (50);
//            keyboardhid.KEYCODE1 = 0x00;  // r
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            break;
//        }
//        case 150:{
//            keyboardhid.KEYCODE1 = 0x23;  // press '6'
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            HAL_Delay (50);
//            keyboardhid.KEYCODE1 = 0x00;  // r
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            break;
//        }
//        case 135:{
//            keyboardhid.KEYCODE1 = 0x24;  // press '7'
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            HAL_Delay (50);
//            keyboardhid.KEYCODE1 = 0x00;  // r
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            break;
//        }
//        case 120:{
//            keyboardhid.KEYCODE1 = 0x25;  // press '8'
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            HAL_Delay (50);
//            keyboardhid.KEYCODE1 = 0x00;  // r
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            break;
//        }
//        case 105:{
//            keyboardhid.KEYCODE1 = 0x26;  // press '9'
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            HAL_Delay (50);
//            keyboardhid.KEYCODE1 = 0x00;  // r
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            break;
//        }
//        case 90:{
//            keyboardhid.KEYCODE1 = 0x2A;  // press 'del'
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            HAL_Delay (50);
//            keyboardhid.KEYCODE1 = 0x00;  // r
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            break;
//        }
//        case 75:{
//            keyboardhid.KEYCODE1 = 0x28;  // press 'enter'
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            HAL_Delay (50);
//            keyboardhid.KEYCODE1 = 0x00;  // r
//            USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof (keyboardhid));
//            break;
//        }
//    }
//}
struct wiegand w;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */
    WiegandInit(w);
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USB_DEVICE_Init();
    /* USER CODE BEGIN 2 */

    uint32_t blink_time = 200;
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {

        uint32_t time = HAL_GetTick();
        if(time > blink_time) {
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        }



            WiegandGetKey(digits, w);
            if(WiegandCard()){
                for(int i = 0; i < 9; i++ ){
                    HidRaportSender(digits[i]);
//                  enQueue(digits[i]);
                }
            }else{
                HidRaportSender(digits[0]);
//              enQueue(digits[0]);
            }
            if(w.current_index!=8){
                for(int i = 0; i < 9; i++ ){
//                  deQueue();
                }
            }else{
//              deQueue();
            }
        }

        if(current_index>0){
            uit =0;
        }

//      if(current_index > 0 && time - last_read_time > 100) {
//          blink_time = time + 200;
//
//          if(current_index>8){
//
//              for (int i = 0, j=10; i < 10 ; ++i) {
//                  digits[i]=uit%10;
//                  uit/=j;
//              }
//
////              for (int i = 0,j=9; i < 10; ++i,--j) {
////                  revdigits[i]=digits[j];
////              }
//
//              for (int i = 0,j=9; i < 4; ++i,--j) {
//                  uint32_t temp = digits[i];
//                  digits[i]=digits[j];
//                  digits[j] = temp;
//              }
//
//              for (int i = 0; i < 10; ++i) {
//                  switch (digits[i]) {
//                      case 0:{
//                          digits[i]=240;
//                          continue;
//                      }
//                      case 1:{
//                          digits[i]=225;  // press '1'
//                          continue;
//                      }
//                      case 2:{
//                          digits[i]=210;  // press '2'
//                          continue;
//                      }
//                      case 3:{
//                          digits[i]=195;  // press '3'
//                          continue;
//                      }
//                      case 4:{
//                          revdigits[i]=180;  // press '4'
//                          continue;
//                      }
//                      case 5:{
//                          digits[i]=165;  // press '5'
//                          continue;
//                      }
//                      case 6:{
//                          digits[i]=150;  // press '6'
//                          continue;
//                      }
//                      case 7:{
//                          digits[i]=135;  // press '7'
//                          continue;
//                      }
//                      case 8:{
//                          digits[i]=120;  // press '8'
//                          continue;
//                      }
//                      case 9:{
//                          digits[i]=105;  // press '9'
//                          continue;
//                      }
//                  }
//              }
//
//              for (int i = 0; i < 10; ++i) {
//
//                  raportsender(digits[i]);
//                  HAL_Delay (15);        //repair
//
//              }
//              raportsender(75);

//          }
//          else{
//              raportsender(uit);
//          }
//         current_index = 0;
//          uit = 0;


    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


/* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : LED_Pin */
    GPIO_InitStruct.Pin = LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : D0_1_Pin D1_1_Pin D0_2_Pin D1_2_Pin */
    GPIO_InitStruct.Pin = D0_1_Pin|D1_1_Pin|D0_2_Pin|D1_2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//    D1_1_Pin
//    D0_1_Pin

    WiegandRead(GPIO_Pin, w);
//    if((GPIO_Pin == D1_1_Pin || GPIO_Pin == D0_1_Pin)&&current_index<33) {
//        values[current_index++] = GPIO_Pin == D1_1_Pin ? 1 : 0;
//        uit=uit<<1;
//        if(GPIO_Pin==D1_1_Pin){
//            uit|=1;
//        }
//        last_read_time = HAL_GetTick();
//    }
//    WiegandRead(GPIO_Pin);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
