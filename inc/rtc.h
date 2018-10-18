/**


TODO:
  * Add function to configure wakeup every minutes
  * Add read time & data functiones
  * Add set time & data functiones
  * Add posibility to calibrate LSI
  * Add change format 12/24 (?)
  * Is it possible read subseconds ?

*/


#ifndef __RTC_H
#define __RTC_H

#ifdef __cplusplus
 extern "C" {
#endif


#include "stm8l15x.h"


#define RTC_TIME_FORMAT     (RTC_H12_AM) /* AM/PM notation is AM or 24 hour format / RTC_H12_PM (AM/PM notation is PM) */
#define RTC_DEFAULT_WEEK    (RTC_Weekday_Monday)
#define RTC_DEFAULT_DATE    (1)
#define RTC_DEFAULT_MONTH   (RTC_Month_January)
#define RTC_DEFAULT_YEAR    (18)

/*--------------------------------------------------------
--- Private functions
--------------------------------------------------------*/



/*--------------------------------------------------------
--- Public functions
--------------------------------------------------------*/
ErrorStatus RTC_init(void);



#ifdef __cplusplus
}
#endif

#endif //__RTC_H