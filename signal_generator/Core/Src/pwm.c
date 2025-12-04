/*
 * pwm.c
 *
 *  Created on: Dec 4, 2025
 *      Author: huse2
 */

#include "pwm.h"


void pwmChannelStart(TIM_HandleTypeDef *htim, uint32_t channel){

	HAL_TIM_PWM_Start(htim, channel);
}

void pwmChannelStop(TIM_HandleTypeDef *htim, uint32_t channel){

	HAL_TIM_PWM_Stop(htim, channel);
}

void setPwmFreqDuty(float frequency, float dutyCycle){
	  TIM4 ->ARR = (int)(CONSTANT_TIMER_VALUE/frequency);
	  TIM4 ->CCR1 = (int) ((TIM4 ->ARR)*(dutyCycle/100.0));
}
