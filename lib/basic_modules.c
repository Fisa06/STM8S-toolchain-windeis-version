//
// Created by karel on 24.06.2024.
//
#include <stm8s.h>
#include "basic_modules.h"
#include "stm8s_tim2.h"
#define MCU_FREQ 16000000

void _get_prescaler_and_period(uint32_t desired_frequency, TIM2_Prescaler_TypeDef* prescaler, uint16_t* period) {
    TIM2_Prescaler_TypeDef prescalers[] = {TIM2_PRESCALER_1, TIM2_PRESCALER_2, TIM2_PRESCALER_4, TIM2_PRESCALER_8, TIM2_PRESCALER_16, TIM2_PRESCALER_32, TIM2_PRESCALER_64, TIM2_PRESCALER_128, TIM2_PRESCALER_256};
    size_t num_prescalers = sizeof(prescalers) / sizeof(prescalers[0]);

    for (size_t i = 0; i < num_prescalers; ++i) {
        uint32_t period_temp = MCU_FREQ / ((prescalers[i] + 1) * desired_frequency);
        if (period_temp <= 65535) {
            *prescaler = prescalers[i];
            *period = period_temp;
            break;
        }
    }
}

void init_pwm_module(){

TIM2_TimeBaseInit( TIM2_PRESCALER_16 // divides mcu frequency by 16
                      , 1000 - 1); // auto reload register AKA how much ticks from prescaler does it take to make on period (starts from 0 so that is  why -1) max val is 16bit num so 65535


//tim2_ch1 - PD4
//tim2_ch2 - PD3
//tim2_ch3 - PA3

    TIM2_OC1Init(TIM2_OCMODE_PWM1,  // mode of pwm pwm2 is basicly inverted pwm1
                 TIM2_OUTPUTSTATE_ENABLE, // enable output by default
                 0,                           // sets the duty cycle (how many ticks from prescaler does it take to flip from 0 to 1) it has to be less than set period
                 TIM2_OCPOLARITY_HIGH);   // sets the polarity of the output (high or low) AKA inverst the pwm



    TIM2_OC2Init(TIM2_OCMODE_PWM1,
                 TIM2_OUTPUTSTATE_ENABLE,
                 0,
                 TIM2_OCPOLARITY_HIGH);



    TIM2_OC3Init(TIM2_OCMODE_PWM1,
                 TIM2_OUTPUTSTATE_ENABLE,
                 0,
                 TIM2_OCPOLARITY_HIGH); // obrácení pwm prozoze npn tranzostory spinaji k nule
    TIM2_OC1PreloadConfig(ENABLE);
    TIM2_OC2PreloadConfig(ENABLE);
    TIM2_OC3PreloadConfig(ENABLE);

    TIM2_Cmd(ENABLE); // povolí TIM2

}