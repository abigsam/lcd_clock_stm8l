





#ifndef __CLOCK_LCD_H
#define __CLOCK_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif


#include "stm8l15x.h"

#define LCD_USE_LSE         (0)

#define LCD_PRESCALLER      (LCD_Prescaler_1)
#define LCD_DIVIDER         (LCD_Divider_31)
#define LCD_VOLTAGE_SOURCE  (LCD_VoltageSource_Internal)
#define LCD_CONTRAST        (LCD_Contrast_3V0)

#define LCD_NUM_POSITION    (4U)


typedef enum {
    LCD_SIGN_NONE = 0,
    LCD_SIGN_PLUS,
    LCD_SIGN_MINUS
} LCD_SignTypeDef;



/*--------------------------------------------------------
--- Private functions
--------------------------------------------------------*/
static void put_char(char *ch, uint8_t pos);
static void wait_for_update(void);
static uint8_t convert_char(char *ch);
static void show_dpoint(uint8_t pos);
static void clear_all(void);



/*--------------------------------------------------------
--- Public functions
--------------------------------------------------------*/
void LCD_init(bool initRTCclock);
void LCD_clear(void);
void LCD_ShowAll(void);
void LCD_DisplayString(uint8_t *ptr);
void LCD_DisplayLowBat(bool low_bat);
void LCD_ShowSign(LCD_SignTypeDef sign);

void LCD_update(void);  //Inser this in LCD interrupt

void LCD_debug(void);

void LCD_Control(bool state);//, bool initRTCclock);

#ifdef __cplusplus
}
#endif

#endif //__CLOCK_LCD_H