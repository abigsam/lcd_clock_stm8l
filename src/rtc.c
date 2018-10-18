/*

*/


#include "rtc.h"

#define TIME_DATA_TYPE      (RTC_Format_BCD) //BCD or bin


/*--------------------------------------------------------
--- Private functions
--------------------------------------------------------*/



/*--------------------------------------------------------
--- Public functions
--------------------------------------------------------*/

/**
 * @brief   Initilize RTC
 * @retval  SUCCESS if all OK
*/
ErrorStatus RTC_init(void)
{
    RTC_InitTypeDef init_struct;
    RTC_TimeTypeDef time_struct;
    RTC_DateTypeDef data_struct;
    /* Choose RTC clocking source */
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
    
    /* Initilize RTC with default parameters
       This inits RTC with 1 Hz clock for 32768 Hz crystal */
    RTC_StructInit(&init_struct);
    init_struct.RTC_HourFormat = RTC_TIME_FORMAT;
    if (SUCCESS != RTC_Init(&init_struct)) { return ERROR; }
    
    /* Set to default  time and data */
    RTC_TimeStructInit(&time_struct);
    if (SUCCESS != RTC_SetTime(TIME_DATA_TYPE, &time_struct)) { return ERROR; }
    data_struct.RTC_WeekDay = RTC_DEFAULT_WEEK;
    data_struct.RTC_Date = RTC_DEFAULT_DATE;
    data_struct.RTC_Month = RTC_DEFAULT_MONTH;
    data_struct.RTC_Year = RTC_DEFAULT_YEAR;
    if (SUCCESS != RTC_SetDate(TIME_DATA_TYPE, &data_struct)) { return ERROR; }
    
    return SUCCESS;
}






 
