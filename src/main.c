/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "delay.h"
#include "lcd.h"
#include "rtc.h"
#include "utils.h"

/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
#define FIRMWARE_VERSION        ((uint8_t *) "f02")

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void error_handler(uint8_t *msg, uint16_t err_num);
                   
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  uint8_t test_str[5] = {' ', '0', '0', '0', 0 };
  uint8_t cnt = 'A';
    
  /* Init harware */
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_16);
  LCD_init(TRUE);
  initRTCwakeup();
  
  /* Check LCD, show firmware version */
  sleep_ms(500u);
  LCD_ShowAll();
  sleep_ms(500u);
  LCD_DisplayString(FIRMWARE_VERSION);
  sleep_s(1);
  LCD_clear();
  sleep_ms(500u);
  
  //error_handler((uint8_t *)"Error Test", 18u);
  
  for(;;) {
    //LCD_ShowAll();
    //LCD_debug();
    //LCD_DisplayString((uint8_t *)" TST");
    
    test_str[1] = cnt++; if (cnt > 'Z') { cnt = 'A'; }
    test_str[2] = cnt++; if (cnt > 'Z') { cnt = 'A'; }
    test_str[3] = cnt++; if (cnt > 'Z') { cnt = 'A'; }
    
    LCD_DisplayString(test_str);
    sleep_s(1);
    LCD_clear();
    sleep_s(1);
  }
  
  /* Infinite loop */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @brief  Error handler function
  * @param  ptr: pointer to the error message
  * @param  err_num: error number
  * @retval None
  */
void error_handler(uint8_t *msg, uint16_t err_num)
{
  uint8_t err_msg[5] = {0};
  int2str(err_num, err_msg, 4);
  for(;;) {
    LCD_DisplayString((uint8_t *)" Err");
    sleep_ms(500u);
    LCD_DisplayString(err_msg);
    sleep_ms(500u);
  }
}


/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
