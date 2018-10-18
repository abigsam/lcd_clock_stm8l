



#ifndef __STM8L_ADC_H
#define __STM8L_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif


#include "stm8l15x.h"
#include "utils.h"
#include "delay.h"


#define DELAY_US(D)      do {} while (0);



void adc_config(void);
void adc_meas_lowp(uint16_t mdelay);
uint16_t get_batt_voltage(void);

void adc_intr(void); //Adc interrupt handler

#ifdef __cplusplus
}
#endif

#endif //__STM8L_ADC_H