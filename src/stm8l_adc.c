

#include "stm8l_adc.h"




/**
  * @brief  Configure ADC
  * @note   Private
  * @param  None
  * @retval None
  */
void adc_config(void) {
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
    ADC_Init(ADC1, ADC_ConversionMode_Single, ADC_Resolution_10Bit, ADC_Prescaler_2);
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, DISABLE);
}


/**
  * @brief  
  * @note   Private
  * @param  
  * @retval 
  */
uint16_t get_batt_voltage(void) {
    uint16_t res = 0u;
    //
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);
    ADC_VrefintCmd(ENABLE);
    DELAY_US(3u);
    ADC_ChannelCmd(ADC1, ADC_Channel_Vrefint, ENABLE);
    
    adc_meas_lowp(0);
    
    res = ADC_GetConversionValue(ADC1);
    ADC_ChannelCmd(ADC1, ADC_Channel_Vrefint, DISABLE);
    ADC_VrefintCmd(DISABLE);
    ADC_Cmd(ADC1, DISABLE);
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, DISABLE);
    return res;
}


/**
  * @brief  Start ADC convert with prestart delay and wait
  *         end convertation in low power mode
  * @note   Private
  * @param  mdelay: ADC prestart delay in ms
  * @retval None
  */
static void adc_meas_lowp(uint16_t mdelay) {
    if (mdelay) { DELAY_US(mdelay); }
    ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
    enableInterrupts();
    ADC_SoftwareStartConv(ADC1);
    wfi();
    disableInterrupts();
    ADC_ITConfig(ADC1, ADC_IT_EOC, DISABLE);
}


/**
  * @brief  Adc interrupt handler
  * @note   Public, copy to ADC interrupt handler
  * @param  None
  * @retval None
  */
void adc_intr(void)
{
  if (ADC1->SR & ADC_FLAG_EOC) {
    ADC1->SR &= ~ADC_FLAG_EOC;
  }
}

