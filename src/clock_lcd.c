




#include "clock_lcd.h"
#include "utils.h"
#include "lcd_7segment_decode.h"


/* Defines */
#define USED_LCDRAM_BYTES   ((uint8_t) 4)

#ifndef NULL
    #define NULL            (0x00)
#endif

/* Macroses */
//#define LCD_LOWBAT_SET()        { lcdRam[3] |= (uint8_t) (1 << 2); }
//#define LCD_LOWBAT_RESET()      { lcdRam[3] &= ~((uint8_t)(1 << 2)); }
//#define LCD_SIGN_HBAR_SET()     { lcdRam[0] |= (uint8_t) 1; }
//#define LCD_SIGN_HBAR_RESET()   { lcdRam[0] &= ~((uint8_t) 1); }
//#define LCD_SIGN_VBAR_SET()     { lcdRam[3] |= (uint8_t) (1 << 3); }
//#define LCD_SIGN_VBAR_RESET()   { lcdRam[3] &= ~((uint8_t) (1 << 3)); }

#define LCD_INTR_CLR()          { LCD->CR3 |= (uint8_t)(LCD_CR3_SOFC); }


/* Constants */

/* Private variables */
uint8_t lcdRam[USED_LCDRAM_BYTES] = {0};

uint8_t tempFlag = 0u;


/*--------------------------------------------------------
--- Private functions
--------------------------------------------------------*/

/**
  * @brief  Put char on specified position on LCD
  * @note   Private
  * @param  ch: pointer to char
  * @param  pos: char position on LCD
  * @retval None
  */
static void put_char(char *ch, uint8_t pos) {
    uint8_t chCoded = convert_char(ch);
    switch(pos) {
        case (0u):
            /* SEG10...SEG16 */
            lcdRam[1] &= ~((uint8_t) 0xfc); //10,11,12,13,14,15
            lcdRam[2] &= ~((uint8_t) 0x01); //16
            //
            lcdRam[1] |= (chCoded & SEG_MASK_A) << 6; //14
            lcdRam[1] |= (chCoded & SEG_MASK_B) << 4; //13
            lcdRam[1] |= (chCoded & SEG_MASK_C) << 2; //12
            lcdRam[1] |= (chCoded & SEG_MASK_D) << 0; //11
            lcdRam[1] |= (chCoded & SEG_MASK_E) >> 2; //10
            lcdRam[1] |= (chCoded & SEG_MASK_F) << 2; //15
            lcdRam[2] |= (chCoded & SEG_MASK_G) >> 6; //16
        break;
        
        case (1u):
            /* SEG7...SEG9, SEG17...SEG20 */
            lcdRam[0] &= ~((uint8_t) 0x80); //7
            lcdRam[1] &= ~((uint8_t) 0x03); //8,9
            lcdRam[2] &= ~((uint8_t) 0x1e); //17,18,19,20
            //
            lcdRam[2] |= (chCoded & SEG_MASK_A) << 2; //18
            lcdRam[2] |= (chCoded & SEG_MASK_B) << 0; //17
            lcdRam[1] |= (chCoded & SEG_MASK_C) >> 1; //9
            lcdRam[1] |= (chCoded & SEG_MASK_D) >> 3; //8
            lcdRam[0] |= (chCoded & SEG_MASK_E) << 3; //7
            lcdRam[2] |= (chCoded & SEG_MASK_F) >> 2; //19
            lcdRam[2] |= (chCoded & SEG_MASK_G) >> 2; //20
        break;
        
        case (2u):
            /* SEG4...SEG6, SEG21...SEG24 */
            lcdRam[0] &= ~((uint8_t) 0x70); //4...6
            lcdRam[2] &= ~((uint8_t) 0xe0); //21...23
            lcdRam[3] &= ~((uint8_t) 0x01); //24
            //
            lcdRam[2] |= (chCoded & SEG_MASK_A) << 6; //22
            lcdRam[2] |= (chCoded & SEG_MASK_B) << 4; //21
            lcdRam[0] |= (chCoded & SEG_MASK_C) << 4; //6
            lcdRam[0] |= (chCoded & SEG_MASK_D) << 2; //5
            lcdRam[0] |= (chCoded & SEG_MASK_E) >> 0; //4
            lcdRam[2] |= (chCoded & SEG_MASK_F) << 2; //23
            lcdRam[3] |= (chCoded & SEG_MASK_G) >> 6; //24
        break;
        
        case (3u):
            /* SEG1...SEG3, SEG25...SEG27 */
            lcdRam[0] &= ~((uint8_t) 0x0e); //1,2,3
            lcdRam[3] &= ~((uint8_t) 0x0e); //25,26,27
            //
            lcdRam[3] |= (chCoded & SEG_MASK_A) << 2; //26
            lcdRam[3] |= (chCoded & SEG_MASK_B) << 0; //25
            lcdRam[0] |= (chCoded & SEG_MASK_C) << 1; //3
            lcdRam[0] |= (chCoded & SEG_MASK_D) >> 1; //2
            lcdRam[0] |= (chCoded & SEG_MASK_E) >> 3; //1
            //lcdRam[] |= (chCoded & SEG_MASK_F) >> ; //Not implemented
            lcdRam[3] |= (chCoded & SEG_MASK_G) >> 3; //27
        break;
        
        default: break;
    }
}


/**
  * @brief  Convert char to 7-segment coding (0b0HGFDCBA)
  * @note   Private
  * @param  None
  * @retval None
  */
static uint8_t convert_char(char *ch) {
    uint8_t outv = SPACE_SIGN;
    switch(*ch) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            outv = NUMBER_MAP[(*ch - '0')];
        break;
        
        case ' ':
            outv = SPACE_SIGN;
        break;
        
        case '*':
            outv = DEGREES_SIGN;
        break;
        
        case '-':
            outv = MINUS_SIGN;
        break;
        
        case 'c':
            outv = LETTER_SMALL_C;
        break;
        
        case 'h':
            outv = LETTER_SMALL_H;
        break;
        
        case 'u':
            outv = LETTER_SMALL_U;
        break;
        
        default:
            if (*ch >= 'A' && *ch <= 'Z') {
                outv = LETTER_MAP[(*ch - 'A')];
            }
            else if (*ch >= 'a' && *ch <= 'z') {
                outv = LETTER_MAP[(*ch - 'a')];
            }
            else {
                outv = SPACE_SIGN;
            }
        break;
    }
    return outv;
}


/**
  * @brief  Wait until LCD will be updated
  * @note   Switch CPU in WFI mode
  * @note   Private
  * @param  None
  * @retval None
  */
static void wait_for_update(void) {
    LCD_INTR_CLR();
    LCD_ITConfig(ENABLE);
    enableInterrupts();
    wfi();
    LCD_ITConfig(DISABLE);
    disableInterrupts();
}

/**
  * @brief  Show/hide decimal point
  * @note   Control one decimal point at once; all other are hided
  * @note   Private
  * @param  pos: decimap point position; 0...2
  * @retval None
  */
static void show_dpoint(uint8_t pos) {
    switch(pos) {
        case 0u: /* SEG10 */
            lcdRam[1] |= 0x4u;
        break;
        
        case 1u: /* SEG6 */
            lcdRam[0] |= 0x40u;
        break;
        
        case 2u: /* SEG2 */
            lcdRam[0] |= 0x4u;
        break;
        
        default: break;
    }
}


static void clear_all(void) {
    uint8_t cnt = 0u;
    for (; cnt < USED_LCDRAM_BYTES; ++cnt) {
        lcdRam[cnt] = LCD_RAM_RESET_VALUE;
    }
}


/*--------------------------------------------------------
--- Public functions
--------------------------------------------------------*/

/**
  * @brief  Init LCD controller
  * @note   Public
  * @param  initRTCclock: false if RTC already inited
  * @retval None
  */
void LCD_init(bool initRTCclock) {
    uint8_t cnt = 0u;
    
    /* Enable LCD/RTC clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);

    if (initRTCclock) {
        CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
//#if (USE_LSE > 0)
//        CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
//#else
        CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);
//#endif
    
    }
  
    /* Initialize the LCD */
    LCD_Init(LCD_PRESCALLER, LCD_DIVIDER,
             LCD_Duty_Static, LCD_Bias_1_2,
             LCD_VOLTAGE_SOURCE);
  
    /* Mask register
    For declare the segements used: from 0 to 27 */
    LCD_PortMaskConfig(LCD_PortMaskRegister_0, 0xff); // 0...7
    LCD_PortMaskConfig(LCD_PortMaskRegister_1, 0xff); // 8...15
    LCD_PortMaskConfig(LCD_PortMaskRegister_2, 0xff); //16...23
    LCD_PortMaskConfig(LCD_PortMaskRegister_3, 0x0f); //24...27
  
    /* To set contrast to mean value */
    LCD_ContrastConfig(LCD_Contrast_3V0);
    LCD_DeadTimeConfig(LCD_DeadTime_0);
    LCD_PulseOnDurationConfig(LCD_PulseOnDuration_1);
    
    /* Clear LCD RAM */
    for (cnt = 0u; cnt <= LCD_RAMRegister_13; ++cnt) {
        LCD->RAM[cnt] = LCD_RAM_RESET_VALUE;
    }
    for (cnt = 0u; cnt < USED_LCDRAM_BYTES; ++cnt) {
        lcdRam[cnt] = LCD_RAM_RESET_VALUE;
    }
    
    /* Enable LCD peripheral */ 
    LCD_Cmd(ENABLE);
}


/**
  * @brief  Clear all segments
  * @note   Public
  * @param  None
  * @retval None
  */
void LCD_clear(void) {
    clear_all();
    wait_for_update();
}


/**
  * @brief  Enable all segments
  * @note   Public
  * @param  None
  * @retval None
  */
void LCD_ShowAll(void) {
    uint8_t cnt;
    for (cnt = 0u; cnt < USED_LCDRAM_BYTES; ++cnt) {
        lcdRam[cnt] = 0xff;
    }
    wait_for_update();
}

/**
  * @brief  Display string on LCD
  * @note   Public
  * @param  ptr: pointer to C-string
  * @retval None
  */
void LCD_DisplayString(uint8_t *ptr)
{
    uint8_t pcnt = 0u;
    uint8_t *p = NULL;
    clear_all();
    
    //Get last char before NULL
    p = str_getLast(ptr, LCD_NUM_POSITION+1);
    for (pcnt = 0u; (pcnt < LCD_NUM_POSITION) && (p >= ptr); ++pcnt, --p) {
        put_char((char*)p, pcnt);
    }
    
    //if (show_dp) { show_dpoint(point_pos); }
    wait_for_update();
}


/**
  * @brief  Show or hide "Battery Low" sign
  * @note   Public
  * @param  low_bat: show "LOBAT" sign if TRUE
  * @retval None
  */
void LCD_DisplayLowBat(bool low_bat) {
    //if (low_bat) { LCD_LOWBAT_SET(); }
    //else         { LCD_LOWBAT_RESET(); }
    wait_for_update();
}


/**
  * @brief  Show or hide left sigh on LCD
  * @note   Public
  * @param  sign: type of sign; can be:
  *         LCD_SIGN_NONE -- without any sign;
  *         LCD_SIGN_PLUS -- show '+' sign;
  *         LCD_SIGN_MINUS -- show '-' sign.
  * @retval None
  */
void LCD_ShowSign(LCD_SignTypeDef sign) {
    //switch(sign) {
    //    case LCD_SIGN_PLUS:
    //        LCD_SIGN_HBAR_SET();
    //        LCD_SIGN_VBAR_SET();
    //    break;
    //    
    //    case LCD_SIGN_MINUS:
    //        LCD_SIGN_HBAR_SET();
    //        LCD_SIGN_VBAR_RESET();
    //    break;
    //    
    //    case LCD_SIGN_NONE:
    //    default:
    //        LCD_SIGN_HBAR_RESET();
    //        LCD_SIGN_VBAR_RESET();
    //    break;
    //}
    wait_for_update();
}


/**
  * @brief  Update LCD RAM in interrupt with actual values
  * @note   Public
  * @param  None
  * @retval None
  */
void LCD_update(void) {
    uint8_t cnt;
    for (cnt = 0u; cnt < USED_LCDRAM_BYTES; ++cnt) {
        LCD->RAM[cnt] = lcdRam[cnt];
    }
    //Clear flag
    LCD_INTR_CLR();
}


//For debug
void LCD_debug(void) {
    char temp[4] = {'o', '3', '2', '-'};
    //
    put_char(temp,   0);
    put_char(temp+1, 1);
    put_char(temp+2, 2);
    put_char(temp+3, 3);
    wait_for_update();
}

/**
  * @brief  Control LCD
  * @note   Public
  * @param  state -- if TRUE LCD enabled; FALSE LCD disabled
  * @retval None
  */
void LCD_Control(bool state) {//, bool initRTCclock) {
  if (state) {
    LCD_init(TRUE);
  }
  else {
    LCD_DeInit();
    LCD_Cmd(DISABLE);
    CLK_PeripheralClockConfig(CLK_Peripheral_LCD, DISABLE);
  }
}

//EOF